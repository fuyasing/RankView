#ifndef CONODEGRAPHICSITEM_H
#define CONODEGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QColor>
#include <QList>
#include <QHash>

class CoLineGraphicsItem;
class QRectF;
class QPainterPath;
class QPainter;
class QStyleOptionGraphicsItem;
class QGraphicsSceneMouseEvent;

const double scaleFactor = 0.03;

/*! 用于绘制结点的Item封装类
  */
class CoNodeGraphicsItem : public QGraphicsItem
{
public:
    CoNodeGraphicsItem(const QColor color, const int x, const int y, QHash<QString,int> ranks);

    void addLine(CoLineGraphicsItem *line);
    QList<CoLineGraphicsItem *> lines() const;

    enum { Type = UserType + 1 };
    int type() const { return Type; }

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget */*widget*/);

    void formToolTip(QHash<QString,int> ranks);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    int m_dataX, m_dataY;
    QColor m_color;
    QList<CoLineGraphicsItem *> m_lineList;
};

#endif // CONODEGRAPHICSITEM_H
