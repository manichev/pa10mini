#ifndef PAX_PROTOTYPE_H
#define PAX_PROTOTYPE_H

#include <QMainWindow>
#include <QTextCodec>
#include <QProgressBar>
#include <QListWidget>
#include <QDebug>
#include <QMessageBox>
#include "ui_pax_prototype.h"
#include "solverparam.h"
#include "variablechooser.h"
#include "plotwindow.h"

class PAX_Prototype : public QMainWindow
{
	Q_OBJECT

public:
    PAX_Prototype(QWidget *parent = nullptr, Qt::WindowFlags flags = 0);
    ~PAX_Prototype() override;
public slots:
	void activateSchemeMode();
	void activateEqualMode();
	void schemeToText();
	void solve();
	void openPlot();
    void showErr(const QString &message);

protected:
    bool eventFilter(QObject *object, QEvent *event) override;

private:
	Ui::PAX_PrototypeClass ui;
    PlotWindow* plot;
};


#endif // PAX_PROTOTYPE_H
