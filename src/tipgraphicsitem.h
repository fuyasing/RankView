#ifndef TIPGRAPHICSITEM_H
#define TIPGRAPHICSITEM_H

#include <QGraphicsItem>

#include "conodegraphicsitem.h"

class TipGraphicsItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit TipGraphicsItem(RankHash ranks);

    enum { Type = UserType + 3 };
    int type() const { return Type; }

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:

public slots:

private:
    RankHash m_ranks;

};

#endif // TIPGRAPHICSITEM_H
