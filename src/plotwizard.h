#ifndef PLOTWIZARD_H
#define PLOTWIZARD_H

#include <QWizard>

namespace Ui {
    class PlotWizard;
}

class PlotWizard : public QWizard
{
    Q_OBJECT

public:
    explicit PlotWizard(QWidget *parent = 0);
    ~PlotWizard();

private:
    Ui::PlotWizard *ui;
};

#endif // PLOTWIZARD_H
