#include "circuititemedit.h"

inline QString prefixFromEdit(const QString &editText)
{
    if (editText.back().isLetter()) {
        return editText.back();
    }

    return {};
}

inline CircuitItemPrefix letterToPrefix(char letter)
{
    switch (letter) {
    case 'a': return CircuitItemPrefix::CircuitItemAtto;
    case 'f': return CircuitItemPrefix::CircuitItemFemto;
    case 'p': return CircuitItemPrefix::CircuitItemPico;
    case 'n': return CircuitItemPrefix::CircuitItemNano;
    case 'u': return CircuitItemPrefix::CircuitItemMicro;
    case 'm': return CircuitItemPrefix::CircuitItemMilli;
    case 'k': return CircuitItemPrefix::CircuitItemKilo;
    case 'M': return CircuitItemPrefix::CircuitItemMega;
    case 'G': return CircuitItemPrefix::CircuitItemGiga;
    case 'T': return CircuitItemPrefix::CircuitItemTera;
    case 'P': return CircuitItemPrefix::CircuitItemPeta;
    }

    return {};
}

inline CircuitItemPrefix letterToPrefix(const QString &letter)
{
    return letterToPrefix(static_cast<char>(letter.front().toLatin1()));
}

CircuitItemEdit::CircuitItemEdit(CircuitItem*item_, QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    item = item_;
    ui.fEdit->setText(QString("%1%2").arg(item->getF(), item->fPrefix()));
    ui.i0Edit->setText(item->getI0());
    ui.u0Edit->setText(item->getU0());
    ui.nameEdit->setText(item->name());
    ui.fNameLabel->setText(item->fName());
    ui.fDimLabel->setText(item->fUnit());
}

CircuitItemEdit::~CircuitItemEdit()
{

}

void CircuitItemEdit::apply()
{
    item->setName(ui.nameEdit->text());
    item->setI0(ui.i0Edit->text());
    item->setU0(ui.u0Edit->text());
    auto reg = QRegExp("\b(sin|cos|+|-|*|/|)\b");
    if (ui.fEdit->text().contains(reg)) {
        item->setF(ui.fEdit->text());
    } else if (ui.fEdit->text().back().isLetter()) {
        auto prefix = letterToPrefix(ui.fEdit->text().back().toLatin1());
        item->setFMult(CircuitItemPrefixMultiplier[prefix]);
        item->setFPrefix(ui.fEdit->text().mid(ui.fEdit->text().count() - 1));
        item->setF(ui.fEdit->text().mid(0, ui.fEdit->text().count() - 1));
    } else {
        item->setF(ui.fEdit->text());
    }
    close();
}
