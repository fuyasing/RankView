#include "rankviewdialog.h"
#include "graphics.h"

#include <QVBoxLayout>
#include <QDialogButtonBox>

RankViewDialog::RankViewDialog(QString stdName, QList<NodeData*> nodeList,QWidget *parent) :
    QDialog(parent)
{
    this->setWindowTitle(tr("Student's Score Rank Trend"));
    QVBoxLayout *viewLayout = new QVBoxLayout;
	if(!nodeList.isEmpty())
	{
		Graphics *rankView = new Graphics(stdName, nodeList);
		viewLayout->addWidget(rankView);
	}
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok, Qt::Horizontal);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    viewLayout->addWidget(buttonBox);
    this->setLayout(viewLayout);
}
