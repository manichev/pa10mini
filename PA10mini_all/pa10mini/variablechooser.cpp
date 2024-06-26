#include "variablechooser.h"

extern Solver* solver;
VariableChooser::VariableChooser(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    setWindowModality(Qt::ApplicationModal);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    QCheckBox* checkBox;
    QLineEdit* line;
    for (const auto &name : solver->names) {
        checkBox = new QCheckBox(name);
        line = new QLineEdit;
        ui.formLayout->addRow(checkBox, line);
        checkBoxes.push_back(checkBox);
        lines.push_back(line);
    }
}

VariableChooser::~VariableChooser()
{
    for (auto checkBox : checkBoxes)
        delete checkBox;
}

void VariableChooser::apply()
{
    int i = 0;
    for (auto checkBox : checkBoxes) {
        if (checkBox->checkState() == Qt::Checked) {
            solver->trace.append(i+1);
            solver->dims.append(lines[i]->text());
            qDebug()<<solver->names[i];
        }
        i++;
    }
    close();
    accepted();
}

void VariableChooser::selectAll(int state)
{
    for (auto checkBox : checkBoxes) {
        checkBox->setCheckState((Qt::CheckState)state);
    }
}
