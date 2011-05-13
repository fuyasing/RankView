#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphics.h"
#include "rankviewdialog.h"
//#include "ui_ranktrenddialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->getGraphics, SIGNAL(clicked()), this, SLOT(Button_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Button_clicked()
{
    RankViewDialog *dialog = new RankViewDialog;
    dialog->setVisible(1);
}
