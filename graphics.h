#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QWidget>

class Graphics : public QWidget
{
    Q_OBJECT
public:
    explicit Graphics(QWidget *parent = 0);

signals:

public slots:
      void ZoomOut(const int value);

private:
      QGraphicsView *graphicsView;
      QGraphicsScene *graphicsScene;


};

#endif // GRAPHICS_H
