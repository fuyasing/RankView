#ifndef RANKVIEWDIALOG_H
#define RANKVIEWDIALOG_H

#include <QDialog>

class QDialogButtonBox;

class RankViewDialog : public QDialog
{
    Q_OBJECT
public:
    explicit RankViewDialog(QWidget *parent = 0);

signals:

public slots:

private:
    QDialogButtonBox *buttonBox;

};

#endif // RANKVIEWDIALOG_H
