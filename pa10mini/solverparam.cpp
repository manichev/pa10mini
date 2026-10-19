#include "solverparam.h"

extern Solver* solver;

SolverParam::SolverParam(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    setWindowModality(Qt::ApplicationModal);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

    ui.okButton->setEnabled(false);

    ui.t0LineEdit->setText(QString::number(solver->get_t0(), 'g'));
    ui.tkLineEdit->setText(QString::number(solver->get_tk(), 'g'));
    ui.hmnLineEdit->setText(QString::number(solver->get_hmn(), 'e', 1));
    ui.hmxLineEdit->setText(QString::number(solver->get_hmx(), 'e', 1));
    ui.epsLineEdit->setText(QString::number(solver->get_eps(), 'e', 1));
    ui.nmSpinBox->setValue(solver->get_nm());
    ui.rj2CheckBox->setChecked(solver->get_rj2_before());
    check();
}

SolverParam::~SolverParam()
{

}

void SolverParam::apply()
{
    solver->set_t0(ui.t0LineEdit->text().toDouble());
    solver->set_tk(ui.tkLineEdit->text().toDouble());
    solver->set_hmn(ui.hmnLineEdit->text().toDouble());
    solver->set_hmx(ui.hmxLineEdit->text().toDouble());
    solver->set_eps(ui.epsLineEdit->text().toDouble());
    solver->set_nm(ui.nmSpinBox->value());
    solver->set_rj2_before(ui.rj2CheckBox->isChecked());
    accept();
}

void SolverParam::check()
{
    bool t0Flag, tkFlag, hmnFlag, hmxFlag, epsFlag;

    double t0Tmp = ui.t0LineEdit->text().toDouble(&t0Flag);
    double tkTmp = ui.tkLineEdit->text().toDouble(&tkFlag);
    double hmnTmp = ui.hmnLineEdit->text().toDouble(&hmnFlag);
    double hmxTmp = ui.hmxLineEdit->text().toDouble(&hmxFlag);
    double epsTmp = ui.epsLineEdit->text().toDouble(&epsFlag);

    ui.tCheckBox->setChecked(t0Flag && tkFlag && t0Tmp < tkTmp && t0Tmp >= 0);
    ui.hCheckBox->setChecked(hmnFlag && hmxFlag && hmnTmp < hmxTmp && hmnTmp >= 0);
    ui.epsCheckBox->setChecked(epsFlag && epsTmp > 0);

    bool okFlag = t0Flag && tkFlag && t0Tmp < tkTmp
                    && hmnFlag && hmxFlag && hmnTmp < hmxTmp;
    ui.okButton->setEnabled(okFlag);
}
