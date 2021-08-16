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


enum class CircuitElementType {
    R, G, L, C, I, E
};

class CircuitItem : public QGraphicsItem
{
public:
    enum {
        CircuitItemType = QGraphicsItem::UserType + 1,
        CircuitItemNodeType
    };

    CircuitItem(QGraphicsItem *parent = nullptr);
    ~CircuitItem() override;

	void rotateRight();
	void setPenWidth(qreal width);
	QPoint mapToGrid(QPointF);
	int contact(QPointF);
	static QRectF contactRect();

	QString equal();
	QString getu();
	QString geti();

	int getId();
    CircuitElementType elementType() { return elemType; }
	//QString getF();
	//void setF(QString);
//implemented virtual functions
    QRectF boundingRect() const override;
    int type() const override;
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
    CircuitElementType elemType;

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent * event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event) override;

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
    CircuitNodeItem(int id_, QPointF pos, QGraphicsItem *parent = nullptr);
    ~CircuitNodeItem() override;
	void setGround(bool);
	bool isGrounded();
//implemented virtual functions
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    int type() const override;
	int getId();
    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;

private:
	bool ground;
	int id;

	QPen pen;
};

class RItem : CircuitItem
{
public:
    RItem(int id, QPointF pos, QGraphicsItem *parent = nullptr);
	QString equal();
    QPainterPath shape() const override;
    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
};

class CItem : CircuitItem
{
public:
    CItem(int id, QPointF pos, QGraphicsItem *parent = nullptr);
	QString equal();
    QPainterPath shape() const override;
    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
};

class LItem : CircuitItem
{
public:
    LItem(int id, QPointF pos, QGraphicsItem *parent = nullptr);
	QString equal();
    QPainterPath shape() const override;
    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
};

class GItem : CircuitItem
{
public:
    GItem(int id, QPointF pos, QGraphicsItem *parent = nullptr);
	QString equal();
    QPainterPath shape() const override;
    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
};

class EItem : CircuitItem
{
public:
    EItem(int id, QPointF pos, QGraphicsItem *parent = nullptr);
	QString equal();
    QPainterPath shape() const override;
    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
};

class IItem : CircuitItem
{
public:
    IItem(int id, QPointF pos, QGraphicsItem *parent = nullptr);
	QString equal();
    QPainterPath shape() const override;
    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
};
