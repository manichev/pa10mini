#ifndef VARIABLECHOOSER_H
#define VARIABLECHOOSER_H

#include <QList>
#include <QDialog>
#include <QLineEdit>
#include <QDebug>
#include "ui_variablechooser.h"
#include "solver.h"
#include "daesystem.h"

class VariableChooser : public QDialog
{
	Q_OBJECT

public:
	VariableChooser(QWidget *parent = 0);
	~VariableChooser();

public slots:
	void apply();
	void selectAll(int state);

private:
	Ui::VariableChooser ui;
	QList<QCheckBox*> checkBoxes;
	QList<QLineEdit*> lines;
};

#endif // VARIABLECHOOSER_H
