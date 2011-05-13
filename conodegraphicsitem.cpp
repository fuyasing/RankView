#include "conodegraphicsitem.h"
#include "colinegraphicsitem.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QRectF>
#include <QPainterPath>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>

CoNodeGraphicsItem::CoNodeGraphicsItem(const QColor color, const int x, const int y, QHash<QString,int> ranks)
{
    this->m_dataX = x;
    this->m_dataY = y;
    this->setPos(x, y);
    this->m_color = color;
    this->setFlags(ItemIsSelectable);
    this->setAcceptHoverEvents(true);
    this->formToolTip(ranks);
}

void CoNodeGraphicsItem::addLine(CoLineGraphicsItem *line)
{
    m_lineList << line;
}

QList<CoLineGraphicsItem *> CoNodeGraphicsItem::lines() const
{
    return m_lineList;
}

QRectF CoNodeGraphicsItem::boundingRect() const
{
    return QRectF(0,0,20,20);
}

QPainterPath CoNodeGraphicsItem::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void CoNodeGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget */*widget*/)
{
    QColor fillColor = m_color;
    painter->setBrush(QBrush(fillColor.darker(option->state&QStyle::State_Sunken ? 120 : 100)));
    QPainterPath path = shape();
    painter->drawPath(path);

    painter->save();
    painter->scale(scaleFactor,scaleFactor);
    painter->restore();
}

void CoNodeGraphicsItem::formToolTip(QHash<QString,int> ranks)
{
    QList<QString> kemu = ranks.keys();
    QStringList result;
    foreach(QString ke, kemu)
    {
        if(ranks.value(ke)>0)
            result << ke << QObject::tr("课较上次排名进步;");
        if(ranks.value(ke)<0)
            result << ke << QObject::tr("课较上次排名下降;");
        if(ranks.value(ke)==0)
            result << ke << QObject::tr("课与上次排名相同;");
    }
    QString res = result.join("\n");
    this->setToolTip(res);
}

void CoNodeGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    update();
}

void CoNodeGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
    update();
}

void CoNodeGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}
