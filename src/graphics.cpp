#include "graphics.h"
#include "colinegraphicsitem.h"
#include "tipgraphicsitem.h"
#include "math.h"
#include "nodedata.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QHash>
#include <QWheelEvent>
#include <QRectF>
#include <QLinearGradient>
#include <QFont>
#include <QtAlgorithms>
#include <QGraphicsLineItem>

Graphics::Graphics(QString stdName, QList<NodeData*> nodeList,QWidget *parent) :
	QGraphicsView(parent)
{
	m_nodeList = nodeList;
	m_stdName = stdName;
	drawGraphics();
}
Graphics::~Graphics()
{
	qDeleteAll(m_nodeList.begin(),m_nodeList.end());
}

void Graphics::wheelEvent(QWheelEvent *event)
{
	scaleView(pow((double)2, event->delta() / 240.0));
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
	QRectF textRect(sceneRect.left() + 100, sceneRect.top() + 4,
			sceneRect.width() - 100, sceneRect.height() - 4);
	QString message(tr("%1\'s Score Rank Trend").arg(m_stdName));

	QFont font = painter->font();
	font.setBold(true);
	font.setPointSize(35);
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

void Graphics::drawGraphics()
{
	scene = new QGraphicsScene(this);
	//scene->setItemIndexMethod(QGraphicsScene::NoIndex);
	scene->setSceneRect(0, 0, 900, 600);
	this->setScene(scene);
	this->setCacheMode(CacheBackground);
	this->setViewportUpdateMode(BoundingRectViewportUpdate);
	this->setRenderHint(QPainter::Antialiasing);
	this->setTransformationAnchor(AnchorUnderMouse);
	this->scale(qreal(0.8), qreal(0.8));
	this->setMinimumSize(900, 600);
	this->setWindowTitle(tr("Student's Score Rank Trend"));


	double everyLength = (scene->width() - scene->width()/5 - scene->width()/20)/(m_nodeList.size() - 1);
	CoNodeGraphicsItem* node;
	CoLineGraphicsItem* line;
	QList<CoNodeGraphicsItem *> nodeItems;
	for(int i=0;i<m_nodeList.size();i++)
	{
		node = new CoNodeGraphicsItem(Qt::blue, m_nodeList.at(i)->examName(), int(scene->width()/10 + i*everyLength), m_nodeList.at(i)->rank(), m_nodeList.at(i)->subjectTrend());
		connect(node, SIGNAL(nodeMouseEnter(int, int, RankHash)), this, SLOT(responseNodeEnter(int, int, RankHash)));
		connect(node, SIGNAL(nodeMouseLeave()), this, SLOT(responseNodeLeave()));
		scene->addItem(node);
		nodeItems.append(node);
	}

	for(int i=0; i<nodeItems.size()-1; i++)
	{
		line = new CoLineGraphicsItem(nodeItems.at(i), nodeItems.at(i+1));
		scene->addItem(line);
	}
	QGraphicsLineItem *lateralAxis = new QGraphicsLineItem(scene->width()/10 - 20, 550, scene->width()*9/10 + 40, 550);
	scene->addItem(lateralAxis);
	QGraphicsLineItem *verticalAxis = new QGraphicsLineItem(scene->width()/10 -20, 70, scene->width()/10 -20, 550);
	scene->addItem(verticalAxis);
}

void Graphics::responseNodeEnter(int posX, int posY, RankHash ranks)
{
	tip = new TipGraphicsItem(ranks);
	if(posX + tip->boundingRect().width() > scene->width())
		posX = posX - tip->boundingRect().width();
	else
		posX = posX + 20;
	if(posY + tip->boundingRect().height() > 550)
		posY = posY - tip->boundingRect().height()*3/4;
	else if(posY - tip->boundingRect().height()/2 > 50 && posY + tip->boundingRect().height()/2 <= 550)
		posY = posY - tip->boundingRect().height()/2;
	tip->setPos(posX, posY);
	scene->addItem(tip);
}
void Graphics::responseNodeLeave()
{
	tip->setVisible(0);
	delete tip;
}
