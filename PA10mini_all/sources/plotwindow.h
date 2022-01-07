#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QWidget>
#include "ui_plotwindow.h"

class PlotWindow : public QWidget
{
    Q_OBJECT

public:
    PlotWindow(QWidget *parent = 0);
    ~PlotWindow();
    void populate();

private:
    Ui::PlotWindow ui;
};

#endif // PLOTWINDOW_H
