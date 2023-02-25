#ifndef CIRCUITITEMEDIT_H
#define CIRCUITITEMEDIT_H

#include <QWidget>
#include "ui_circuititemedit.h"
#include "circuititem.h"

enum CircuitItemPrefix {
    CircuitItemAtto,
    CircuitItemFemto,
    CircuitItemPico,
    CircuitItemNano,
    CircuitItemMicro,
    CircuitItemMilli,
    CircuitItemKilo,
    CircuitItemMega,
    CircuitItemGiga,
    CircuitItemTera,
    CircuitItemPeta
};

static const QStringList CircuitItemPrefixName = { "a", "f", "p", "n", "u", "m", "k", "M", "G", "T", "P"};
static const QStringList CircuitItemPrefixNameRu = { "а", "ф", "п", "н", "мк", "м", "к", "М", "Г", "Т", "П"};
static const QList<double> CircuitItemPrefixMultiplier = { 1e-18, 1e-15, 1e-12, 1e-9, 1e-6, 1e-3, 1e3, 1e6, 1e9, 1e12, 1e15};

class CircuitItem;
class CircuitItemEdit : public QWidget
{
    Q_OBJECT

public:
    CircuitItemEdit(CircuitItem*item_, QWidget *parent = nullptr);
    ~CircuitItemEdit();

    public slots:
        void apply();

private:
    Ui::CircuitItemEdit ui;
    CircuitItem* item;
};

#endif // CIRCUITITEMEDIT_H
