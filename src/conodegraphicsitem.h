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
typedef QHash<QString, int> RankHash;

/*! 用于绘制结点的Item封装类
  */
class CoNodeGraphicsItem : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    CoNodeGraphicsItem();
    CoNodeGraphicsItem(const QColor color, const QString examName, const int x, const int y, QHash<QString,int> ranks);

    void addLine(CoLineGraphicsItem *line);
    QList<CoLineGraphicsItem *> lines() const;

    enum { Type = UserType + 1 };
    int type() const { return Type; }

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget */*widget*/);

    const QHash<QString, int> getRanks() const;

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

signals:
    void nodeMouseEnter(int posX, int posY, RankHash ranks);
    void nodeMouseLeave();

private:
    int m_dataX, m_dataY, m_tRank;
    QColor m_color;
    QString m_examName;
    QHash<QString, int> m_ranks;
    QList<CoLineGraphicsItem *> m_lineList;
};

#endif // CONODEGRAPHICSITEM_H
