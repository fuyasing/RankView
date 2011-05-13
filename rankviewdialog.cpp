#include "rankviewdialog.h"
#include "graphics.h"

#include <QVBoxLayout>
#include <QDialogButtonBox>

RankViewDialog::RankViewDialog(QWidget *parent) :
    QDialog(parent)
{
    QVBoxLayout *viewLayout = new QVBoxLayout;
    Graphics *rankView = new Graphics;
    viewLayout->addWidget(rankView);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok, Qt::Horizontal);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    viewLayout->addWidget(buttonBox);
     this->setLayout(viewLayout);
}
