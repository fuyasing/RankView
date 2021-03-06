#ifndef COLINEGRAPHICSITEM_H
#define COLINEGRAPHICSITEM_H

#include <QGraphicsItem>

class CoNodeGraphicsItem;

/*! 用于绘制结点之间连线的Item封装类
  */
class CoLineGraphicsItem : public QGraphicsItem
{
public:
    CoLineGraphicsItem(CoNodeGraphicsItem *sourceNode, CoNodeGraphicsItem *destNode);
    CoNodeGraphicsItem *sourceNode() const;
    CoNodeGraphicsItem *destNode() const;

    enum { Type = UserType + 2 };
    int type() const { return Type; }

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    //void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    //void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
    CoNodeGraphicsItem *m_source, *m_dest;

    QPointF m_sourcePoint, m_destPoint;
};

#endif // COLINEGRAPHICSITEM_H
