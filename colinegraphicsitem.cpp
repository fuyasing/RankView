#include "colinegraphicsitem.h"
#include "conodegraphicsitem.h"

#include <QPainter>
#include <QPen>

CoLineGraphicsItem::CoLineGraphicsItem(CoNodeGraphicsItem *sourceNode, CoNodeGraphicsItem *destNode)
{
    this->setAcceptedMouseButtons(0);
    this->setAcceptHoverEvents(0);
    m_source = sourceNode;
    m_dest = destNode;
    m_sourcePoint = m_source->pos();
    m_destPoint = m_dest->pos();
    m_source->addLine(this);
    m_dest->addLine(this);
}

CoNodeGraphicsItem* CoLineGraphicsItem::sourceNode() const
{
    return m_source;
}

CoNodeGraphicsItem* CoLineGraphicsItem::destNode() const
{
    return m_dest;
}

QRectF CoLineGraphicsItem::boundingRect() const
{
    if(!m_source || !m_dest)
        return QRectF();
    return QRectF(m_sourcePoint,QSizeF(abs(m_source->x()-m_dest->x()),abs(m_source->y()-m_dest->y())));
}

void CoLineGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!m_source || !m_dest)
        return;

    QLineF line(m_sourcePoint.x()+m_source->boundingRect().width()/2,m_sourcePoint.y()+m_source->boundingRect().height()/2,m_destPoint.x()+m_dest->boundingRect().width()/2, m_destPoint.y()+m_dest->boundingRect().height()/2);
   // QLineF line(m_sourcePoint,m_destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    painter->setPen(QPen(Qt::black,1,Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);
    painter->save();
    painter->scale(scaleFactor, scaleFactor);
    painter->restore();
}
/*void CoLineGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverEnterEvent(event);
    //update();
}

void CoLineGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverLeaveEvent(event);
    //update();
}*/
