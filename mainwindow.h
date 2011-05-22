#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>

namespace Ui {
    class MainWindow;
}

class NodeData;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void Button_clicked();

private:
    Ui::MainWindow *ui;
    QList<NodeData*> nodeList, nullList;
};

#endif // MAINWINDOW_H
