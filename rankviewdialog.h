#ifndef RANKVIEWDIALOG_H
#define RANKVIEWDIALOG_H

#include <QDialog>
#include <QList>

class QDialogButtonBox;
class NodeData;

class RankViewDialog : public QDialog
{
    Q_OBJECT
public:
    explicit RankViewDialog(QString stdName, QList<NodeData*> nodeList,QWidget *parent = 0);

signals:

public slots:

private:
    QDialogButtonBox *buttonBox;

};

#endif // RANKVIEWDIALOG_H
