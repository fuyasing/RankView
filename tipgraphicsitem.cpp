#include "tipgraphicsitem.h"

#include <QFont>
#include <QPainter>
#include <QRectF>
#include <QImage>

TipGraphicsItem::TipGraphicsItem(RankHash ranks)
{
    m_ranks = ranks;
}

QRectF TipGraphicsItem::boundingRect() const
{
    return QRectF(0, 0, 100, m_ranks.size()*30);
}

void TipGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QList<QString> kemu = m_ranks.keys();
    QFont font;
    font.setPointSize(20);
    QBrush brush;
    brush.setColor(Qt::black);
    painter->setBackground(brush);
    painter->setBackgroundMode(Qt::OpaqueMode);
    painter->setFont(font);
    painter->setPen(Qt::black);
    QImage image;
    for(int i=0; i<kemu.size(); i++)
    {
        if(m_ranks.value(kemu.at(i))>0)
        {
             painter->drawText(QRectF(0, boundingRect().height()/m_ranks.size()*i, boundingRect().width()/2, boundingRect().height()/m_ranks.size()), kemu.at(i));
             image = QImage(":/images/upRank.png");
          }
        if(m_ranks.value(kemu.at(i))<0)
        {
            painter->drawText(QRectF(0, boundingRect().height()/m_ranks.size()*i, boundingRect().width()/2, boundingRect().height()/m_ranks.size()), kemu.at(i));
            image = QImage(":/images/downRank.png");
        }
        if(m_ranks.value(kemu.at(i))==0)
        {
            painter->drawText(QRectF(0, boundingRect().height()/m_ranks.size()*i, boundingRect().width()/2, boundingRect().height()/m_ranks.size()), kemu.at(i));
            image = QImage(":/images/sameRank.png");
         }
        painter->drawImage(QRectF(boundingRect().width()/2, boundingRect().height()/m_ranks.size()*i, 30, 25), image);
    }
}
