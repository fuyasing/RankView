#ifndef PLOTWIZARD_H
#define PLOTWIZARD_H

#include <QDialog>
#include <QList>

class QSqlTableModel;
class QLabel;
class QCheckBox;
class QPushButton;
class QComboBox;

class PlotWizard : public QDialog
{
    Q_OBJECT

public:
    explicit PlotWizard(QSqlTableModel* student_list, QSqlTableModel* exam_list, QWidget *parent = 0);
    ~PlotWizard();

	int selectedStudent() const;
	int startExam() const;
	int endExam() const;
	QList<int> selectedSubjects() const;
	QString selectedStudentName() const;

private:
	QLabel* subjectLabel;
	QCheckBox* checkChinese;
	QCheckBox* checkMaths;
	QCheckBox* checkForignLanguage;
	QCheckBox* checkPhysics;
	QCheckBox* checkChemistry;
	QCheckBox* checkBiology;
	QCheckBox* checkPolitics;
	QCheckBox* checkHistory;
	QCheckBox* checkGeography;

	QLabel* studentLabel;
	QComboBox* studentCombo;

	QLabel* startExamLabel;
	QComboBox* startExamCombo;

	QLabel* endExamLabel;
	QComboBox* endExamCombo;

	QPushButton* plotButton;
	QPushButton* cancelButton;
	
	QList<int> m_subjectsList;
};

#endif // PLOTWIZARD_H
