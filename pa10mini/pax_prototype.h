#ifndef PAX_PROTOTYPE_H
#define PAX_PROTOTYPE_H

#include <QMainWindow>
#include <QTextCodec>
#include <QProgressBar>
#include <QListWidget>
#include <QDebug>
#include <QMessageBox>
#include <memory>
#include "ui_pax_prototype.h"
#include "daesystem.h"
#include "solverparam.h"
#include "variablechooser.h"
#include "plotwindow.h"

class PAX_Prototype : public QMainWindow
{
	Q_OBJECT

public:
    PAX_Prototype(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::Widget);
    ~PAX_Prototype() override;
public slots:
	void activateSchemeMode();
	void activateEqualMode();
	void schemeToText();
	void solve();
	void openPlot();
    void showErr(const QString &message);

private slots:
    void saveSchemeSlot();
    void saveSchemeAsSlot();
    void loadSchemeSlot();
    void showSettingsDialog();
    void showStatusBarMessage(const QString &mesg);
    void showAboutDialog();
    void onSolveFinished(bool success, const QString &message);

private:
    void saveScheme(const QString &path);
    void loadScheme(const QString &path);

private:
	Ui::PAX_PrototypeClass ui;
    PlotWindow* plot;
    QString m_schemePath;
    QString m_pathToMinGW;
    QStatusBar *m_statusBar;
    std::unique_ptr<DAESystem> m_activeSystem;
};

#endif // PAX_PROTOTYPE_H
