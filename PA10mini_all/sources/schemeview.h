#ifndef PVIEW_H
#define PVIEW_H

#include <QGraphicsView>
#include <QGraphicsItemGroup>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QScrollBar>
#include <QApplication>
#include <QList>
#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QLabel>
#include <QPixmap>


#include "circuititemedit.h"
#include "circuititem.h"

class CircuitItem;
class CircuitNodeItem;
enum ElementType;

class SchemeView : public QGraphicsView
{
	Q_OBJECT

public:
	SchemeView(QWidget *parent = 0);
	~SchemeView();

	void checkgrid();

public slots:
	QString getSystem();
	void rotateItem();
	void groundNode();
	void ungroundNode();
	void editCircuitItem();

	void deleteItem();

	//add slots
	void addR();
	void addG();
	void addL();
	void addC();
	void addU();
	void addI();

protected:
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent ( QMouseEvent * event );
    void wheelEvent ( QWheelEvent * event );
    void enterEvent (QEvent* event);
    void leaveEvent (QEvent* event);

private:
	bool eventFilter(QObject *target, QEvent *event);
	inline qreal getScale();
	inline qreal fullScale();
	void setScale (qreal s);
	int recieveElementId(ElementType type);
	void addNode(QPointF pos);

	int gridW;
	int gridH;

	bool isGrabbed;
	bool isScaled;
	QPoint	lastMousePos;
	qreal scaleStep;

	QList<CircuitNodeItem*> nodes;
	QList<CircuitItem*> elements;
	QGraphicsItem* hoveredItem;

	QMenu* itemMenu;
	QMenu* nodeMenu;
	QMenu* mainMenu;
};

#endif // PVIEW_H
