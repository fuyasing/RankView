#include "rankviewdialog.h"
#include "graphics.h"

#include <QVBoxLayout>
#include <QDialogButtonBox>

RankViewDialog::RankViewDialog(QString stdName, QList<NodeData*> nodeList,QWidget *parent) :
    QDialog(parent)
{
    this->setWindowTitle(tr("学生考试成绩趋势示意图"));
    QVBoxLayout *viewLayout = new QVBoxLayout;
    Graphics *rankView = new Graphics(stdName, nodeList);
    viewLayout->addWidget(rankView);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok, Qt::Horizontal);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    viewLayout->addWidget(buttonBox);
    this->setLayout(viewLayout);
}
