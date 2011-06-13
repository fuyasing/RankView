#include "scoreview.h"

#include <QSqlRelationalTableModel>
#include <QTableView>
#include <QHBoxLayout>
#include <QSqlRecord>
#include <QHeaderView>

ScoreView::ScoreView(QSqlTableModel* student_list, QSqlTableModel* exam_list, QSqlRelationalTableModel* score_list, QWidget* parent):QWidget(parent)
{
	m_mainLayout = new QHBoxLayout;
	createStudentListView(student_list);
	createExamListView(exam_list);
	createScoreListView(score_list);
	this->setLayout(m_mainLayout);
	m_studentListView->setCurrentIndex(studentListModel()->index(0,0));
}

ScoreView::~ScoreView()
{
}

QSqlTableModel* ScoreView::studentListModel() const
{
	return qobject_cast<QSqlTableModel*>(m_studentListView->model());
}

void ScoreView::setStudentListModel(QSqlTableModel* student_list)
{
	m_studentListView->setModel(student_list);
}

QSqlTableModel* ScoreView::examListModel() const
{
	return qobject_cast<QSqlTableModel*>(m_examListView->model());
}

void ScoreView::setExamListModel(QSqlTableModel* exam_list)
{
	m_examListView->setModel(exam_list);
}

QSqlRelationalTableModel* ScoreView::scoreListModel() const
{
	return qobject_cast<QSqlRelationalTableModel*>(m_scoreListView->model());
}

void ScoreView::setScoreListModel(QSqlRelationalTableModel* score_list)
{
	m_scoreListView->setModel(score_list);
}

void ScoreView::updateScoreListView()
{
	QModelIndex index = m_studentListView->currentIndex();
	if(index.isValid())
	{
		QSqlRecord record = studentListModel()->record(index.row());
		scoreListModel()->setFilter(QString("StudentId = %1").arg(record.value("id").toInt()));
	}
	else
	{
		scoreListModel()->setFilter("StudentId = -1");
	}
	m_scoreListView->horizontalHeader()->setVisible(m_scoreListView->model()->rowCount() > 0);
}

void ScoreView::createStudentListView(QSqlTableModel* student_list)
{
	m_studentListView = new QTableView;
	m_studentListView->setModel(student_list);
	m_studentListView->setSelectionMode(QAbstractItemView::SingleSelection);
	m_studentListView->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_studentListView->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::SelectedClicked);
	m_studentListView->setColumnHidden(Global::Student_Id,true);
	m_studentListView->horizontalHeader()->setStretchLastSection(true);
	m_studentListView->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	m_mainLayout->addWidget(m_studentListView);
	connect(m_studentListView->selectionModel(),SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)),this, SLOT(updateScoreListView()));
}

void ScoreView::createExamListView(QSqlTableModel* exam_list)
{
	m_examListView = new QTableView;
	m_examListView->setModel(exam_list);
	m_examListView->setSelectionMode(QAbstractItemView::SingleSelection);
	m_examListView->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_examListView->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::SelectedClicked);
	m_examListView->setColumnHidden(Global::Exam_Id,true);
	m_examListView->horizontalHeader()->setStretchLastSection(true);
	m_examListView->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	m_mainLayout->addWidget(m_examListView);
}

void ScoreView::createScoreListView(QSqlRelationalTableModel* score_list)
{
	m_scoreListView = new QTableView;
	m_scoreListView->setModel(score_list);
	m_scoreListView->setSelectionMode(QAbstractItemView::SingleSelection);
	m_scoreListView->setSelectionBehavior(QAbstractItemView::SelectItems);
	m_scoreListView->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::SelectedClicked);
	m_scoreListView->setColumnHidden(Global::Score_Id, true);
	m_scoreListView->setColumnHidden(Global::Score_StudentId, true);
	m_scoreListView->setColumnHidden(Global::Score_ExamId, true);
	m_scoreListView->horizontalHeader()->setStretchLastSection(true);
	m_scoreListView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	m_mainLayout->addWidget(m_scoreListView);
}

void ScoreView::setCurrentStudent(int row)
{
	m_studentListView->setCurrentIndex(studentListModel()->index(row,0));
	updateScoreListView();
}
