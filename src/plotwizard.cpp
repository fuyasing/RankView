#include "plotwizard.h"
#include "ui_plotwizard.h"

PlotWizard::PlotWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::PlotWizard)
{
    ui->setupUi(this);
}

PlotWizard::~PlotWizard()
{
    delete ui;
}
