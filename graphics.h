#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QGraphicsView>

class QWheelEvent;
class QPainter;
class QRectF;
class QGraphicsScene;

class Graphics : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Graphics(QWidget *parent = 0);

protected:
    void wheelEvent(QWheelEvent *event);
    void drawBackground(QPainter *painter, const QRectF &rect);

    void scaleView(qreal scaleFactor);
signals:

public slots:
    //  void ZoomOut(const int value);

private:
      QGraphicsScene *graphicsScene;


};

#endif // GRAPHICS_H
