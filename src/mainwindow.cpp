#include "mainwindow.h"
#include "scoreview.h"
#include "plotwizard.h"
#include "nodedata.h"
#include "rankviewdialog.h"

#include <QApplication>
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QIcon>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QSettings>
#include <QtAlgorithms>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
{
	m_subjectMap.insert(Global::Score_Chinese,QObject::tr("Chinese"));
	m_subjectMap.insert(Global::Score_Maths,QObject::tr("Maths"));
	m_subjectMap.insert(Global::Score_ForeignLanguage,QObject::tr("Foreign Language"));
	m_subjectMap.insert(Global::Score_Physics,QObject::tr("Physics"));
	m_subjectMap.insert(Global::Score_Chemistry,QObject::tr("Chemistry"));
	m_subjectMap.insert(Global::Score_Biology,QObject::tr("Biology"));
	m_subjectMap.insert(Global::Score_Politics,QObject::tr("Politics"));
	m_subjectMap.insert(Global::Score_History,QObject::tr("History"));
	m_subjectMap.insert(Global::Score_Geography,QObject::tr("Geography"));

	QWidget* blankWidget = new QWidget;
	blankWidget->setMinimumSize(1000,600);
	setCentralWidget(blankWidget);

	createActions();
	createMenus();
	createToolBars();

	readSettings();

	setWindowIcon(QIcon(":/images/logo"));
	setWindowTitle(tr("RankView"));
}

MainWindow::~MainWindow()
{
	m_DB.close();
}

void MainWindow::newDB()
{
	QString dbName = QFileDialog::getSaveFileName(this,tr("Create New RankView Database"),".",tr("RankView DB (*.rkv)"));
	if(!dbName.isEmpty())
		if(setCurrentDB(dbName))
			createTable();
}

void MainWindow::openDB()
{
	QString dbName = QFileDialog::getOpenFileName(this,tr("Open An Exsisted RankView Database"),".",tr("RankView DB (*.rkv)"));
	if(!dbName.isEmpty())
		if(setCurrentDB(dbName))
			openTable();
}

void MainWindow::importData()
{
	int exam_id;
	QString dataFileName = QFileDialog::getOpenFileName(this,tr("Import Data From a CSV File"),".",tr("CSV File (*.csv)"));
	if(dataFileName.isEmpty())
		return;
	QFile dataFile(dataFileName);
	if(!dataFile.open(QIODevice::ReadOnly))
	{
		QMessageBox::critical(this,tr("Open File Failed"),tr("Cannot open selected file"));;
		return;
	}

	QSqlTableModel* student = m_scoreView->studentListModel();
	QSqlTableModel* exam = m_scoreView->examListModel();
	QSqlRelationalTableModel* score = m_scoreView->scoreListModel();

	QFileInfo tmp(dataFileName);
	QString exam_name = tmp.baseName();
	exam->setFilter(QString("name = \'%1\'").arg(exam_name));
	if(exam->rowCount() == 1)
	{
		QSqlRecord rq = exam->record(0);
		exam_id = rq.value("id").toInt();
	}
	else
	{
		exam->insertRow(0);
		exam->setData(exam->index(0,Global::Exam_Name),exam_name);
		exam->submitAll();
		exam->setFilter(QString("name = \'%1\'").arg(exam_name));
		QSqlRecord rq = exam->record(0);
		exam_id = rq.value("id").toInt();
	}

	QHash<QString,int> studentMap;
	for(int row = 0;row < student->rowCount();++row)
		studentMap.insert(student->data(student->index(row,1)).toString(),student->data(student->index(row,0)).toInt());

	QTextStream in(&dataFile);
	QString record = in.readLine();
	QStringList cols = record.split(";");
	if(cols.size()!=11)
	{
		QMessageBox::critical(this,tr("Import Data Failed"),tr("file format illegal"));
		return;
	}
	while(!in.atEnd())
	{
		record = in.readLine();
		cols = record.split(";");
		if(cols.size()!=11)
			continue;
		if(!studentMap.contains(cols[Global::Data_StudentNum]))
		{
			student->insertRow(0);
			student->setData(student->index(0,Global::Student_Num),cols[Global::Data_StudentNum].toInt());
			student->setData(student->index(0,Global::Student_Name),cols[Global::Data_StudentName]);
			student->submitAll();
			student->setFilter(QString("num = %1").arg(cols[Global::Data_StudentNum]));
			QSqlRecord rq = student->record(0);
			studentMap.insert(cols[Global::Data_StudentNum],rq.value("id").toInt());
		}
		score->insertRow(0);
		score->setData(score->index(0,Global::Score_StudentId),studentMap.value(cols[Global::Data_StudentNum]));
		score->setData(score->index(0,Global::Score_ExamId),exam_id);
		score->setData(score->index(0,Global::Score_Chinese),cols[Global::Data_Chinese]);
		score->setData(score->index(0,Global::Score_Maths),cols[Global::Data_Maths]);
		score->setData(score->index(0,Global::Score_ForeignLanguage),cols[Global::Data_ForeignLanguage]);
		score->setData(score->index(0,Global::Score_Physics),cols[Global::Data_Physics]);
		score->setData(score->index(0,Global::Score_Chemistry),cols[Global::Data_Chemistry]);
		score->setData(score->index(0,Global::Score_Biology),cols[Global::Data_Biology]);
		score->setData(score->index(0,Global::Score_Politics),cols[Global::Data_Politics]);
		score->setData(score->index(0,Global::Score_History),cols[Global::Data_History]);
		score->setData(score->index(0,Global::Score_Geography),cols[Global::Data_Geography]);
		score->submitAll();
	}
	student->setFilter("id > -1");
	exam->setFilter("id > -1");
	m_scoreView->setCurrentStudent();
}

void MainWindow::applyChanges()
{
	QSqlTableModel* student = m_scoreView->studentListModel();
	QSqlRelationalTableModel* score = m_scoreView->scoreListModel();
	student->submitAll();
	score->submitAll();
}

void MainWindow::revertChanges()
{
	QSqlTableModel* student = m_scoreView->studentListModel();
	QSqlRelationalTableModel* score = m_scoreView->scoreListModel();
	student->revertAll();
	score->revertAll();
}

void MainWindow::plotRank()
{
	QSqlTableModel* student_list = m_scoreView->studentListModel();
	QSqlTableModel* exam_list = m_scoreView->examListModel();
	PlotWizard* plotDlg = new PlotWizard(student_list, exam_list, this);
	if(plotDlg->exec())
	{
		QList<NodeData*> node_list = computeNodeList(plotDlg->selectedStudent(),plotDlg->startExam(),plotDlg->endExam(),plotDlg->selectedSubjects());
		RankViewDialog* rankview = new RankViewDialog(plotDlg->selectedStudentName(),node_list);
		rankview->exec();
		delete rankview;

	}
	delete plotDlg;
}

void MainWindow::about()
{
	QMessageBox::about(this, tr("About RankView"),
			tr("<h2>RankView 1.0</h2>"
				"<p>Copyright &copy; 2011 Free Storm ORG</p>"
				"<p>RankView is a small software written for Michael Ding's dear teacher</p>"
				"<p>Authors:</p>"
				"<p>Michael Ding &lt;dingyan@freestorm.org&gt;</p>"
				"<p>Stella Fu &lt;fuyaxing@freestorm.org&gt;</p>"
			  ));
}

void MainWindow::openRecentDB()
{
	QAction* action = qobject_cast<QAction*>(sender());
	if(action)
	{
		if(setCurrentDB(action->data().toString()))
			openTable();
	}
}

void MainWindow::createActions()
{
	newAction = new QAction(tr("&New"),this);
	newAction->setIcon(QIcon(":images/new.png"));
	newAction->setShortcut(QKeySequence::New);
	newAction->setStatusTip(tr("Create New DataBase"));
	connect(newAction, SIGNAL(triggered()),this, SLOT(newDB()));

	openAction = new QAction(tr("&Open"),this);
	openAction->setIcon(QIcon(":images/open.png"));
	openAction->setShortcut(QKeySequence::Open);
	openAction->setStatusTip(tr("Open exsisted DataBase"));
	connect(openAction, SIGNAL(triggered()),this, SLOT(openDB()));

	importAction = new QAction(tr("&Import"),this);
	importAction->setIcon(QIcon(":images/import.png"));
	importAction->setShortcut(QKeySequence::Save);
	importAction->setStatusTip(tr("Import Data To The Current DataBase"));
	importAction->setEnabled(false);
	connect(importAction, SIGNAL(triggered()),this, SLOT(importData()));

	applyAction = new QAction(tr("&Apply"),this);
	applyAction->setIcon(QIcon(":images/apply.png"));
	applyAction->setStatusTip(tr("Apply Changes To Database"));
	applyAction->setEnabled(false);
	connect(applyAction, SIGNAL(triggered()),this,SLOT(applyChanges()));

	revertAction = new QAction(tr("&Revert"),this);
	revertAction->setIcon(QIcon(":images/revert.png"));
	revertAction->setStatusTip(tr("Give Up Changes To Database"));
	revertAction->setEnabled(false);
	connect(revertAction, SIGNAL(triggered()),this,SLOT(revertChanges()));

	plotAction = new QAction(tr("&Plot"),this);
	plotAction->setIcon(QIcon(":images/plot.png"));
	plotAction->setShortcut(QKeySequence::Print);
	plotAction->setStatusTip(tr("Plot For Current Student"));
	plotAction->setEnabled(false);
	connect(plotAction, SIGNAL(triggered()),this, SLOT(plotRank()));

	for (int i =0; i<Global::MaxRecentDBs;++i)
	{
		recentDBActions[i] = new QAction(this);
		recentDBActions[i]->setVisible(false);
		connect(recentDBActions[i],SIGNAL(triggered()),this,SLOT(openRecentDB()));
	}

	quitAction = new QAction(tr("Q&uit"),this);
	quitAction->setShortcut(QString("Ctrl+Q"));
	quitAction->setStatusTip(tr("Quit The Application"));
	connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));

	aboutAction = new QAction(tr("About"), this);
	aboutAction->setStatusTip(tr("Show RankView's About Box"));
	connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

	aboutQtAction = new QAction(tr("About &Qt"), this);
	aboutQtAction->setStatusTip(tr("Show Qt Library's About Box"));
	connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(newAction);
	fileMenu->addAction(openAction);
	fileMenu->addAction(importAction);
	fileMenu->addAction(quitAction);
	fileMenu->addSeparator();
	for(int i =0; i<Global::MaxRecentDBs;++i)
		fileMenu->addAction(recentDBActions[i]);
	fileMenu->addSeparator();
	fileMenu->addAction(quitAction);

	editMenu = menuBar()->addMenu(tr("&Edit"));
	editMenu->addAction(applyAction);
	editMenu->addAction(revertAction);

	menuBar()->addAction(plotAction);

	menuBar()->addSeparator();

	helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(aboutAction);
	helpMenu->addAction(aboutQtAction);
}

void MainWindow::createToolBars()
{
	fileToolBar = addToolBar(tr("File"));
	fileToolBar->addAction(newAction);
	fileToolBar->addAction(openAction);
	fileToolBar->addAction(importAction);

	editToolBar = addToolBar(tr("Edit"));
	editToolBar->addAction(applyAction);
	editToolBar->addAction(revertAction);

	plotToolBar = addToolBar(tr("Plot"));
	plotToolBar->addAction(plotAction);
}

void MainWindow::readSettings()
{
	QSettings settings("Free Storm Org","RankView");

	m_recentDBs = settings.value("recentDBs").toStringList();
}

void MainWindow::writeSettings()
{
	QSettings settings("Free Storm Org","RankView");

	settings.setValue("recentDBs", m_recentDBs);
}

bool MainWindow::setCurrentDB(const QString &dbName)
{
	m_DB = QSqlDatabase::addDatabase("QSQLITE");
	m_DB.setDatabaseName(dbName);
	if(!m_DB.open())
	{
		QMessageBox::critical(this,tr("Database Connect Failed"),m_DB.lastError().text());
		return false;
	}
	m_curDB = dbName;
	m_recentDBs.removeAll(m_curDB);
	m_recentDBs.prepend(m_curDB);
	updateRecentDBActions();
	importAction->setEnabled(true);
	plotAction->setEnabled(true);
	applyAction->setEnabled(true);
	revertAction->setEnabled(true);
	setWindowTitle(QString("%1 - %2").arg(m_curDB).arg(tr("RankView")));
	return true;
}

void MainWindow::createTable()
{
	QString query = "CREATE TABLE student ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT,"
		"num INTEGER NOT NULL,"
		"name VARCHAR(40) NOT NULL);";
	QSqlQuery stuq(query);
	if(!stuq.isActive())
	{
		QMessageBox::critical(this,tr("Table Create Failed"),tr("create table student failed because:\n")+stuq.lastError().text());
		return;
	}
	query = "CREATE TABLE exam ("
		"id integer primary key autoincrement,"
		"name varchar(100) not null);";
	QSqlQuery exaq(query);
	if(!exaq.isActive())
	{
		QMessageBox::critical(this,tr("Table Create Failed"),tr("create table exam failed because:\n")+exaq.lastError().text());
		return;
	}
	query = "CREATE TABLE score ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT,"
		"studentid INTEGER NOT NULL,"
		"examid INTEGER NOT NULL,"
		"chinese INTEGER NOT NULL,"
		"maths INTEGER NOT NULL,"
		"foreignlanguage INTEGER NOT NULL,"
		"chemistry INTEGER NOT NULL,"
		"biology INTEGER NOT NULL,"
		"politics INTEGER NOT NULL,"
		"history INTEGER NOT NULL,"
		"geography INTEGER NOT NULL,"
		"FOREIGN KEY (studentid) REFERENCES student,"
		"FOREIGN KEY (examid) REFERENCES exam);";
	QSqlQuery scoq(query);
	if(!scoq.isActive())
	{
		QMessageBox::critical(this,tr("Table Create Failed"),tr("create table score failed because:\n")+scoq.lastError().text());
		return;
	}
	QSqlRelationalTableModel* scoreModel = new QSqlRelationalTableModel;
	scoreModel->setTable("score");
	scoreModel->setRelation(Global::Score_StudentId, 
			QSqlRelation("student","id","id"));
	scoreModel->setRelation(Global::Score_ExamId,
			QSqlRelation("exam","id","id"));
	scoreModel->setSort(Global::Score_ExamId, Qt::AscendingOrder);
	scoreModel->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);
	scoreModel->setHeaderData(Global::Score_Chinese, Qt::Horizontal, QObject::tr("Chinese"));
	scoreModel->setHeaderData(Global::Score_Maths, Qt::Horizontal, QObject::tr("Maths"));
	scoreModel->setHeaderData(Global::Score_ForeignLanguage, Qt::Horizontal, QObject::tr("Foreign Language"));
	scoreModel->setHeaderData(Global::Score_Physics, Qt::Horizontal, QObject::tr("Physics"));
	scoreModel->setHeaderData(Global::Score_Chemistry, Qt::Horizontal, QObject::tr("Chemistry"));
	scoreModel->setHeaderData(Global::Score_Biology, Qt::Horizontal, QObject::tr("Biology"));
	scoreModel->setHeaderData(Global::Score_Politics, Qt::Horizontal, QObject::tr("Politics"));
	scoreModel->setHeaderData(Global::Score_History, Qt::Horizontal, QObject::tr("History"));
	scoreModel->setHeaderData(Global::Score_Geography, Qt::Horizontal, QObject::tr("Geography"));
	if(!scoreModel->select())
	{
		QMessageBox::critical(this,tr("Table Create Failed"),tr("select table score failed because:\n")+scoreModel->lastError().text());
		return;
	}

	QSqlTableModel* studentModel = scoreModel->relationModel(Global::Score_StudentId);
	studentModel->setSort(Global::Student_Id, Qt::AscendingOrder);
	studentModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	studentModel->setHeaderData(Global::Student_Num, Qt::Horizontal, tr("Student No."));
	studentModel->setHeaderData(Global::Student_Name, Qt::Horizontal, tr("Name"));
	if(!studentModel->select())
	{
		QMessageBox::critical(this,tr("Table Create Failed"),tr("select table student failed because:\n")+studentModel->lastError().text());
		return;
	}

	QSqlTableModel* examModel = scoreModel->relationModel(Global::Score_ExamId);
	examModel->setSort(Global::Exam_Id, Qt::AscendingOrder);
	examModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	examModel->setHeaderData(Global::Exam_Name, Qt::Horizontal, tr("Examination Name"));
	if(!examModel->select())
	{
		QMessageBox::critical(this,tr("Table Create Failed"),tr("select table exam failed because:\n")+examModel->lastError().text());
		return;
	}

	m_scoreView = new ScoreView(studentModel, examModel, scoreModel);
	setCentralWidget(m_scoreView);

}

void MainWindow::openTable()
{
	QSqlRelationalTableModel* scoreModel = new QSqlRelationalTableModel;
	scoreModel->setTable("score");
	scoreModel->setRelation(Global::Score_StudentId, 
			QSqlRelation("student","id","id"));
	scoreModel->setRelation(Global::Score_ExamId,
			QSqlRelation("exam","id","id"));
	scoreModel->setSort(Global::Score_ExamId, Qt::AscendingOrder);
	scoreModel->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);
	scoreModel->setHeaderData(Global::Score_Chinese, Qt::Horizontal, QObject::tr("Chinese"));
	scoreModel->setHeaderData(Global::Score_Maths, Qt::Horizontal, QObject::tr("Maths"));
	scoreModel->setHeaderData(Global::Score_ForeignLanguage, Qt::Horizontal, QObject::tr("Foreign Language"));
	scoreModel->setHeaderData(Global::Score_Physics, Qt::Horizontal, QObject::tr("Physics"));
	scoreModel->setHeaderData(Global::Score_Chemistry, Qt::Horizontal, QObject::tr("Chemistry"));
	scoreModel->setHeaderData(Global::Score_Biology, Qt::Horizontal, QObject::tr("Biology"));
	scoreModel->setHeaderData(Global::Score_Politics, Qt::Horizontal, QObject::tr("Politics"));
	scoreModel->setHeaderData(Global::Score_History, Qt::Horizontal, QObject::tr("History"));
	scoreModel->setHeaderData(Global::Score_Geography, Qt::Horizontal, QObject::tr("Geography"));
	if(!scoreModel->select())
	{
		QMessageBox::critical(this,tr("Table Open Failed"),tr("open table score failed because:\n")+scoreModel->lastError().text());
		return;
	}

	QSqlTableModel* studentModel = scoreModel->relationModel(Global::Score_StudentId);
	studentModel->setSort(Global::Student_Id, Qt::AscendingOrder);
	studentModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	studentModel->setHeaderData(Global::Student_Num, Qt::Horizontal, tr("Student No."));
	studentModel->setHeaderData(Global::Student_Name, Qt::Horizontal, tr("Name"));
	if(!studentModel->select())
	{
		QMessageBox::critical(this,tr("Table Open Failed"),tr("open table student failed because:\n")+studentModel->lastError().text());
		return;
	}

	QSqlTableModel* examModel = scoreModel->relationModel(Global::Score_ExamId);
	examModel->setSort(Global::Exam_Id, Qt::AscendingOrder);
	examModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	examModel->setHeaderData(Global::Exam_Name, Qt::Horizontal, tr("Examination Name"));
	if(!examModel->select())
	{
		QMessageBox::critical(this,tr("Table Open Failed"),tr("open table exam failed because:\n")+examModel->lastError().text());
		return;
	}

	m_scoreView = new ScoreView(studentModel, examModel, scoreModel);
	setCentralWidget(m_scoreView);
}

void MainWindow::updateRecentDBActions()
{
	QMutableStringListIterator i(m_recentDBs);

	while(i.hasNext())
	{
		if (!QFile::exists(i.next()))
			i.remove();
	}

	for (int j=0;j < Global::MaxRecentDBs; ++j)
	{
		if (j < m_recentDBs.count())
		{
			QString text = QString("&%1 %2").arg(j+1).arg(strippedName(m_recentDBs[j]));
			recentDBActions[j]->setText(text);
			recentDBActions[j]->setData(m_recentDBs[j]);
			recentDBActions[j]->setVisible(true);
		}
		else
		{
			recentDBActions[j]->setVisible(false);
		}
	}
}

QString MainWindow::strippedName(const QString &fullFileName)
{
	return QFileInfo(fullFileName).fileName();
}

QList<NodeData*> MainWindow::computeNodeList(int student_id, int start_exam, int end_exam, QList<int> subjects)
{
	QList<NodeData*> node_list;

	if(subjects.isEmpty())
		return node_list;

	QList<QList<QPair<int,int> > > rows_subjects_scores;
	QList<QList<int> > all_exams_ranks;
	QSqlRelationalTableModel* scoreModel = m_scoreView->scoreListModel();
	scoreModel->setFilter(QString("examid BETWEEN %1 AND %2").arg(start_exam).arg(end_exam));
	QSqlTableModel* examModel = m_scoreView->examListModel();

	int row = 0;
	int last_examid = scoreModel->data(scoreModel->index(row, Global::Score_ExamId)).toInt();
	NodeData* node = new NodeData;
	node->setExamName(examModel->data(examModel->index(last_examid-1,Global::Exam_Name)).toString());
	node_list.append(node);

	for(;row<scoreModel->rowCount();)
	{
		if(last_examid == scoreModel->data(scoreModel->index(row, Global::Score_ExamId)).toInt())
		{
			int studentId = scoreModel->data(scoreModel->index(row,Global::Score_StudentId)).toInt();
			int subject, sumscore = 0;
			QList<QPair<int,int> > row_subjects_scores;
			foreach(subject,subjects)
			{
				int subject_score = scoreModel->data(scoreModel->index(row,subject)).toInt();
				QPair<int,int> row_subject_score = qMakePair(studentId,subject_score);
				row_subjects_scores.append(row_subject_score);
				sumscore += subject_score;
			}
			QPair<int,int> one_sum_scores = qMakePair(studentId,sumscore);
			row_subjects_scores.prepend(one_sum_scores);
			rows_subjects_scores.append(row_subjects_scores);
			row++;
		}
		else
		{
			QList<QPair<int,int> > subject_students_scores;
			QList<int> single_exam_ranks;
			for(int i=0; i<subjects.size()+1; ++i)
			{
				for(int j=0;j<rows_subjects_scores.size();++j)
					subject_students_scores.append(rows_subjects_scores.at(j).at(i));
				qStableSort(subject_students_scores.begin(),subject_students_scores.end(),greater);
				single_exam_ranks.append(buildRank(student_id,subject_students_scores));
				subject_students_scores.clear();
			}
			all_exams_ranks.append(single_exam_ranks);
			rows_subjects_scores.clear();
			last_examid = scoreModel->data(scoreModel->index(row,Global::Score_ExamId)).toInt();
			node = new NodeData;
			node->setExamName(examModel->data(examModel->index(last_examid-1,Global::Exam_Name)).toString());
			node_list.append(node);
		}
	}
	QList<QPair<int,int> > subject_students_scores;
	QList<int> single_exam_ranks;
	for(int i=0; i<subjects.size()+1; ++i)
	{
		for(int j=0;j<rows_subjects_scores.size();++j)
			subject_students_scores.append(rows_subjects_scores.at(j).at(i));
		qStableSort(subject_students_scores.begin(),subject_students_scores.end(),greater);
		single_exam_ranks.append(buildRank(student_id,subject_students_scores));
		subject_students_scores.clear();
	}
	all_exams_ranks.append(single_exam_ranks);
	rows_subjects_scores.clear();
	single_exam_ranks.clear();

	single_exam_ranks = all_exams_ranks.first();
	node_list.first()->setRank(single_exam_ranks.first());
	QHash<QString,int> subject_trend;
	for(int k = 1; k<single_exam_ranks.size(); ++k)
	{
		int trend = 0;
		QString subject_name = m_subjectMap.value(subjects.at(k-1));
		subject_trend.insert(subject_name,trend);
	}
	node_list.first()->setSubjectTrend(subject_trend);

	for(int m=1; m<all_exams_ranks.size(); ++m)
	{
		single_exam_ranks.clear();
		subject_trend.clear();
		single_exam_ranks = all_exams_ranks.at(m);
		node_list.at(m)->setRank(single_exam_ranks.first());
		for(int k =1; k<single_exam_ranks.size(); ++k)
		{
			int trend = all_exams_ranks.at(m-1).at(k) - single_exam_ranks.at(k);
			QString subject_name = m_subjectMap.value(subjects.at(k-1));
			subject_trend.insert(subject_name,trend);
		}
		node_list.at(m)->setSubjectTrend(subject_trend);
	}

	m_scoreView->setCurrentStudent();
	return node_list;
}

//QList<NodeData*> MainWindow::computeNodeList(int student_id, int start_exam, int end_exam, QList<int> subjects)
//{
	//QList<NodeData*> node_list;
	////
	//m_scoreView->setCurrentStudent();
	//return node_list;
//}
bool MainWindow::greater(const QPair<int,int> rank_item1,const QPair<int,int> rank_item2)
{
	return (rank_item1.second > rank_item2.second);
}

int MainWindow::buildRank(int student_id, QList<QPair<int,int> > scores)
{
	int index=-1;
	for(int i=0; i<scores.size(); ++i)
		if(student_id == scores.at(i).first)
			if(i > 0)
			{
				for(index=i-1; index>=0; --index)
					if(scores.at(index).second!=scores.at(i).second)
					{
						index++;
						break;
					}
				if(index < 0)
					index++;
				break;
			}
			else
			{
				index = i;
				break;
			}
	return index+1;
}
