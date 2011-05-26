#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphics.h"
#include "rankviewdialog.h"
#include "nodedata.h"

#include <QMessageBox>4

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->getGraphics, SIGNAL(clicked()), this, SLOT(Button_clicked()));
    QHash<QString,int> rank1;
    rank1.insert(tr("地理"), 1);
    rank1.insert(tr("英语"),1);
    rank1.insert(tr("数学"),0);
    rank1.insert(tr("语文"),-1);
    NodeData *node1 = new NodeData(tr("第一次考试"),20, rank1);
    nodeList.append(node1);
    QHash<QString,int> rank2;
    rank2.insert(tr("英语"),1);
    rank2.insert(tr("数学"),0);
    rank2.insert(tr("语文"),1);
    NodeData *node2 = new NodeData(tr("期中考试"),1, rank2);
    nodeList.append(node2);
    QHash<QString,int> rank3;
    rank3.insert(tr("英语"),1);
    rank3.insert(tr("数学"),1);
    rank3.insert(tr("语文"),-1);
    NodeData *node3 = new NodeData(tr("期末考试"),15, rank3);
    nodeList.append(node3);
    QHash<QString,int> rank4;
    rank4.insert(tr("英语"),1);
    rank4.insert(tr("数学"),-1);
    rank4.insert(tr("语文"),0);
    NodeData *node4 = new NodeData(tr("月考"),45, rank4);
    nodeList.append(node4);
    QHash<QString,int> rank5;
    rank5.insert(tr("英语"),1);
    rank5.insert(tr("数学"),1);
    rank5.insert(tr("语文"),0);
    NodeData *node5 = new NodeData(tr("冲刺考试"),5, rank5);
    nodeList.append(node5);
    QHash<QString,int> rank6;
    rank6.insert(tr("英语"),-1);
    rank6.insert(tr("数学"),1);
    rank6.insert(tr("语文"),0);
    NodeData *node6 = new NodeData(tr("升级考试"),2, rank6);
    nodeList.append(node6);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Button_clicked()
{
    QString stdname("Stella Fu");
    if(nodeList.size()==0)
    {
        QMessageBox::about(this,tr("排名数据为空"),tr("%1考试数据为空,请录入考试排名").arg(stdname));
        return;
    }
    RankViewDialog *dialog = new RankViewDialog(stdname, nodeList);
    dialog->setVisible(1);
}
