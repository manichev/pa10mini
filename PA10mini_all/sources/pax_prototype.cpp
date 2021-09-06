#include "pax_prototype.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdexcept>
#include <QJsonObject>
#include <QJsonDocument>

#include "daesystem.h"
#include "textdriver.h"
#include "solver.h"
#include "manzhuk/manzhuk.h"

extern Solver* solver;

PAX_Prototype::PAX_Prototype(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
    // QTextCodec *langcodec=QTextCodec::codecForName("CP1251");
    // QTextCodec::setCodecForTr(langcodec);
    ui.setupUi(this);
    ui.progressBar->hide();
    solver = new Solver(this);
    connect( solver, SIGNAL(progressChanged(int)), ui.progressBar, SLOT(setValue(int)));

    connect(ui.loadSchemeButton, &QPushButton::clicked, this, &PAX_Prototype::loadSchemeSlot);
    connect(ui.saveSchemeButton, &QPushButton::clicked, this, &PAX_Prototype::saveSchemeSlot);
    connect(ui.saveSchemeAsButton, &QPushButton::clicked, this, &PAX_Prototype::saveSchemeAsSlot);

    installEventFilter(this);
    plot = new PlotWindow;
}

PAX_Prototype::~PAX_Prototype()
{
    delete solver;
}

void PAX_Prototype::showErr(const QString& message)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Error");
    msgBox.setText(message);
    msgBox.exec();
}

bool PAX_Prototype::eventFilter(QObject *object, QEvent *event)
{
    Q_UNUSED(object)

    if( event->type() == QEvent::Close )
    {
        exit(0);
    }
    return false;
}

void PAX_Prototype::openPlot()
{
    plot->show();
    plot->populate();
}

void PAX_Prototype::schemeToText()
{
    activateEqualMode();
    ui.equalEdit->createNew();
    ui.equalEdit->setPlainText(ui.schemeView->getSystem());
}

void PAX_Prototype::solve()
{
    DAESystem daeSystem;
    grammar::TextDriver textDriver(&daeSystem);
    std::string daeStr;

    if( sender()->objectName() == "solveButton" )
    {
        daeStr = ui.equalEdit->toPlainText().toStdString();
    }
    else
    {
        daeStr = ui.schemeView->getSystem().toStdString();
    }
    try
    {
        textDriver.parse_string(daeStr);
    }
    catch(TextDriverException e)
    {
        showErr(e.reason());
        return ;
    }

    SolverParam*  param = new SolverParam;
    param->exec();

    if( param->result() != QDialog::Accepted)
        return;

    QString name;
    if( sender()->objectName() == "solveButton" )
    {
        name = ui.equalEdit->getFileName();
        int pos = name.lastIndexOf('/');
        name.remove(0, pos);
        name.prepend("output/");
        name.replace(".txt", ".rez"); //".pa10");
    }
    else
    {
        name = "output/scheme.pa10";
    }

    solver->set_outFileName(name);
    solver->setSystem(&daeSystem);
    VariableChooser* vc = new VariableChooser;
    vc->exec();

    ui.solveButton->setDisabled(true);
    ui.plotButton->setDisabled(true);
    ui.plotButton_2->setDisabled(true);
    ui.progressBar->setValue(0);
    ui.progressBar->show();

    try
    {
        solver->solve();
    }
    catch(invalid_argument& e)
    {
        cerr << e.what() << endl;
        getchar();
        return;
    }

    ui.progressBar->hide();
    ui.solveButton->setEnabled(true);
    ui.plotButton->setEnabled(true);
    ui.plotButton_2->setEnabled(true);

    delete param;
    openPlot();
}

void PAX_Prototype::activateSchemeMode()
{
    ui.stackedWidget->setCurrentWidget(ui.schemeMode);
}

void PAX_Prototype::activateEqualMode()
{
    ui.stackedWidget->setCurrentWidget(ui.equalMode);
}

void PAX_Prototype::saveSchemeSlot()
{
    saveScheme(m_schemePath);
}

void PAX_Prototype::loadSchemeSlot()
{
    m_schemePath = QFileDialog::getOpenFileName(this, tr("Открыть файл схемы"), m_schemePath, tr("(*.*)"));
    loadScheme(m_schemePath);
}

void PAX_Prototype::saveSchemeAsSlot()
{
    m_schemePath = QFileDialog::getSaveFileName(this, tr("Сохранить файл схемы как"), m_schemePath, tr("(*.*)"));

    saveScheme(m_schemePath);
}

//! [4]
/*bool Game::saveGame(Game::SaveFormat saveFormat) const
{
    QFile saveFile(saveFormat == Json
        ? QStringLiteral("save.json")
        : QStringLiteral("save.dat"));

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QJsonObject gameObject;
    write(gameObject);
    QJsonDocument saveDoc(gameObject);
    saveFile.write(saveFormat == Json
        ? saveDoc.toJson()
        : saveDoc.toBinaryData());

    return true;
}*/

void PAX_Prototype::saveScheme(const QString &path)
{
    QFile saveFile(path);

    auto items = ui.schemeView->scene()->items();

    if (! saveFile.open(QIODevice::WriteOnly)) {
        qCritical() << "Output file " << path << " wasn't opened on write";
        return;
    }

    QJsonObject schemeObject;

    foreach (auto item, items) {
        CircuitItem *citem = qgraphicsitem_cast<CircuitItem*>(item);
        if (citem)
            schemeObject[citem->name] = citem->toJSON();
    }

    QJsonDocument saveDoc(schemeObject);
    saveFile.write(saveDoc.toJson());
}

/*void PAX_Prototype::saveScheme(const QString &path)
{
    auto items = ui.schemeView->scene()->items();

    QFile file(path);

    if (! file.open(QIODevice::WriteOnly)) {
        qCritical() << "Output file " << path << " wasn't opened on write";
    }

    // QTextStream *stream = new QTextStream(&file);
    QTextStream stream(&file);

    foreach (auto item, items) {
        CircuitItem *citem = qgraphicsitem_cast<CircuitItem*>(item);
        if (citem)
            stream << citem->toQVariant().toByteArray();
    }
}*/

void PAX_Prototype::loadScheme(const QString &path)
{

}
