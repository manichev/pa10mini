#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QFileDialog>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    setWindowTitle(tr("Диалог настроек"));
#if defined(Q_OS_WIN)
    ui->label->setText(tr("Компилятор задания: g++ (MinGW)"));
#else
    ui->label->setText(tr("Компилятор задания: g++ (пустой путь — поиск в PATH)"));
#endif

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
#if defined(Q_OS_WIN)
    const QString filter = tr("Исполняемый файл (*.exe);;Все файлы (*)");
#else
    const QString filter = tr("Все файлы (*)");
#endif
    const QString str = QFileDialog::getOpenFileName(
        this, tr("Укажите путь к g++"), ui->pathToMinGWEdit->text(), filter);

    if (!str.isEmpty())
        ui->pathToMinGWEdit->setText(str);
}
