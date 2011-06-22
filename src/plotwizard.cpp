#include "plotwizard.h"
#include "global.h"

#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSqlTableModel>


PlotWizard::PlotWizard(QSqlTableModel* student_list, QSqlTableModel* exam_list, QWidget *parent) :
    QDialog(parent)
{
	subjectLabel = new QLabel(tr("Select &Subjects"));
	checkChinese = new QCheckBox(QObject::tr("Chinese"));
	checkMaths = new QCheckBox(QObject::tr("Maths"));
	checkForignLanguage = new QCheckBox(QObject::tr("Foreign Language"));
	checkPhysics = new QCheckBox(QObject::tr("Physics"));
	checkChemistry = new QCheckBox(QObject::tr("Chemistry"));
	checkBiology = new QCheckBox(QObject::tr("Biology"));
	checkPolitics = new QCheckBox(QObject::tr("Politics"));
	checkHistory = new QCheckBox(QObject::tr("History"));
	checkGeography = new QCheckBox(QObject::tr("Geography"));

	subjectLabel->setBuddy(checkChinese);
	checkChinese->setChecked(true);
	checkMaths->setChecked(true);
	checkForignLanguage->setChecked(true);

	studentLabel = new QLabel(tr("Select St&udent"));
	studentCombo = new QComboBox;
	startExamLabel = new QLabel(tr("S&tart Exam"));
	startExamCombo = new QComboBox;
	endExamLabel = new QLabel(tr("&End Exam"));
	endExamCombo = new QComboBox;
	plotButton = new QPushButton(tr("&Plot"));
	cancelButton = new QPushButton(tr("C&ancel"));

	studentCombo->setModel(student_list);
	studentCombo->setModelColumn(Global::Student_Name);
	studentLabel->setBuddy(studentCombo);
	startExamCombo->setModel(exam_list);
	startExamCombo->setModelColumn(Global::Exam_Name);
	startExamLabel->setBuddy(startExamCombo);
	endExamCombo->setModel(exam_list);
	endExamCombo->setModelColumn(Global::Exam_Name);
	endExamLabel->setBuddy(endExamCombo);
	connect(plotButton, SIGNAL(clicked()), this, SLOT(accept()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

	QVBoxLayout* leftLayout = new QVBoxLayout;
	leftLayout->addWidget(subjectLabel);
	leftLayout->addWidget(checkChinese);
	leftLayout->addWidget(checkMaths);
	leftLayout->addWidget(checkForignLanguage);
	leftLayout->addWidget(checkPhysics);
	leftLayout->addWidget(checkChemistry);
	leftLayout->addWidget(checkBiology);
	leftLayout->addWidget(checkPolitics);
	leftLayout->addWidget(checkHistory);
	leftLayout->addWidget(checkGeography);

	QVBoxLayout* rightLayout = new QVBoxLayout;
	rightLayout->addWidget(studentLabel);
	rightLayout->addWidget(studentCombo);
	rightLayout->addWidget(startExamLabel);
	rightLayout->addWidget(startExamCombo);
	rightLayout->addWidget(endExamLabel);
	rightLayout->addWidget(endExamCombo);
	rightLayout->addStretch();
	rightLayout->addWidget(plotButton);
	rightLayout->addWidget(cancelButton);

	QHBoxLayout *mainLayout = new QHBoxLayout;
	mainLayout->addLayout(leftLayout);
	mainLayout->addLayout(rightLayout);
	setLayout(mainLayout);
}

PlotWizard::~PlotWizard()
{
}

int PlotWizard::selectedStudent() const
{
	QSqlTableModel* model = qobject_cast<QSqlTableModel*>(studentCombo->model());
	return model->data(model->index(studentCombo->currentIndex(),Global::Student_Id)).toInt();
}

int PlotWizard::startExam() const
{
	QSqlTableModel* model = qobject_cast<QSqlTableModel*>(startExamCombo->model());
	return model->data(model->index(startExamCombo->currentIndex(),Global::Exam_Id)).toInt();
}

int PlotWizard::endExam() const
{
	QSqlTableModel* model = qobject_cast<QSqlTableModel*>(endExamCombo->model());
	return model->data(model->index(endExamCombo->currentIndex(),Global::Exam_Id)).toInt();
}

QList<int> PlotWizard::selectedSubjects() const
{
	QList<int> subjects;
	if(checkChinese->isChecked())
		subjects.append(Global::Score_Chinese);
	if(checkMaths->isChecked())
		subjects.append(Global::Score_Maths);
	if(checkForignLanguage->isChecked())
		subjects.append(Global::Score_ForeignLanguage);
	if(checkPhysics->isChecked())
		subjects.append(Global::Score_Physics);
	if(checkChemistry->isChecked())
		subjects.append(Global::Score_Chemistry);
	if(checkBiology->isChecked())
		subjects.append(Global::Score_Biology);
	if(checkPolitics->isChecked())
		subjects.append(Global::Score_Politics);
	if(checkHistory->isChecked())
		subjects.append(Global::Score_History);
	if(checkGeography->isChecked())
		subjects.append(Global::Score_Geography);

	return subjects;
}

QString PlotWizard::selectedStudentName() const
{
	return studentCombo->currentText();
}
