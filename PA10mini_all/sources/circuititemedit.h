#ifndef CIRCUITITEMEDIT_H
#define CIRCUITITEMEDIT_H

#include <QWidget>
#include "ui_circuititemedit.h"
#include "circuititem.h"
class CircuitItem;
class CircuitItemEdit : public QWidget
{
    Q_OBJECT

public:
    CircuitItemEdit(CircuitItem*item_, QWidget *parent = 0);
    ~CircuitItemEdit();

    public slots:
        void apply();

private:
    Ui::CircuitItemEdit ui;
    CircuitItem* item;
};

#endif // CIRCUITITEMEDIT_H
