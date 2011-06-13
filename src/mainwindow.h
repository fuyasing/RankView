#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QSqlRelationalTableModel>

#include "global.h"

class QAction;
class QMenu;
class QToolBar;

class ScoreView;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

	void newDB();
	void openDB();
	void importData();

	void applyChanges();
	void revertChanges();

	void plotRank();

	void about();

	void openRecentDB();

private:

	ScoreView* m_scoreView;
	QStringList m_recentDBs;
	QString m_curDB;
	QSqlDatabase m_DB;

	QMenu *fileMenu;
	QMenu *editMenu;
	QMenu *helpMenu;

	QToolBar *fileToolBar;
	QToolBar *editToolBar;
	QToolBar *plotToolBar;

	QAction *recentDBActions[Global::MaxRecentDBs];
	QAction *newAction;
	QAction *openAction;
	QAction *importAction;
	QAction *quitAction;

	QAction *applyAction;
	QAction *revertAction;

	QAction *plotAction;

	QAction *aboutAction;
	QAction *aboutQtAction;

	void createActions();
	void createMenus();
	void createToolBars();
	void readSettings();
	void writeSettings();
	bool setCurrentDB(const QString &dbName);
	void createTable();
	void openTable();
	void updateRecentDBActions();
	QString strippedName(const QString &fullFileName);

};

#endif // MAINWINDOW_H
