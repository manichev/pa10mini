#pragma once

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QCursor>
#include <QRectF>
#include <QDebug>
#include <QMenu>

#include "schemeview.h"

enum	{	CircuitItemType = QGraphicsItem::UserType+1,
			CircuitItemNodeType 
		};

enum ElementType	{
		R, G, L, C, I, E
	};

class CircuitItem : public QGraphicsItem
{
public:

	CircuitItem(QGraphicsItem *parent = 0);
	~CircuitItem();

	void rotateRight();
	void setPenWidth(qreal width);
	QPoint mapToGrid(QPointF);
	int contact(QPointF);
	static QRectF contactRect();

	QString equal();
	QString getu();
	QString geti();

	int getId();
	ElementType elementType() {return elemType;};
	//QString getF();
	//void setF(QString);
//implemented virtual functions
	QRectF boundingRect()  const;
	int type() const;
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	QString fDim;
	QString fName;
	QString name;
	QString eq;
	QString f;
	QString u;
	QString i;
	QString i0;
	QString u0;
	ElementType elemType;

protected:
	void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
	void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );
	void mousePressEvent ( QGraphicsSceneMouseEvent * event );
	void mouseReleaseEvent ( QGraphicsSceneMouseEvent * event );

	inline void drawContacts(QPainter* painter);
	inline void contactsShape(QPainterPath& path) const;

//parameters;
	int id;

//painter pen
	QPen pen;

//contacts;
	QVector<QPointF> contacts;
	QVector<QPointF> contactsStart;
	QRectF rect;
	QRectF mainRect;

private:
	inline QPointF ceilPoint(QPointF point);

	bool isItemGrabbed;
	int contactGrabbed;
	QPointF center;
};

class CircuitNodeItem : public QGraphicsItem
{
public:
	CircuitNodeItem(int id_, QPointF pos, QGraphicsItem *parent = 0);
	~CircuitNodeItem();
	void setGround(bool);
	bool isGrounded();
//implemented virtual functions
	QRectF boundingRect()  const;
	QPainterPath shape() const;
	int type() const;
	int getId();
	void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);

private:
	bool ground;
	int id;

	QPen pen;
};

class RItem : CircuitItem
{
public:
	RItem(int id, QPointF pos, QGraphicsItem *parent = 0);
	QString equal();
	QPainterPath shape() const;
	void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
};

class CItem : CircuitItem
{
public:
	CItem(int id, QPointF pos, QGraphicsItem *parent = 0);
	QString equal();
	QPainterPath shape() const;
	void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
};

class LItem : CircuitItem
{
public:
	LItem(int id, QPointF pos, QGraphicsItem *parent = 0);
	QString equal();
	QPainterPath shape() const;
	void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
};

class GItem : CircuitItem
{
public:
	GItem(int id, QPointF pos, QGraphicsItem *parent = 0);
	QString equal();
	QPainterPath shape() const;
	void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
};

class EItem : CircuitItem
{
public:
	EItem(int id, QPointF pos, QGraphicsItem *parent = 0);
	QString equal();
	QPainterPath shape() const;
	void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
};

class IItem : CircuitItem
{
public:
	IItem(int id, QPointF pos, QGraphicsItem *parent = 0);
	QString equal();
	QPainterPath shape() const;
	void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
};