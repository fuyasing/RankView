#ifndef SCOREVIEW_H
#define SCOREVIEW_H

#include <QWidget>

#include "global.h"

class QSqlTableModel;
class QSqlRelationalTableModel;
class QTableView;
class QHBoxLayout;

class ScoreView : public QWidget
{
	Q_OBJECT

	public:

		explicit ScoreView(QSqlTableModel* student_list, QSqlTableModel* exam_list, QSqlRelationalTableModel* score_list, QWidget *parent = 0);
		~ScoreView();

		QSqlTableModel* studentListModel() const;
		void setStudentListModel(QSqlTableModel* student_list);
		QSqlTableModel* examListModel() const;
		void setExamListModel(QSqlTableModel* exam_list);
		QSqlRelationalTableModel* scoreListModel() const;
		void setScoreListModel(QSqlRelationalTableModel* score_list);
		void setCurrentStudent(int row = 0);

	private slots:

		void updateScoreListView();

	private:

		void createStudentListView(QSqlTableModel* student_list);
		void createExamListView(QSqlTableModel* exam_list);
		void createScoreListView(QSqlRelationalTableModel* score_list);

		QHBoxLayout* m_mainLayout;
		QTableView* m_studentListView;
		QTableView* m_examListView;
		QTableView* m_scoreListView;

};

#endif
