#include "schemeview.h"

void exportPics()
{
    QPen pen;
    int a =128;
    pen.setWidthF(4.5);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setCapStyle(Qt::RoundCap);
    QPixmap pix(2*a, a);
    QPainter * painter = new QPainter(&pix);
    painter->translate(a, a/2);
    painter->setRenderHint(QPainter::Antialiasing);

    painter->setPen(pen);
    QColor col(255,255,255,255);

    pix.fill(col);
    //resistance
    painter->drawRect(QRectF(a*-0.3, a*-0.15, a*0.6, a*0.3));
    painter->drawLine(QLineF(a*-0.8, a*0.0, a*-0.3, a*0.0));
    painter->drawLine(QLineF(a*0.3, a*0.0, a*0.8, a*0.0));

    pix.save("Resources/SchemeEditor/R.png", "PNG");
    pix.fill(col);
    //capacitor
    painter->drawLine(QLineF(a*-0.8, a*0.0, a*-0.1, a*0.0));
    painter->drawLine(QLineF(a*0.1, a*0.0, a*0.8, a*0.0));

    painter->drawLine(QLineF(a*-0.1, a*-0.2, a*-0.1, a*0.2));
    painter->drawLine(QLineF(a*0.1, a*-0.2, a*0.1, a*0.2));

    pix.save("Resources/SchemeEditor/C.png", "PNG");
    pix.fill(col);
    //inductance
    painter->drawLine(QLineF(a*-0.8, a*0.0, a*-0.4, a*0.0));
    painter->drawLine(QLineF(a*0.4, a*0.0, a*0.8, a*0.0));

    painter->drawArc(QRectF(a*-0.4, a*-0.1, a*0.2, a*0.2), a*0*16, 180*16);
    painter->drawArc(QRectF(a*-0.2, a*-0.1, a*0.2, a*0.2), a*0*16, 180*16);
    painter->drawArc(QRectF(a*0.0, a*-0.1, a*0.2, a*0.2), a*0*16, 180*16);
    painter->drawArc(QRectF(a*0.2, a*-0.1, a*0.2, a*0.2), a*0*16, 180*16);

    pix.save("Resources/SchemeEditor/L.png", "PNG");
    pix.fill(col);
    //conduction
    painter->drawRect(QRectF(a*-0.3, a*-0.15, a*0.6, a*0.3));
    painter->drawLine(QLineF(a*-0.8, a*0.0, a*-0.3, a*0.0));
    painter->drawLine(QLineF(a*0.3, a*0.0, a*0.8, a*0.0));

    painter->drawLine(QLineF(a*-0.3, a*-0.15, a*0.3, a*0.15));
    painter->drawLine(QLineF(a*-0.3, a*0.15, a*0.3, a*-0.15));

    pix.save("Resources/SchemeEditor/G.png", "PNG");
    pix.fill(col);
    //voltage

    painter->drawLine(QLineF(a*-0.8, a*0.0, a*0.8, a*0.0));

    painter->drawEllipse(QRectF(a*-0.25, a*-0.25, a*0.5, a*0.5));

    painter->drawLine(QLineF(a*-0.05, a*-0.1, a*-0.2, a*0.0));
    painter->drawLine(QLineF(a*-0.05, a*0.1, a*-0.2, a*0.0));

    pix.save("Resources/SchemeEditor/E.png", "PNG");
    pix.fill(col);
    //current

    painter->drawLine(QLineF(a*-0.8, a*0.0, a*0.8, a*0.0));

    painter->drawEllipse(QRectF(a*-0.25, a*-0.25, a*0.5, a*0.5));

    painter->drawLine(QLineF(a*-0.15, a*-0.1, a*0.0, a*0.0));
    painter->drawLine(QLineF(a*0.0, a*0.0, a*-0.15, a*0.1));

    painter->drawLine(QLineF(a*0.05, a*-0.1, a*0.2, a*0.0));
    painter->drawLine(QLineF(a*0.2, a*0.0, a*0.05, a*0.1));

    pix.save("Resources/SchemeEditor/I.png", "PNG");
    pix.fill(col);
    painter->fillRect(QRectF(a*-0.05, a*-0.05, a*0.1, a*0.1), Qt::black);
    painter->drawRect(QRectF(a*-0.05, a*-0.05, a*0.1, a*0.1).adjusted(a*-0.1, a*-0.1, a*0.1, a*0.1));
    pix.save("Resources/SchemeEditor/Ungrounded.png", "PNG");
    pix.fill(col);
    painter->translate(0, -a/4);

    painter->fillRect(QRectF(a*-0.05, a*-0.05, a*0.1, a*0.1), Qt::black);
    painter->drawRect(QRectF(a*-0.05, a*-0.05, a*0.1, a*0.1).adjusted(a*-0.1, a*-0.1, a*0.1, a*0.1));
    painter->drawLine(QLineF(a*0.0, a*0.0, a*0.0, a*0.6));
    painter->drawLine(QLineF(a*-0.3, a*0.35, a*0.3, a*0.35));
    painter->drawLine(QLineF(a*-0.2, a*0.45, a*0.2, a*0.45));
    painter->drawLine(QLineF(a*-0.1, a*0.55, a*0.1, a*0.55));
    pix.save("Resources/SchemeEditor/Grounded.png", "PNG");
}


SchemeView::SchemeView(QWidget *parent)
    : QGraphicsView(parent)
{
    exportPics();
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setFrameShape(QFrame::NoFrame);
    setScene(new QGraphicsScene());

    isGrabbed = false;
    isScaled = false;

    //setRenderHint(QPainter::Antialiasing);

//numbers...
    gridW = 15;
    gridH = 10;
    scaleStep = 0.05;

//drawing grid
    setSceneRect(-1, -1, gridW + 2, gridH + 2);
    QList<QGraphicsLineItem *> gridLines;
    QPen gridPen;
    gridPen.setColor(QColor(222, 222, 222, 255));
    gridPen.setStyle(Qt::DashLine);
    gridPen.setWidthF(0.01);

    for (double x = 0; x <= gridW; x += 1.0)
        gridLines.push_back(scene()->addLine(x, 0.0, x, gridH, gridPen));
    for (double y = 0; y <= gridH; y+=1.0)
        gridLines.push_back(scene()->addLine(0.0, y, gridW, y, gridPen));
    installEventFilter(this);

    //settin up menus
    //item
    itemMenu = new QMenu(this);

    QAction* rotateAction;
    rotateAction = new QAction("Rotate", this);
    connect(rotateAction, SIGNAL(triggered()), this, SLOT(rotateItem()));
    itemMenu->addAction(rotateAction);

    QAction* editAction;
    editAction = new QAction("Edit", this);
    connect(editAction, SIGNAL(triggered()), this, SLOT(editCircuitItem()));
    itemMenu->addAction(editAction);

    QAction* deleteAction;
    deleteAction = new QAction("Delete", this);
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteItem()));
    itemMenu->addAction(deleteAction);
    //node
    nodeMenu = new QMenu(this);

    QAction* groundAction;
    groundAction = new QAction("Ground", this);
    connect(groundAction, SIGNAL(triggered()), this, SLOT(groundNode()));
    nodeMenu->addAction(groundAction);

    QAction* ungroundAction;
    ungroundAction = new QAction("Unground", this);
    connect(ungroundAction, SIGNAL(triggered()), this, SLOT(ungroundNode()));
    nodeMenu->addAction(ungroundAction);

    //main
    initMainMenu();
}

void SchemeView::initMainMenu()
{
    mainMenu = new QMenu(this);

    QAction* addRAction;
    addRAction = new QAction("Add R", this);
    connect(addRAction, SIGNAL(triggered()), this, SLOT(addR()));
    mainMenu->addAction(addRAction);

    QAction* addGAction;
    addGAction = new QAction("Add G", this);
    connect(addGAction, SIGNAL(triggered()), this, SLOT(addG()));
    mainMenu->addAction(addGAction);

    QAction* addLAction;
    addLAction = new QAction("Add L", this);
    connect(addLAction, SIGNAL(triggered()), this, SLOT(addL()));
    mainMenu->addAction(addLAction);

    QAction* addCAction;
    addCAction = new QAction("Add C", this);
    connect(addCAction, SIGNAL(triggered()), this, SLOT(addC()));
    mainMenu->addAction(addCAction);

    QAction* addEAction;
    addEAction = new QAction("Add E", this);
    connect(addEAction, SIGNAL(triggered()), this, SLOT(addU()));
    mainMenu->addAction(addEAction);

    QAction* addIAction;
    addIAction = new QAction("Add I", this);
    connect(addIAction, SIGNAL(triggered()), this, SLOT(addI()));
    mainMenu->addAction(addIAction);

    QAction* selectAllAction;
    selectAllAction = new QAction("Select all", this);
    selectAllAction->setShortcut(QKeySequence::SelectAll);
    connect(selectAllAction, &QAction::triggered, this, &SchemeView::selectAllAction);
    mainMenu->addAction(selectAllAction);
}

void SchemeView::selectAllAction() const
{
    for (auto item : items()) {
        item->setSelected(true);
    }
}

void SchemeView::deleteItem()
{
    CircuitItem* element;

    foreach (element, elements) {
        if (element->isSelected()) {
            elements.removeOne(element);
            delete element;
        } else if (hoveredItem && qgraphicsitem_cast<CircuitItem*>(hoveredItem)->getId() == element->getId() &&
            qgraphicsitem_cast<CircuitItem*>(hoveredItem)->elementType() == element->elementType()) {// cHANGE: && to ==

            elements.removeOne(element);
            delete element;
        }
    }
    checkgrid();
}
void SchemeView::editCircuitItem()
{
    CircuitItemEdit *tmp = new CircuitItemEdit(reinterpret_cast<CircuitItem*>(hoveredItem));
    tmp->move(lastMousePos);
    tmp->show();
}

void SchemeView::groundNode()
{
    reinterpret_cast<CircuitNodeItem*>(hoveredItem)->setGround(true);
}

void SchemeView::ungroundNode()
{
    reinterpret_cast<CircuitNodeItem*>(hoveredItem)->setGround(false);
}

SchemeView::~SchemeView()
{

}

void SchemeView::checkgrid()
{
    QList<QGraphicsItem*> items;
    QGraphicsItem* item;
    CircuitNodeItem* node;
    for (int i = 0; i <= gridH; ++i) {
        for (int j = 0; j <= gridW; ++j) {
            int counter = 0;
            items = scene()->items(CircuitItem::contactRect().translated(j, i));
            int id = -1;
            foreach (item, items) {
                if (item->type() == CircuitItem::CircuitItemType) {
                    if (reinterpret_cast<CircuitItem*>(item)->contact(QPointF(j, i)) != -1)
                        counter++;
                } else if (item->type() == CircuitItem::CircuitItemNodeType) {
                    id = reinterpret_cast<CircuitNodeItem*>(item)->getId();
                }
            }

            if (id == -1 && counter >= 2) {
                addNode(QPointF(j, i));
            } else if (id != -1 && counter < 2) {
                foreach (node, nodes) {
                    if (node->getId() == id) {
                        nodes.removeOne(node);
                        delete node;
                    }
                }
            }
        }
    }
}

void SchemeView::addNode(const QPointF &pos, int id)
{
    nodes.push_back(new CircuitNodeItem(id, pos));
    scene()->addItem(nodes.last());
}

void SchemeView::addNode(const QPointF &pos)
{
    CircuitNodeItem* node;
    int newId = 1;
    bool stop = false;
    while (!stop) {
        stop = true;
        foreach (node, nodes)
            if (newId == node->getId())
                stop = false;
        if (!stop)
            ++newId;
    }

    addNode(pos, newId);
}

QString SchemeView::getSystem()
{
    QString result;
    CircuitItem* element;
    CircuitNodeItem* node;
//dPhi and element equals
    foreach (element, elements) {
        result.append(element->equal() + "\n");
        result.append(element->getU() + "=");
        bool isFirstInLine = true;
        foreach (node, nodes) {
            if (!node->isGrounded()) {
                int contact = element->contact(node->scenePos());
                qDebug() << contact;
                if (contact == 0) {
                    if (isFirstInLine)
                        isFirstInLine = false;
                    else
                        result.append("+");
                    result.append("phi" + QString::number(node->getId()));
                } if (contact == 1) {
                    isFirstInLine = false;
                    result.append("-");
                    result.append("phi" + QString::number(node->getId()));
                }
            }
        }
        result.append("\n");
    }
//Kirchhoff
    foreach (node, nodes) {
        bool isFirstInLine = true;
        if (!node->isGrounded()) {
            foreach(element, elements) {
                int contact = element->contact(node->scenePos());
                if (contact == 0) {
                    if (isFirstInLine)
                        isFirstInLine = false;
                    else
                        result.append("+");
                    result.append(element->getI());
                } else if (contact == 1) {
                    isFirstInLine = false;
                    result.append("-");
                    result.append(element->getI());
                }
            }
            result.append("=0\n");
        }
    }

    foreach (element, elements) {
        if (element->getU0().toDouble() != 0) {
            result.append(element->getU());
            result.append("==");
            result.append(element->getU0());
            result.append("\n");
        }

        if (element->getI0().toDouble() != 0) {
            result.append(element->getI());
            result.append("==");
            result.append(element->getI0());
            result.append("\n");
        }
    }
    return result;
}

bool SchemeView::eventFilter(QObject *object, QEvent *event)
{
    Q_UNUSED(object)
    if (event->type() == QEvent::Resize ) {
        if (getScale() < fullScale()) {
            setScale(fullScale());
        }
    }

    return false;
}


void SchemeView::mousePressEvent(QMouseEvent * event)
{
    if (event->button() == Qt::MidButton) {
        setCursor(Qt::ClosedHandCursor);
        isGrabbed = true;
    } else {
        QGraphicsView::mousePressEvent(event);
    }
    lastMousePos = event->pos();
}

void SchemeView::rotateItem()
{
    static_cast<CircuitItem*>(hoveredItem)->rotateRight();
    checkgrid();
}
void SchemeView::mouseMoveEvent(QMouseEvent * event)
{
    if (isGrabbed) {
        int dx  = lastMousePos.x() - event->pos().x();
        int dy  = lastMousePos.y() - event->pos().y();
        QScrollBar* hBar = horizontalScrollBar();
        QScrollBar* vBar = verticalScrollBar();
        hBar->setValue(hBar->value() + dx);
        vBar->setValue(vBar->value() + dy);

        lastMousePos = event->pos();
    } else {
        QGraphicsView::mouseMoveEvent(event);
    }
}


void SchemeView:: mouseReleaseEvent(QMouseEvent * event)
{
    if (event->button() == Qt::MidButton) {
        setCursor(Qt::ArrowCursor);
        isGrabbed = false;
        hoveredItem = nullptr;
    } else if (event->button() == Qt::LeftButton) {
        isGrabbed = false;
        hoveredItem = nullptr;
        QGraphicsItem* item = scene()->itemAt(mapToScene(event->pos()), QTransform());
        if (item)
            item->setSelected(true);
        if (event->modifiers() != Qt::KeyboardModifier::ControlModifier) {
            for (auto other : items())
                if (other != item)
                    other->setSelected(false);
        }
    } else if (event->button() == Qt::RightButton) {
        hoveredItem = scene()->itemAt(mapToScene(event->pos()), QTransform());
        if (hoveredItem != nullptr) {
            lastMousePos = event->globalPos();

            switch(hoveredItem->type()) {
            case CircuitItem::CircuitItemType:
                itemMenu->exec(event->globalPos());
                return;//break;
            case CircuitItem::CircuitItemNodeType:
                nodeMenu->exec(event->globalPos());
                return;//break;
            case QGraphicsLineItem::Type:
                break;
            }
        }
        //else
        //{
        lastMousePos = event->pos();
        mainMenu->exec(event->globalPos());
        //}
    } else {
        hoveredItem = nullptr;
        QGraphicsView::mouseReleaseEvent(event);
    }
}


void SchemeView::enterEvent (QEvent* event)
{
    Q_UNUSED(event)

    setMouseTracking(true);
}


void SchemeView::leaveEvent (QEvent* event)
{
    Q_UNUSED(event)

    setMouseTracking(false);
}

void SchemeView::keyPressEvent(QKeyEvent *event)
{
    if (event->matches(QKeySequence::SelectAll)) {
        selectAllAction();
    } else if (event->key() == Qt::Key_Delete) {
        deleteItem();
    }
}

void SchemeView::wheelEvent ( QWheelEvent * event )
{
    qreal delta = (event->delta() > 0) ? scaleStep : -scaleStep;
    qreal scaleValue = getScale() * (1 + delta);
    if (scaleValue > fullScale()) {
        setScale(scaleValue);
        isScaled = true;
    } else {
        setScale(fullScale());
        isScaled = false;
    }
}


qreal SchemeView::getScale()
{
    return transform().m11();
}

qreal SchemeView::fullScale()
{
    return sceneRect().height()/height()>sceneRect().width()/width() ?
                height()/sceneRect().height() : width()/sceneRect().width();
}

int SchemeView::recieveElementId(CircuitElementType type)
{
    CircuitItem* element;
    int newId = 1;
    bool stop = false;
    while(!stop) {
        stop = true;
        foreach (element, elements)
            if (newId == element->getId() && element->elementType() == type)
                stop = false;

        if (!stop)
            ++newId;
    }
    return newId;
}

void SchemeView::setScale (qreal s)
{
    QTransform tr = transform();
    tr.setMatrix(s, tr.m12(), tr.m13(),
                 tr.m21(), s, tr.m23(),
                 tr.m31(), tr.m32(), tr.m33());
    setTransform(tr);
}

void SchemeView::addR(const QPointF &pos, int id)
{
    RItem* tmp = new RItem(id, pos);
    // scene()->addItem(reinterpret_cast<QGraphicsLineItem*>(tmp));
    scene()->addItem(tmp);
    elements.push_back(static_cast<CircuitItem*>(tmp));
}

void SchemeView::addG(const QPointF &pos, int id)
{
    GItem* tmp = new GItem(id, pos);
    scene()->addItem(tmp);
    elements.push_back(static_cast<CircuitItem*>(tmp));
}

void SchemeView::addL(const QPointF &pos, int id)
{
    LItem* tmp = new LItem(id, pos);
    scene()->addItem(tmp);
    elements.push_back(static_cast<CircuitItem*>(tmp));
}

void SchemeView::addC(const QPointF &pos, int id)
{
    CItem* tmp = new CItem(id, pos);
    scene()->addItem(tmp);
    elements.push_back(static_cast<CircuitItem*>(tmp));
}

void SchemeView::addU(const QPointF &pos, int id)
{
    EItem* tmp = new EItem(id, pos);
    scene()->addItem(tmp);
    elements.push_back(static_cast<CircuitItem*>(tmp));
}

void SchemeView::addI(const QPointF &pos, int id)
{
    IItem* tmp = new IItem(id, pos);
    scene()->addItem(tmp);
    elements.push_back(static_cast<CircuitItem*>(tmp));
}

void SchemeView::addR(const QPointF &pos)
{
    int id = recieveElementId(CircuitElementType::R);

    addR(pos, id);

    checkgrid();
}

void SchemeView::addG(const QPointF &pos)
{
    int id = recieveElementId(CircuitElementType::G);

    addG(pos, id);

    checkgrid();
}

void SchemeView::addL(const QPointF &pos)
{
    int id = recieveElementId(CircuitElementType::L);

    addL(pos, id);

    checkgrid();
}

void SchemeView::addC(const QPointF &pos)
{
    int id = recieveElementId(CircuitElementType::C);

    addC(pos, id);

    checkgrid();
}

void SchemeView::addU(const QPointF &pos)
{
    int id = recieveElementId(CircuitElementType::E);

    addU(pos, id);

    checkgrid();
}

void SchemeView::addI(const QPointF &pos)
{
    int id = recieveElementId(CircuitElementType::I);

    addI(pos, id);

    checkgrid();
}

void SchemeView::addR()
{
    addR(mapToScene(lastMousePos).toPoint());
}

void SchemeView::addG()
{
    addG(mapToScene(lastMousePos).toPoint());
}

void SchemeView::addL()
{
    addL(mapToScene(lastMousePos).toPoint());
}

void SchemeView::addC()
{
    addC(mapToScene(lastMousePos).toPoint());
}

void SchemeView::addU()
{
    addU(mapToScene(lastMousePos).toPoint());
}

void SchemeView::addI()
{
    addI(mapToScene(lastMousePos).toPoint());
}


