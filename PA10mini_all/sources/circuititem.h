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

class QJsonObject;

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
    CircuitItem(const QJsonObject &jo, QGraphicsItem *parent = nullptr);
    ~CircuitItem() override;

    void rotateRight();
    void setPenWidth(qreal width);
    QPoint mapToGrid(QPointF) const;
    int contact(QPointF) const;
    static QRectF contactRect();
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    QString equal() const;
    QString getu() const;
    QString geti() const;
    QString getF() const { return m_f; } //!< Value e.g. resistance, voltage, current
    void setF(const QString &f) { m_f = f; }

    int getId() const;
    void setId(int id) { m_id = id; }
    CircuitElementType elementType() const { return m_elemType; }
    QString fName() const { return m_fName; }
    QString name() const { return m_name; }
    void setFName(const QString & fname) { m_fName = fname; }
    void setName(const QString & name) { m_name = name; }
    //QString getF();
    //void setF(QString);
//implemented virtual functions
    QRectF boundingRect() const override;
    int type() const override;

    QVariant toQVariant() const;
    virtual QJsonObject toJSON() const;
    void fromJSON(const QJsonObject &jo);
    void fromQVariant(const QVariantHash &hash);
    QString fUnit() const { return m_fUnit; }
    void setFUnit(const QString &uName) { m_fUnit = uName; }
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    QString eq;
    QString m_u;
    QString m_i;
    QString m_i0;
    QString m_u0;
    CircuitElementType m_elemType;

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent * event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event) override;

    inline void drawContacts(QPainter* painter);
    inline void contactsShape(QPainterPath& path) const;

//parameters;

//painter pen
    QPen m_pen;

//contacts;
    QVector<QPointF> m_contacts;
    QVector<QPointF> m_contactsStart;
    // QRectF rect;
    QRectF m_mainRect;

private:
    inline QPointF ceilPoint(QPointF point);
    void initItem();

private:
    int m_id;
    QString m_f;
    QString m_fName;
    QString m_fUnit;
    QString m_name;
    bool m_isItemGrabbed;
    int m_contactGrabbed;
    // QPointF center;
};

class CircuitNodeItem : public QGraphicsItem
{
public:
    CircuitNodeItem(int id_, QPointF pos, QGraphicsItem *parent = nullptr);
    ~CircuitNodeItem() override;
    void setGround(bool);
    bool isGrounded() const;
//implemented virtual functions
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    QJsonObject toJSON() const;
    void fromJSON(const QJsonObject &jo);
    int type() const override;
    int getId() const;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    bool m_ground;
    int m_id;

    QPen pen;
};

class RItem : public CircuitItem
{
public:
    RItem(int id, QPointF pos, QGraphicsItem *parent = nullptr);
    QString equal();
    QPainterPath shape() const override;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

class CItem : public CircuitItem
{
public:
    CItem(int id, QPointF pos, QGraphicsItem *parent = nullptr);
    QString equal();
    QPainterPath shape() const override;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

class LItem : public CircuitItem
{
public:
    LItem(int id, QPointF pos, QGraphicsItem *parent = nullptr);
    QString equal();
    QPainterPath shape() const override;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

class GItem : public CircuitItem
{
public:
    GItem(int id, QPointF pos, QGraphicsItem *parent = nullptr);
    QString equal();
    QPainterPath shape() const override;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

class EItem : public CircuitItem
{
public:
    EItem(int id, QPointF pos, QGraphicsItem *parent = nullptr);
    QString equal();
    QPainterPath shape() const override;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

class IItem : public CircuitItem
{
public:
    IItem(int id, QPointF pos, QGraphicsItem *parent = nullptr);
    QString equal();
    QPainterPath shape() const override;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

CircuitItem *CircuitItemFactory(const QString &name, int id, QPointF pos);

QTextStream * operator<<(QTextStream * stream, const CircuitNodeItem & i);
// QTextStream & operator<<(QTextStream & stream, const CircuitNodeItem & i);
QTextStream & operator<<(QTextStream & stream, const CircuitItem & i);
