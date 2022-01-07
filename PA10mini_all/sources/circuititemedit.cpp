#include "circuititemedit.h"

CircuitItemEdit::CircuitItemEdit(CircuitItem*item_, QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    item = item_;
    ui.fEdit->setText(item->getF());
    ui.i0Edit->setText(item->i0);
    ui.u0Edit->setText(item->u0);
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
    item->setF(ui.fEdit->text());
    item->i0 = ui.i0Edit->text();
    item->u0 = ui.u0Edit->text();
    close();
}
