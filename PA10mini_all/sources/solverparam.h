#ifndef SOLVERPARAM_H
#define SOLVERPARAM_H

#include <QDialog>
#include "ui_solverparam.h"

#include "solver.h"

class SolverParam : public QDialog
{
    Q_OBJECT

public:
    SolverParam(QWidget *parent = nullptr);
    ~SolverParam();
public slots:
    void check();
    void apply();
private:
    Ui::SolverParam ui;
};

#endif // SOLVERPARAM_H
