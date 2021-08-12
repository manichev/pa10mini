#include "pax_prototype.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdexcept>

#include "daesystem.h"
#include "textdriver.h"
#include "solver.h"
#include "manzhuk/manzhuk.h"

extern Solver* solver;

PAX_Prototype::PAX_Prototype(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	QTextCodec *langcodec=QTextCodec::codecForName("CP1251");
    QTextCodec::setCodecForTr(langcodec);
	ui.setupUi(this);
	ui.progressBar->hide();
	solver = new Solver(this);
	connect( solver, SIGNAL(progressChanged(int)), ui.progressBar, SLOT(setValue(int)));
	installEventFilter(this);
	plot = new PlotWindow;
}

PAX_Prototype::~PAX_Prototype()
{
	delete solver;
}

void PAX_Prototype::showErr(QString& message)
{
	QMessageBox msgBox;
	msgBox.setWindowTitle("Error");
	msgBox.setText(message);
	msgBox.exec();
}

bool PAX_Prototype::eventFilter(QObject *object, QEvent *event)
{
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

	if(	sender()->objectName() == "solveButton" )
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
	if(	sender()->objectName() == "solveButton" )
	{
		name = ui.equalEdit->getFileName();
		int pos = name.lastIndexOf('/');
		name.remove(0, pos);
		name.prepend("output/");
		name.replace(".txt", ".pa10");
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