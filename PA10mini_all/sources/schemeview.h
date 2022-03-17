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
enum class CircuitElementType;

class SchemeView : public QGraphicsView
{
    Q_OBJECT

public:
    //using enum CircuitElementType;
    SchemeView(QWidget *parent = nullptr);
    ~SchemeView() override;

    void checkgrid();
    CircuitItem *lastElement() { return elements.last(); }
    CircuitNodeItem *lastNode() { return nodes.last(); }

public slots:
    QString getSystem();
    void rotateItem();
    void groundNode();
    void ungroundNode();
    void editCircuitItem();

    void deleteItem();

    //!< Add items slots
    void addR(const QPointF &pos, int id);
    void addG(const QPointF &pos, int id);
    void addL(const QPointF &pos, int id);
    void addC(const QPointF &pos, int id);
    void addU(const QPointF &pos, int id);
    void addI(const QPointF &pos, int id);

    void addR(const QPointF &pos);
    void addG(const QPointF &pos);
    void addL(const QPointF &pos);
    void addC(const QPointF &pos);
    void addU(const QPointF &pos);
    void addI(const QPointF &pos);
    void addNode(const QPointF &pos);
    void addNode(const QPointF &pos, int id);

private slots:
    void addR();
    void addG();
    void addL();
    void addC();
    void addU();
    void addI();
    void selectAllAction() const;

protected:
    void mousePressEvent(QMouseEvent * event) override;
    void mouseMoveEvent(QMouseEvent * event) override;
    void mouseReleaseEvent ( QMouseEvent * event ) override;
    void wheelEvent ( QWheelEvent * event ) override;
    void enterEvent (QEvent* event) override;
    void leaveEvent (QEvent* event) override;

private:
    void initMainMenu();
    bool eventFilter(QObject *target, QEvent *event) override;
    inline qreal getScale();
    inline qreal fullScale();
    void setScale (qreal s);
    int recieveElementId(CircuitElementType type);

    int gridW;
    int gridH;

    bool isGrabbed;
    bool isScaled;
    QPoint    lastMousePos;
    qreal scaleStep;

    QList<CircuitNodeItem*> nodes;
    QList<CircuitItem*> elements;
    QGraphicsItem* hoveredItem;

    QMenu* itemMenu;
    QMenu* nodeMenu;
    QMenu* mainMenu;
};

#endif // PVIEW_H
