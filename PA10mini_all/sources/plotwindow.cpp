#include "plotwindow.h"

PlotWindow::PlotWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

PlotWindow::~PlotWindow()
{

}

void PlotWindow::populate()
{
	ui.plot->populate();
}