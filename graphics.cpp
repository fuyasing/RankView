#include "graphics.h"
#include "conodegraphicsitem.h"
#include "colinegraphicsitem.h"
#include "math.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QHash>
#include <QWheelEvent>
#include <QRectF>
#include <QLinearGradient>
#include <QFont>

Graphics::Graphics(QWidget *parent) :
    QGraphicsView(parent)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    //scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0, 0, 700, 600);
    this->setScene(scene);
    this->setCacheMode(CacheBackground);
    this->setViewportUpdateMode(BoundingRectViewportUpdate);
    this->setRenderHint(QPainter::Antialiasing);
    this->setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(700, 600);
    setWindowTitle(tr("学生成绩趋势统计图"));
    QHash<QString,int> ranks1,ranks2;
    ranks1.insert(tr("语文"),1);
    ranks1.insert(tr("数学"),0);
    ranks1.insert(tr("英语"),-1);
    ranks2.insert(tr("语文"),0);
    ranks2.insert(tr("数学"),-1);
    ranks2.insert(tr("英语"),1);
    CoNodeGraphicsItem *node1 = new CoNodeGraphicsItem(Qt::green,10,10,ranks1);
    CoNodeGraphicsItem *node2 = new CoNodeGraphicsItem(Qt::red,100,100,ranks2);
    CoLineGraphicsItem *line12 = new CoLineGraphicsItem(node1,node2);
    scene->addItem(node1);
    scene->addItem(node2);
    scene->addItem(line12);
}

void Graphics::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}
void Graphics::drawBackground(QPainter *painter, const QRectF &rect)
 {
     Q_UNUSED(rect);

     // Shadow
     QRectF sceneRect = this->sceneRect();
     QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
     QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
     if (rightShadow.intersects(rect) || rightShadow.contains(rect))
         painter->fillRect(rightShadow, Qt::darkGray);
     if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
         painter->fillRect(bottomShadow, Qt::darkGray);

     // Fill
     QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
     gradient.setColorAt(0, Qt::white);
     gradient.setColorAt(1, Qt::lightGray);
     painter->fillRect(rect.intersect(sceneRect), gradient);
     painter->setBrush(Qt::NoBrush);
     painter->drawRect(sceneRect);

     // Text
     QRectF textRect(sceneRect.left() + 4, sceneRect.top() + 4,
                     sceneRect.width() - 4, sceneRect.height() - 4);
     QString message(tr("学生成绩变化趋势示意图"));

     QFont font = painter->font();
     font.setBold(true);
     font.setPointSize(14);
     painter->setFont(font);
     painter->setPen(Qt::lightGray);
     painter->drawText(textRect.translated(2, 2), message);
     painter->setPen(Qt::black);
     painter->drawText(textRect, message);
 }

void Graphics::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}
