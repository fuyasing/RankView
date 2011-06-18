#include "conodegraphicsitem.h"
#include "colinegraphicsitem.h"
#include "graphics.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QRectF>
#include <QPainterPath>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsWidget>

CoNodeGraphicsItem::CoNodeGraphicsItem()
{
    this->m_dataX = 0;
    this->m_dataY = 0;
    this->m_color = QColor(Qt::black);
    this->m_examName = "";
    this->m_ranks = QHash<QString, int>();
    this->m_lineList = QList<CoLineGraphicsItem *>();
}

CoNodeGraphicsItem::CoNodeGraphicsItem(const QColor color, const QString examName, const int x, const int y, QHash<QString, int> ranks)
{
    this->m_dataX = x;
    this->m_dataY = y * 10 + 50;
    this->m_tRank = y;
    this->setPos(m_dataX, m_dataY);
    this->m_color = color;
    this->m_examName = examName;
    this->m_ranks = ranks;
    this->setFlags(ItemIsSelectable);
    this->setAcceptHoverEvents(true);
    this->setAcceptedMouseButtons(0);
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

    QRectF rankRect(0, -20, 20, 20);
    QRectF textRect(0, 550-m_dataY, 200, 100);
    QFont font = painter->font();
    font.setBold(0);
    font.setPointSize(14);
    painter->setFont(font);
    painter->setPen(Qt::black);
    painter->drawText(rankRect, QString(QString("%1")).arg(m_tRank));
    painter->drawText(textRect, m_examName);

    QLineF line(boundingRect().width()/2, boundingRect().height()/2, boundingRect().width()/2, 550 - m_dataY);
   // QLineF line(m_sourcePoint,m_destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    painter->setPen(QPen(Qt::gray,1,Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);

    painter->save();
    painter->scale(scaleFactor,scaleFactor);
    painter->restore();
}


const QHash<QString, int> CoNodeGraphicsItem::getRanks() const
{
    return m_ranks;
}

void CoNodeGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    emit nodeMouseEnter(m_dataX, m_dataY, m_ranks);
 //   QGraphicsItem::hoverEnterEvent(event);
//    update();
}

void CoNodeGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    emit nodeMouseLeave();
//    QGraphicsItem::hoverLeaveEvent(event);
//    update();
}
