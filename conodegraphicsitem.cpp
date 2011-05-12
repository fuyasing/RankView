#include "conodegraphicsitem.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>

CoNodeGraphicsItem::CoNodeGraphicsItem(const QColor color, const int x, const int y, QList<int> ranks)
{
    this->m_dataX = x;
    this->m_dataY = y;
    this->m_color = color;
    this->setFlags(ItemIsSelectable);
    this->setAcceptHoverEvents(true);
    this->formToolTip(ranks);
}

void CoNodeGraphicsItem::addLine(CoLineGraphicsItem *line)
{
}

QList<CoLineGraphicsItem *> CoNodeGraphicsItem::lines()
{
}

QRectF CoNodeGraphicsItem::boundingRect() const
{
    return QRectF(0,0,20,20);
}

QPainterPath CoNodeGraphicsItem::shape() const
{
    QPainterPath path;
    path.addEllipse(0,0,boundingRect().width()/2,boundingRect().height()/2);
    return path;
}

void CoNodeGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget */*widget*/)
{
    QColor fillColor = m_color;
    painter->setBrush(QBrush(fillColor.darker(option->state&QStyle::State_Sunken ? 120 : 100)));
    QPainterPath path = shape();
    painter->drawPath(&path);
}

void CoNodeGraphicsItem::formToolTip(QList<int> ranks)
{
}
