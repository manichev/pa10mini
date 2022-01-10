#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QFileDialog>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    connect(ui->pathToMinGWToolButton, &QToolButton::clicked, this, &SettingsDialog::onPathToMingwToolButtonClick);
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

void SettingsDialog::onPathToMingwToolButtonClick()
{
    auto str = QFileDialog::getOpenFileName(this, tr("Укажите путь к g++"), ui->pathToMinGWEdit->text(), tr("Исполняемый файл (*.exe)"));

    if (!str.isEmpty())
        ui->pathToMinGWEdit->setText(str);
}
