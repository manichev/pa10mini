#include "circuititem.h"

CircuitItem::CircuitItem(QGraphicsItem * parent)
    : QGraphicsItem(parent)
{
    isItemGrabbed = false;
    contactGrabbed = -1;

    u = "u";
    i = "i";
    i0 = "0";
    u0 = "0";

    //painter
    pen.setWidthF(0.03);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setCapStyle(Qt::RoundCap);

    //contacts
    contacts << QPointF(-1.0, 0.0);
    contacts << QPointF(1.0, 0.0);
    mainRect.setRect(-1.0,-0.5,+2.0,+1.0);
    //bounding rect
    for(int i = 0; i < contacts.size(); ++i)
    {
        contactsStart << contacts[i];
        rect = rect.united(contactRect().translated(contacts[i]).adjusted(-0.5,-0.5,+0.5,+0.5));
    }
    setAcceptHoverEvents(true);
    setZValue(1.0);
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
    return rect;
}

void CircuitItem::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{
    if(event->button() == Qt::LeftButton)
    {
        setCursor(Qt::ClosedHandCursor);
        contactGrabbed = contact(event->scenePos());
        if(contactGrabbed == -1)
        {
            isItemGrabbed = true;
        }
    }

}

void CircuitItem::mouseMoveEvent ( QGraphicsSceneMouseEvent * event )
{
    if(isItemGrabbed)
    {
        QPointF d = event->scenePos().toPoint() - event->lastScenePos().toPoint();
        moveBy(d.x(), d.y());
            QGraphicsView* a = scene()->views().last();
    static_cast<SchemeView*>(a)->checkgrid();
    }
    if(contactGrabbed != -1)
    {
        contacts[contactGrabbed] += mapFromScene(event->scenePos().toPoint()) - mapFromScene(event->lastScenePos().toPoint());
        rect = shape().boundingRect() ;
        rect = rect.united(mainRect);
        prepareGeometryChange();
            QGraphicsView* a = scene()->views().last();
    static_cast<SchemeView*>(a)->checkgrid();
    }
}

void CircuitItem::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )
{
    Q_UNUSED(event)
    if(isItemGrabbed)
    {
        setCursor(Qt::ArrowCursor);
        isItemGrabbed = false;
        QGraphicsView* a = scene()->views().last();
        static_cast<SchemeView*>(a)->checkgrid();
    }
    if(contactGrabbed != -1)
    {
        setCursor(Qt::ArrowCursor);
        contactGrabbed = -1;
        //after changing shape
        prepareGeometryChange();
        QGraphicsView* a = scene()->views().last();
        static_cast<SchemeView*>(a)->checkgrid();
    }
}

void CircuitItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    Q_UNUSED(event)

    setCursor(Qt::OpenHandCursor);
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

QPoint CircuitItem::mapToGrid(QPointF)
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

int CircuitItem::contact(QPointF pos)
{
    for(int i = 0; i < contacts.size(); ++i)
    if(contactRect().translated(contacts[i]).contains(mapFromScene(pos)))
        return i;
    return -1;
}

void CircuitItem::drawContacts(QPainter* painter)
{
    for(int i = 0; i < contacts.size(); ++i)
    {
        if(contactsStart[i].x() < contacts[i].x() && i == 0)
        {
            painter->drawLine(QLineF(contactsStart[i].x(), contacts[i].y(), contactsStart[i].x(), contactsStart[i].y()));
            painter->drawLine(QLineF(contactsStart[i].x(), contacts[i].y(), contacts[i].x(), contacts[i].y()));
        }
        else    if(contactsStart[i].x() > contacts[i].x() && i == 1)
        {
            painter->drawLine(QLineF(contactsStart[i].x(), contacts[i].y(), contactsStart[i].x(), contactsStart[i].y()));
            painter->drawLine(QLineF(contactsStart[i].x(), contacts[i].y(), contacts[i].x(), contacts[i].y()));
        } else
        {
            painter->drawLine(QLineF(contactsStart[i].x(), contactsStart[i].y(), contacts[i].x(), contactsStart[i].y()));
            painter->drawLine(QLineF(contacts[i].x(), contactsStart[i].y(), contacts[i].x(), contacts[i].y()));
        }
        painter->fillRect(contactRect().translated(contacts[i]), Qt::black);
    }

    qreal scale = 14;
    QFont font = painter->font();
    font.setPointSizeF(2);
    painter->setFont(font);
    painter->scale(1/scale, 1/scale);
    painter->drawText(QRectF(-scale*0.5, -scale*0.5, scale*1.0, scale*0.2), Qt::AlignCenter, f);
    painter->drawText(QRectF(-scale*0.5, scale*0.3, scale*1.0, scale*0.2), Qt::AlignCenter, name);
}

void CircuitItem::contactsShape(QPainterPath& path) const
{
    for(int i = 0; i < contacts.size(); ++i)
        path.addRect(contactRect().translated(contacts[i]));
}

//paint implementation for circuit elements

void RItem::paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 )
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(pen);
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

void CItem::paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr )
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(pen);
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

void LItem::paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 )
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(pen);
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


void GItem::paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(pen);
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

void EItem::paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(pen);
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
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(pen);
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

int CircuitItem::getId()
{
    return id;
}

QString CircuitItem::equal()
{
    QString tmp = eq;
    tmp.replace("u", getu());
    tmp.replace("i", geti());
    tmp.replace("f", f);
    return tmp;
}

QString CircuitItem::getu()
{
    return u+name;
}

QString CircuitItem::geti()
{
    return i+name;
}

RItem::RItem(int id_, QPointF pos_, QGraphicsItem *parent)
    : CircuitItem(parent)
{
    id = id_;
    name = "R" + QString::number(id);
    eq = "u=i*f";
    f = "1.0";
    fDim = "Ohm";
    fName = "R";
    elemType = CircuitElementType::R;
    setPos(pos_);
}

GItem::GItem(int id_, QPointF pos_, QGraphicsItem *parent)
    : CircuitItem(parent)
{
    id = id_;
    name = "G" + QString::number(id);
    eq = "i=u*f";
    f = "1.0";
    fDim = "Si";
    fName = "G";
    elemType = CircuitElementType::G;
    setPos(pos_);
}

CItem::CItem(int id_, QPointF pos_, QGraphicsItem *parent)
    : CircuitItem(parent)
{
    id = id_;
    name = "C" + QString::number(id);
    eq = "i=u'*f";
    f = "1.0";
    fDim = "F";
    fName = "C";
    elemType = CircuitElementType::C;
    setPos(pos_);
}

LItem::LItem(int id_, QPointF pos_, QGraphicsItem *parent)
    : CircuitItem(parent)
{
    id = id_;
    name = "L" + QString::number(id);
    eq = "u=i'*f";
    f = "1.0";
    fDim = "H";
    fName = "L";
    elemType = CircuitElementType::L;
    setPos(pos_);
}

IItem::IItem(int id_, QPointF pos_, QGraphicsItem *parent)
    : CircuitItem(parent)
{
    id = id_;
    name = "I" + QString::number(id);
    eq = "i=f";
    f = "1.0";
    fDim = "A";
    fName = "I";
    elemType = CircuitElementType::I;
    setPos(pos_);
}

EItem::EItem(int id_, QPointF pos_, QGraphicsItem *parent)
    : CircuitItem(parent)
{
    id = id_;
    name = "E" + QString::number(id);
    eq = "u=f";
    f = "1.0";
    fDim = "V";
    fName = "E";
    elemType = CircuitElementType::E;
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
    ground = false;
    id = id_;
    setZValue(2.0);
}

CircuitNodeItem::~CircuitNodeItem()
{

}

void CircuitNodeItem::setGround(bool ground_)
{
    ground = ground_;
    update();
}

QRectF CircuitNodeItem::boundingRect()  const
{
    return     QRectF(-0.5, -0.5, 1.5, 1.5);
}

QPainterPath CircuitNodeItem::shape() const
{
    QPainterPath path;
    path.addRect(CircuitItem::contactRect().adjusted(-0.1, -0.1, 0.1, 0.1));
    return path;
}

void CircuitNodeItem::paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(pen);
    painter->drawRect(CircuitItem::contactRect().adjusted(-0.1, -0.1, 0.1, 0.1));
    if(ground)
    {
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
    painter->scale(1/scale, 1/scale);
    painter->drawText(QRectF(-scale*0.4, -scale*0.4, scale*0.4, scale*0.2), Qt::AlignCenter, QString::number(id));

}

int CircuitNodeItem::type() const
{
    return CircuitItem::CircuitItemNodeType;
}

int CircuitNodeItem::getId()
{
    return id;
}

bool CircuitNodeItem::isGrounded()
{
    return ground;
}
