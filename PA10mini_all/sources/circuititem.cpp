#include "circuititem.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStyleOptionGraphicsItem>

CircuitItem::CircuitItem(QGraphicsItem * parent)
    : QGraphicsItem(parent)
{
    initItem();
}

void CircuitItem::initItem()
{
    setFlags(ItemIsSelectable | ItemIsMovable | ItemIsFocusable | ItemIsFocusable);
    m_isItemGrabbed = false;
    m_contactGrabbed = -1;

    m_u = "u";
    m_i = "i";
    m_i0 = "0";
    m_u0 = "0";

    //painter
    m_pen.setWidthF(0.03);
    m_pen.setJoinStyle(Qt::RoundJoin);
    m_pen.setCapStyle(Qt::RoundCap);

    //contacts
    m_contacts << QPointF(-1.0, 0.0);
    m_contacts << QPointF(1.0, 0.0);
    m_mainRect.setRect(-1.0,-0.5,+2.0,+1.0);
    //bounding rect
    for (int i = 0; i < m_contacts.size(); ++i)
    {
        m_contactsStart << m_contacts[i];
        // rect = rect.united(contactRect().translated(contacts[i]).adjusted(-0.5,-0.5,+0.5,+0.5));
    }
    setAcceptHoverEvents(true);
    setZValue(1.0);
}

CircuitItem::CircuitItem(const QJsonObject &jo, QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    initItem();
    fromJSON(jo);
}

CircuitItem::~CircuitItem()
{

}

int CircuitItem::type() const
{
    return CircuitItemType;
}

QRectF CircuitItem::boundingRect(void) const
{
    QRectF rect;

    rect = shape().boundingRect();
    rect = rect.united(m_mainRect);

    return rect;
}

void CircuitItem::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{
    if (event->button() == Qt::LeftButton) {
        setCursor(Qt::ClosedHandCursor);
        m_contactGrabbed = contact(event->scenePos());
        if (m_contactGrabbed == -1) {
            m_isItemGrabbed = true;
        }
    }

}

void CircuitItem::mouseMoveEvent ( QGraphicsSceneMouseEvent * event )
{
    if (m_contactGrabbed != -1) {
        m_contacts[m_contactGrabbed] += mapFromScene(event->scenePos().toPoint()) - mapFromScene(event->lastScenePos().toPoint());
        // rect = shape().boundingRect();
        // rect = rect.united(mainRect);
        prepareGeometryChange();
        QGraphicsView* a = scene()->views().last();
        static_cast<SchemeView*>(a)->checkgrid();
    } else if (m_isItemGrabbed) {
        QPointF d = event->scenePos().toPoint() - event->lastScenePos().toPoint();
        moveBy(d.x(), d.y());
        QGraphicsView* a = scene()->views().last();
        static_cast<SchemeView*>(a)->checkgrid();
    }
}

void CircuitItem::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )
{
    Q_UNUSED(event)
    if (m_isItemGrabbed) {
        setCursor(Qt::ArrowCursor);
        m_isItemGrabbed = false;
        QGraphicsView* a = scene()->views().last();
        static_cast<SchemeView*>(a)->checkgrid();
    }
    if (m_contactGrabbed != -1) {
        setCursor(Qt::ArrowCursor);
        m_contactGrabbed = -1;
        //after changing shape
        prepareGeometryChange();
        QGraphicsView* a = scene()->views().last();
        static_cast<SchemeView*>(a)->checkgrid();
    }
}

void CircuitItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    setCursor(Qt::OpenHandCursor);

    QGraphicsItem::hoverEnterEvent(event);
}

void CircuitItem::rotateRight()
{
    setRotation(rotation() + 90);
}

QPointF CircuitItem::ceilPoint(QPointF point)
{
    auto a = point.x();
    auto b = point.y();
    return QPointF((point.x() < 0) ? a - 1 : a, (point.y() < 0) ? b - 1 : b);
}

QPoint CircuitItem::mapToGrid(QPointF) const
{
    return QPoint(0,0);
}

void CircuitItem::setPenWidth(qreal width)
{
    Q_UNUSED(width)
}

QRectF CircuitItem::contactRect()
{
    return QRectF(-0.05, -0.05, 0.1, 0.1);
}

void CircuitItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if ((option->state & QStyle::State_Selected) || isSelected()) {
        m_pen.setWidthF(0.06);
        // m_pen.setStyle();
    } else {
        m_pen.setWidthF(0.03);
    }
}

int CircuitItem::contact(QPointF pos) const
{
    for (int i = 0; i < m_contacts.size(); ++i)
        if (contactRect().translated(m_contacts[i]).contains(mapFromScene(pos)))
            return i;
    return -1;
}

void CircuitItem::drawContacts(QPainter* painter)
{
    for (int i = 0; i < m_contacts.size(); ++i)
    {
        if (m_contactsStart[i].x() < m_contacts[i].x() && i == 0)
        {
            painter->drawLine(QLineF(m_contactsStart[i].x(), m_contacts[i].y(), m_contactsStart[i].x(), m_contactsStart[i].y()));
            painter->drawLine(QLineF(m_contactsStart[i].x(), m_contacts[i].y(), m_contacts[i].x(), m_contacts[i].y()));
        }
        else if (m_contactsStart[i].x() > m_contacts[i].x() && i == 1)
        {
            painter->drawLine(QLineF(m_contactsStart[i].x(), m_contacts[i].y(), m_contactsStart[i].x(), m_contactsStart[i].y()));
            painter->drawLine(QLineF(m_contactsStart[i].x(), m_contacts[i].y(), m_contacts[i].x(), m_contacts[i].y()));
        }
        else
        {
            painter->drawLine(QLineF(m_contactsStart[i].x(), m_contactsStart[i].y(), m_contacts[i].x(), m_contactsStart[i].y()));
            painter->drawLine(QLineF(m_contacts[i].x(), m_contactsStart[i].y(), m_contacts[i].x(), m_contacts[i].y()));
        }
        painter->fillRect(contactRect().translated(m_contacts[i]), Qt::black);
    }

    qreal scale = 14;
    QFont font = painter->font();
    font.setPointSizeF(2);
    painter->setFont(font);
    painter->scale(1 / scale, 1 / scale);
    painter->drawText(QRectF(-scale * 0.5, -scale * 0.5, scale * 1.0, scale * 0.2), Qt::AlignCenter, getF());
    painter->drawText(QRectF(-scale * 0.5, scale * 0.3, scale * 1.0, scale * 0.2), Qt::AlignCenter, m_name);
}

void CircuitItem::contactsShape(QPainterPath& path) const
{
    for (int i = 0; i < m_contacts.size(); ++i)
        path.addRect(contactRect().translated(m_contacts[i]));
}

QVariant CircuitItem::toQVariant() const
{
    qDebug() << "Save CircuitItem #" << int(elementType()) << " name:" << m_name;

    QVariantHash hash;

    hash["x"] = x();
    hash["y"] = y();

    return hash;
}

QJsonObject CircuitItem::toJSON() const
{
    QJsonObject jitem;
    QJsonArray contactArray;

    jitem["type"] = "CircuitItem";
    jitem["x"] = x();
    jitem["y"] = y();
    jitem["id"] = getId();
    jitem["fName"] = m_fName;
    jitem["name"] = m_name;
    jitem["rot"] = rotation();
    jitem["value"] = getF();

    //for (auto contact : contacts) {
    for (int i = 0; i < m_contacts.size(); ++i) {
        QJsonObject contactItem;
        contactItem["x"] = m_contacts[i].x();
        contactItem["y"] = m_contacts[i].y();
        contactItem["id"] = i;
        contactArray.append(contactItem);
    }

    jitem["contacts"] = contactArray;

    return jitem;
}

void CircuitItem::fromJSON(const QJsonObject &jo)
{
    if (jo["type"] != "CircuitItem")
        return;

    setX(jo["x"].toDouble());
    setY(jo["y"].toDouble());
    m_fName = jo["fName"].toString();
    m_name = jo["name"].toString();
    m_id = jo["id"].toInt();
    setRotation(jo["rot"].toDouble());
    setF(jo["value"].toString());

    QJsonArray contactArray = jo["contacts"].toArray();
    for (int i = 0; i < contactArray.size(); ++i) {
        int id = contactArray[i].toObject()["id"].toInt();
        QPointF p(contactArray[i].toObject()["x"].toDouble(), contactArray[i].toObject()["y"].toDouble());
        m_contacts[id] = p;
    }
}

void CircuitItem::fromQVariant(const QVariantHash &hash)
{
    qDebug() << "Load CircuitItem #" << int(elementType()) << " name:" << m_name;

    setX(hash["x"].toDouble());
    setY(hash["y"].toDouble());
}

QJsonObject CircuitNodeItem::toJSON() const
{
    QJsonObject jitem;

    jitem["type"] = "CircuitNodeItem";
    jitem["x"] = x();
    jitem["y"] = y();
    jitem["id"] = m_id;
    jitem["ground"] = m_ground;

    return jitem;
}

void CircuitNodeItem::fromJSON(const QJsonObject &jo)
{
    if (jo["type"] != "CircuitNodeItem")
        return;

    setX(jo["x"].toDouble());
    setY(jo["y"].toDouble());
    m_id = jo["id"].toInt();
    m_ground = jo["ground"].toBool();
}

//paint implementation for circuit elements

void RItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Q_UNUSED(option)
    // Q_UNUSED(widget)
    CircuitItem::paint(painter, option, widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(m_pen);
    //resistance
    painter->drawRect(QRectF(-0.3, -0.15, 0.6, 0.3));
    painter->drawLine(QLineF(-1.0, 0.0, -0.3, 0.0));
    painter->drawLine(QLineF(0.3, 0.0, 1.0, 0.0));

    drawContacts(painter);
}

QPainterPath RItem::shape() const
{
    QPainterPath path;
    path.addRect(QRectF(-0.3, -0.15, 0.6, 0.3));

    contactsShape(path);
    return path;
}

void CItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Q_UNUSED(option)
    // Q_UNUSED(widget)
    CircuitItem::paint(painter, option, widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(m_pen);
    //capacitor
    painter->drawLine(QLineF(-1.0, 0.0, -0.1, 0.0));
    painter->drawLine(QLineF(0.1, 0.0, 1.0, 0.0));

    painter->drawLine(QLineF(-0.1, -0.2, -0.1, 0.2));
    painter->drawLine(QLineF(0.1, -0.2, 0.1, 0.2));

    drawContacts(painter);
}

QPainterPath CItem::shape() const
{
    QPainterPath path;
    path.addRect(QRectF(-0.3, -0.3, 0.6, 0.6));

    contactsShape(path);
    return path;
}

void LItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Q_UNUSED(option)
    // Q_UNUSED(widget)

    CircuitItem::paint(painter, option, widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(m_pen);
    //inductance
    painter->drawLine(QLineF(-1.0, 0.0, -0.4, 0.0));
    painter->drawLine(QLineF(0.4, 0.0, 1.0, 0.0));

    painter->drawArc(QRectF(-0.4, -0.1, 0.2, 0.2), 0*16, 180*16);
    painter->drawArc(QRectF(-0.2, -0.1, 0.2, 0.2), 0*16, 180*16);
    painter->drawArc(QRectF(0.0, -0.1, 0.2, 0.2), 0*16, 180*16);
    painter->drawArc(QRectF(0.2, -0.1, 0.2, 0.2), 0*16, 180*16);

    drawContacts(painter);
}

QPainterPath LItem::shape() const
{
    QPainterPath path;
    path.addRect(QRectF(-0.4, -0.2, 0.8, 0.4));

    contactsShape(path);
    return path;
}


void GItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Q_UNUSED(option)
    // Q_UNUSED(widget)
    CircuitItem::paint(painter, option, widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(m_pen);
    //conduction
    painter->drawRect(QRectF(-0.3, -0.15, 0.6, 0.3));
    painter->drawLine(QLineF(-1.0, 0.0, -0.3, 0.0));
    painter->drawLine(QLineF(0.3, 0.0, 1.0, 0.0));

    painter->drawLine(QLineF(-0.3, -0.15, 0.3, 0.15));
    painter->drawLine(QLineF(-0.3, 0.15, 0.3, -0.15));

    drawContacts(painter);
}

QPainterPath GItem::shape() const
{
    QPainterPath path;
    path.addRect(QRectF(-0.3, -0.15, 0.6, 0.3));

    contactsShape(path);
    return path;
}

void EItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Q_UNUSED(option)
    // Q_UNUSED(widget)
    CircuitItem::paint(painter, option, widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(m_pen);
    //voltage

    painter->drawLine(QLineF(-1.0, 0.0, 1.0, 0.0));

    painter->drawEllipse(QRectF(-0.25, -0.25, 0.5, 0.5));

    painter->drawLine(QLineF(-0.05, -0.1, -0.2, 0.0));
    painter->drawLine(QLineF(-0.05, 0.1, -0.2, 0.0));

    drawContacts(painter);
}

QPainterPath EItem::shape() const
{
    QPainterPath path;
    path.addEllipse(QRectF(-0.25, -0.25, 0.5, 0.5));

    contactsShape(path);
    return path;
}

void IItem::paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    // Q_UNUSED(option)
    // Q_UNUSED(widget)
    CircuitItem::paint(painter, option, widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(m_pen);
    //current

    painter->drawLine(QLineF(-1.0, 0.0, 1.0, 0.0));

    painter->drawEllipse(QRectF(-0.25, -0.25, 0.5, 0.5));

    painter->drawLine(QLineF(-0.15, -0.1, 0.0, 0.0));
    painter->drawLine(QLineF(0.0, 0.0, -0.15, 0.1));

    painter->drawLine(QLineF(0.05, -0.1, 0.2, 0.0));
    painter->drawLine(QLineF(0.2, 0.0, 0.05, 0.1));

    drawContacts(painter);
}

QPainterPath IItem::shape() const
{
    QPainterPath path;
    path.addEllipse(QRectF(-0.25, -0.25, 0.5, 0.5));

    contactsShape(path);
    return path;
}

int CircuitItem::getId() const
{
    return m_id;
}

QString CircuitItem::equal() const
{
    QString tmp = eq;
    tmp.replace("u", getU());
    tmp.replace("i", getI());
    tmp.replace("f", getF());
    return tmp;
}

QString CircuitItem::getU() const
{
    return m_u + m_name;
}

QString CircuitItem::getI() const
{
    return m_i + m_name;
}

QString CircuitItem::getI0() const
{
    return m_i0;
}

QString CircuitItem::getU0() const
{
    return m_u0;
}

RItem::RItem(int id_, QPointF pos_, QGraphicsItem *parent)
    : CircuitItem(parent)
{
    setId(id_);
    setName("R" + QString::number(id_));
    eq = "u=i*f";
    setF("1.0");
    setFUnit("Ohm");
    setFName("R");
    m_elemType = CircuitElementType::R;
    setPos(pos_);
}

GItem::GItem(int id_, QPointF pos_, QGraphicsItem *parent)
    : CircuitItem(parent)
{
    setId(id_);
    setName("G" + QString::number(id_));
    eq = "i=u*f";
    setF("1.0");
    setFUnit("Si");
    setFName("G");
    m_elemType = CircuitElementType::G;
    setPos(pos_);
}

CItem::CItem(int id_, QPointF pos_, QGraphicsItem *parent)
    : CircuitItem(parent)
{
    setId(id_);
    setName("C" + QString::number(id_));
    eq = "i=u'*f";
    setF("1.0");
    setFUnit("F");
    setFName("C");
    m_elemType = CircuitElementType::C;
    setPos(pos_);
}

LItem::LItem(int id_, QPointF pos_, QGraphicsItem *parent)
    : CircuitItem(parent)
{
    setId(id_);
    setName("L" + QString::number(id_));
    eq = "u=i'*f";
    setF("1.0");
    setFUnit("H");
    setFName("L");
    m_elemType = CircuitElementType::L;
    setPos(pos_);
}

IItem::IItem(int id_, QPointF pos_, QGraphicsItem *parent)
    : CircuitItem(parent)
{
    setId(id_);
    setName("I" + QString::number(id_));
    eq = "i=f";
    setF("1.0");
    setFUnit("A");
    setFName("I");
    m_elemType = CircuitElementType::I;
    setPos(pos_);
}

EItem::EItem(int id_, QPointF pos_, QGraphicsItem *parent)
    : CircuitItem(parent)
{
    setId(id_);
    setName("E" + QString::number(id_));
    eq = "u=f";
    setF("1.0");
    setFUnit("V");
    setFName("E");
    m_elemType = CircuitElementType::E;
    setPos(pos_);
}

//CircuitNodeItem
CircuitNodeItem::CircuitNodeItem(int id_, QPointF pos, QGraphicsItem *parent)
        : QGraphicsItem(parent)
{
    setPos(pos);
//painter
    pen.setWidthF(0.03);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setCapStyle(Qt::RoundCap);
    m_ground = false;
    m_id = id_;
    setZValue(2.0);
}

CircuitNodeItem::~CircuitNodeItem()
{

}

void CircuitNodeItem::setGround(bool ground_)
{
    m_ground = ground_;
    update();
}

QRectF CircuitNodeItem::boundingRect() const
{
    return QRectF(-0.5, -0.5, 1.5, 1.5);
}

QPainterPath CircuitNodeItem::shape() const
{
    QPainterPath path;
    path.addRect(CircuitItem::contactRect().adjusted(-0.1, -0.1, 0.1, 0.1));
    return path;
}

void CircuitNodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(pen);
    painter->drawRect(CircuitItem::contactRect().adjusted(-0.1, -0.1, 0.1, 0.1));
    if (m_ground)
    {   // Draw ground sign
        painter->drawLine(QLineF(0.0, 0.0, 0.5, 0.4));
        painter->drawLine(QLineF(0.5, 0.4, 0.5, 0.8));
        painter->drawLine(QLineF(0.2, 0.55, 0.8, 0.55));
        painter->drawLine(QLineF(0.3, 0.65, 0.7, 0.65));
        painter->drawLine(QLineF(0.4, 0.75, 0.6, 0.75));
    }
    qreal scale = 14;
    QFont font = painter->font();
    font.setPointSizeF(2);
    painter->setFont(font);
    painter->scale(1 / scale, 1 / scale);
    painter->drawText(QRectF(-scale * 0.4, -scale * 0.4, scale * 0.4, scale * 0.2),
                      Qt::AlignCenter, QString::number(m_id));
}

int CircuitNodeItem::type() const
{
    return CircuitItem::CircuitItemNodeType;
}

int CircuitNodeItem::getId() const
{
    return m_id;
}

bool CircuitNodeItem::isGrounded() const
{
    return m_ground;
}

CircuitItem *CircuitItemFactory(const QString &name, int id, QPointF pos)
{
    if (name.compare("R", Qt::CaseInsensitive) == 0) {
        return new RItem(id, pos);
    } else if (name.compare("L", Qt::CaseInsensitive) == 0) {
        return new LItem(id, pos);
    } else if (name.compare("C", Qt::CaseInsensitive) == 0) {
        return new CItem(id, pos);
    } else if (name.compare("E", Qt::CaseInsensitive) == 0) {
        return new EItem(id, pos);
    } else if (name.compare("I", Qt::CaseInsensitive) == 0) {
        return new IItem(id, pos);
    } else if (name.compare("G", Qt::CaseInsensitive) == 0) {
        return new GItem(id, pos);
    } else {
        return nullptr;
    }
}

QTextStream * operator<<(QTextStream * stream, const CircuitNodeItem & i)
{
    qDebug() << "Save CircuitNodeItem #" << i.getId();
    *stream << i.type();
    *stream << i.x();
    *stream << i.y();
    *stream << i.boundingRect().x();
    *stream << i.boundingRect().y();
    *stream << i.boundingRect().width();
    *stream << i.boundingRect().height();
    *stream << i.isGrounded();
    
    return stream;
}

QTextStream & operator<<(QTextStream & stream, const CircuitItem & i)
{
    qDebug() << "Save CircuitItem #" << int(i.elementType()) << " name:" << i.name();
    stream << i.type();
    stream << int(i.elementType());
    stream << i.x();
    stream << i.y();
    stream << i.boundingRect().x();
    stream << i.boundingRect().y();
    stream << i.boundingRect().width();
    stream << i.boundingRect().height();
    
    return stream;
}
