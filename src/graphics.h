#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QGraphicsView>
#include <QList>

#include "conodegraphicsitem.h"

class QWheelEvent;
class QPainter;
class QRectF;
class QGraphicsScene;
class NodeData;
class TipGraphicsItem;

class Graphics : public QGraphicsView
{
	Q_OBJECT
	public:
		explicit Graphics(QString stdName, QList<NodeData*> nodeList,QWidget *parent = 0);
		~Graphics();

	protected:
		void wheelEvent(QWheelEvent *event);
		void drawBackground(QPainter *painter, const QRectF &rect);

		void scaleView(qreal scaleFactor);
signals:

		public slots:
			//  void ZoomOut(const int value);
			void responseNodeEnter(int posX, int posY, RankHash ranks);
		void responseNodeLeave();

	private:
		void drawGraphics();
		QGraphicsScene *scene;
		QList<NodeData*> m_nodeList;
		TipGraphicsItem* tip;
		QString m_stdName;


};

#endif // GRAPHICS_H
