#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

QString SettingsDialog::getMinGWPath() const
{
    return ui->pathToMinGWEdit->text();
}

void SettingsDialog::setMinGWPath(const QString &path)
{
    ui->pathToMinGWEdit->setText(path);
}
