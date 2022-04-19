#include "daesystem.h"
#include "manzhuk/manzhuk.h"
#include "pax_prototype.h"
#include "settingsdialog.h"
#include "solver.h"
#include "textdriver.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSettings>

// Versions
static const int major = 10;
static const int minor = 2;
static const int patch = 0;

extern Solver* solver;

PAX_Prototype::PAX_Prototype(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
    // QTextCodec *langcodec=QTextCodec::codecForName("CP1251");
    // QTextCodec::setCodecForTr(langcodec);
    ui.setupUi(this);

    setWindowTitle(QString("PA%1mini-v%2.%3").arg(major).arg(minor).arg(patch));

    ui.progressBar->hide();
    solver = new Solver(this);
    connect( solver, SIGNAL(progressChanged(int)), ui.progressBar, SLOT(setValue(int)));

    connect(ui.loadSchemeButton, &QPushButton::clicked, this, &PAX_Prototype::loadSchemeSlot);
    connect(ui.saveSchemeButton, &QPushButton::clicked, this, &PAX_Prototype::saveSchemeSlot);
    connect(ui.saveSchemeAsButton, &QPushButton::clicked, this, &PAX_Prototype::saveSchemeAsSlot);
    connect(ui.settingButton, &QPushButton::clicked, this, &PAX_Prototype::showSettingsDialog);
    connect(ui.settingButton_2, &QPushButton::clicked, this, &PAX_Prototype::showSettingsDialog);
    connect(solver, &Solver::statusMessage, this, &PAX_Prototype::showStatusBarMessage);

    installEventFilter(this);
    plot = new PlotWindow;

    QSettings settings("PAXMINI", "CADCAMCAE6BMSTU");
    m_pathToMinGW = settings.value("MinGWPath").toString();

    m_statusBar = new QStatusBar();
    setStatusBar(m_statusBar);
    m_schemePath = "scheme.json";
}

PAX_Prototype::~PAX_Prototype()
{
    delete solver;
}

void PAX_Prototype::showStatusBarMessage(const QString &mesg)
{
    m_statusBar->showMessage(mesg);
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

    if ( event->type() == QEvent::Close )
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

    if (sender()->objectName() == "solveButton") {
        daeStr = ui.equalEdit->toPlainText().toStdString();
    } else {
        daeStr = ui.schemeView->getSystem().toStdString();
    }

    try {
        textDriver.parse_string(daeStr);
    } catch (TextDriverException e) {
        showErr(e.reason());
        return ;
    }

    SolverParam*  param = new SolverParam;
    param->exec();

    if (param->result() != QDialog::Accepted)
        return;

    QString name;
    if (sender()->objectName() == "solveButton") {
        name = ui.equalEdit->getFileName();
        int pos = name.lastIndexOf('/');
        name.remove(0, pos);
        name.prepend("output/");
        name.replace(".txt", ".csv");
    } else {
        name = m_schemePath;
        int pos = name.lastIndexOf('/');
        name.remove(0, pos);
        name.prepend("output/");
        name.replace(".json", ".csv");
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

    try {
        solver->solve(m_pathToMinGW);
    } catch(invalid_argument& e) {
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

void PAX_Prototype::showSettingsDialog()
{
    QSettings settings("PAXMINI", "CADCAMCAE6BMSTU");

    SettingsDialog *dialog = new SettingsDialog();

    dialog->setMinGWPath(settings.value("MinGWPath").toString());

    if (dialog->exec()) {
        m_pathToMinGW = dialog->getMinGWPath();
        settings.setValue("MinGWPath", m_pathToMinGW);
    }

    delete dialog;
}

void PAX_Prototype::saveSchemeSlot()
{
    if (m_schemePath.contains(".json", Qt::CaseInsensitive))
        saveScheme(m_schemePath);
}

void PAX_Prototype::loadSchemeSlot()
{
    m_schemePath = QFileDialog::getOpenFileName(this, tr("Открыть файл схемы"), m_schemePath, tr("JSON Files (*.json)"));
    loadScheme(m_schemePath);
}

void PAX_Prototype::saveSchemeAsSlot()
{
    m_schemePath = QFileDialog::getSaveFileName(this, tr("Сохранить файл схемы как"), m_schemePath, tr("JSON Files (*.json)"));

    if (!m_schemePath.endsWith(".json", Qt::CaseInsensitive))
        m_schemePath += ".json";

    saveScheme(m_schemePath);
}

void PAX_Prototype::saveScheme(const QString &path)
{
    QFile saveFile(path);

    auto items = ui.schemeView->scene()->items();

    if (! saveFile.open(QIODevice::WriteOnly)) {
        auto str = QString("Output file %1 wasn't opened on write").arg(path);
        qCritical() << str;
        m_statusBar->showMessage(str);
        return;
    }

    QJsonObject schemeObject;
    QJsonArray itemsArray;
    QJsonArray nodesArray;
    QJsonArray connectionArray;

    foreach (auto item, items) {
        CircuitItem *citem = nullptr;
        CircuitNodeItem *nitem = nullptr;
        citem = dynamic_cast<CircuitItem*>(item);
        if (citem) {
            itemsArray.append(citem->toJSON());
        } else if ((nitem = dynamic_cast<CircuitNodeItem*>(item))) {
            nodesArray.append(nitem->toJSON());
        }
    }

    schemeObject["Elements"] = itemsArray;
    schemeObject["Nodes"] = nodesArray;

    QJsonDocument saveDoc(schemeObject);
    saveFile.write(saveDoc.toJson());
}

void PAX_Prototype::loadScheme(const QString &path)
{
    QFile loadFile(path);

    if (! loadFile.open(QIODevice::ReadOnly)) {
        auto str = QString("Input file %1 wasn't opened on read").arg(path);
        qCritical() << str;
        m_statusBar->showMessage(str);
        return;
    }

    QByteArray loadData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(loadData));

    QJsonArray elementArray = loadDoc.object()["Elements"].toArray();

    for (int i = 0; i < elementArray.size(); ++i) {
        QJsonObject elementObject = elementArray[i].toObject();
        QString type = elementObject["type"].toString();
        QPoint pos(elementObject["x"].toInt(), elementObject["y"].toInt());
        if (type.compare("CircuitItem", Qt::CaseInsensitive) == 0) {
            QString fName = elementObject["fName"].toString();

            if (fName.compare("R", Qt::CaseInsensitive) == 0)
                ui.schemeView->addR(pos, elementObject["id"].toInt());
            else if (fName.compare("L", Qt::CaseInsensitive) == 0)
                ui.schemeView->addL(pos, elementObject["id"].toInt());
            else if (fName.compare("C", Qt::CaseInsensitive) == 0)
                ui.schemeView->addC(pos, elementObject["id"].toInt());
            else if (fName.compare("I", Qt::CaseInsensitive) == 0)
                ui.schemeView->addI(pos, elementObject["id"].toInt());
            else if (fName.compare("E", Qt::CaseInsensitive) == 0)
                ui.schemeView->addU(pos, elementObject["id"].toInt());
            else if (fName.compare("G", Qt::CaseInsensitive) == 0)
                ui.schemeView->addG(pos, elementObject["id"].toInt());
            ui.schemeView->lastElement()->fromJSON(elementObject);
        }
    }

    QJsonArray nodeArray = loadDoc.object()["Nodes"].toArray();
    for (int i = 0; i < nodeArray.size(); ++i) {
        QJsonObject elementObject = nodeArray[i].toObject();
        QString type = elementObject["type"].toString();
        QPoint pos(elementObject["x"].toInt(), elementObject["y"].toInt());

        if (type.compare("CircuitNodeItem", Qt::CaseInsensitive) == 0) {
            ui.schemeView->addNode(pos, elementObject["id"].toInt());
            ui.schemeView->lastNode()->fromJSON(elementObject);
        }
    }
}
