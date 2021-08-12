#include <stdexcept>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <io.h>

#include "solver.h"

//global variable;
Solver* solver;

Solver::Solver(QObject *parent)
	: QObject(parent)
{
//default values of solver parameters
	t0 = 0.0;
	tk = 240.0;
	hmn = 1e-16;
	hmx = 1e16;
	eps = 1e-3;
	nm = 3;
	rj2_before = false;
	writeFile = false;
	maxMemSize = 1024*1024*2;
}

void Solver::setSystem(DAESystem* system_)
{
	system = system_;
	system->updateAllIds();
	Variable variable;
	names.clear();
	trace.clear();
	dims.clear();
	QVector<QString> dnames;
	foreach(variable, system->variables)
	{
		names.append(QString::fromStdString(variable.name));
		if(variable.isDerivative)
			dnames.append(QString::fromStdString(variable.name) + "'");
	}
	names+=dnames;
}

void Solver::outtask(double z[],double px[],int n,int m,double t,double t0,double tk,double h,double *tkv,int ncon,int ip[])
{
	if(writeFile) {
		QString line;
		line.append(" ");
		line.append(QString::number(t, 'e'));
		for(int i = 0; i < trace.size(); ++i)
		{
			line.append(" ");
			if(trace[i] > n)
				line.append(QString::number(px[trace[i]-n], 'e'));
			else
				line.append(QString::number(z[trace[i]], 'e'));
		}
		line.append("\n");
		*outTextStream << line;
	}
	if( t >= tout )
	{
		paxData[0].append(t);
		for(int i = 0; i < trace.size(); ++i)
		{
			if(trace[i] > n)
				paxData[i+1]+=px[trace[i]-n];
			else
				paxData[i+1]+=z[trace[i]];
		}
		tout+= (tk-t0)/maxPoints;
	}
	
	if( t>=tp )
	{
		tp += (tk-t0)/100;
		emit progressChanged((int)((t-t0)/(tk-t0)*100));
	}
}

void global_outtask(double z[],double px[],int n,int m,double t,double t0,double tk,double h,double *tkv,int ncon,int ip[])
{
	solver->outtask(z, px, n, m, t, t0, tk, h, tkv, ncon, ip);
}

int progressChanged(int value)
{
	return value;
}

void Solver::create_fcttask()
{
	ofstream file;
	file.open("manzhuk/fcttask/fcttask.cpp");

	file << "#include \"fcttask.h\"\n";
	file << "#include <cmath>\n\n";
	file << "void fcttask(double z[], double px[], double f[], double rj1[], double rj2[], int n, int m, double t, double h, int ncon, int *nbad, int ip[])\n";
	file << "{\n";

	std::list<Expression*>::iterator eqIt;
	Expression* der;
	int i = 1;
	for(eqIt = system->equals.begin(); eqIt != system->equals.end(); ++eqIt)
	{
		file << "\tf[" << i << "] = ";
		(*eqIt)->simplify();
		(*eqIt)->print_c_ostream(file);
		file << ";\n";
		for(int j = 1; j <= m; ++j)
		{
			der = (*eqIt)->derivative(-j);
			if( !der->isConst(0.0) )
			{
				file << "\trj1[" << i << "*n+"<< + j << "] = ";
				der->print_c_ostream(file);
				file << ";\n";
			}
		}
		if(rj2_before)
		{
			for(int j = 1; j <= n; ++j)
			{
				der = (*eqIt)->derivative(j);
				if( !der->isConst(0.0) )
				{
					file << "\trj2[" << i << "*n+"<< + j << "] = ";
					der->print_c_ostream(file);
					file << ";\n";
				}
			}
		}
		++i;
	}
	file << "}";
	file.close();

	//compiling fcttask.dll
	remove("manzhuk/fcttask/fcttask.dll");
	std::system("manzhuk\\fcttask\\build.cmd");
	//removing extra files
	remove("manzhuk/fcttask/fcttask.lib");
	remove("manzhuk/fcttask/fcttask.exp");
	remove("fcttask.obj");
}


void Solver::solve()
{
	double *z, *px, *z1, *px1, *f, *rj1, *rj2;
	double t, h, tkv;

	int ncon, nbad, ier, *ip;
	if(writeFile)
	{
		outFile = new QFile(outFileName);
		if (!outFile->open(QIODevice::WriteOnly | QIODevice::Text))
			return;
		outTextStream = new QTextStream(outFile);
	}

	n = system->countEquals();
	m = system->countDerivatives();
	//if(system->countVariables() > system->countEquals())
	//	throw invalid_argument("NM!");
//allocating memory
	z = new double[n+1];
	px = new double[m+1];
	z1 = new double[n+1];
	px1 = new double[m+1];
	f = new double[n+1];
	rj1 = new double[(n+1)*(n+1)];
	rj2 = new double[(n+1)*(n+1)];
	ip = new int[20+2*(n+1)+6*(m+1)];
	paxData.clear();
	paxData.resize(trace.size()+1);
	
//initializing values
	t = 0.0;
	h = 0.0;
	ncon = 0;
	nbad = 1;

	ier = rj2_before ? 0 : -1;

	maxPoints = maxMemSize/(sizeof(double)*paxData.size());
	tout = t0 + (tk - t0)/maxPoints;
	tp = t0 + (tk-t0)/100;

create_fcttask();
//applying dll
	HINSTANCE dll = LoadLibrary(L"manzhuk/fcttask/fcttask.dll");
	void (* fcttask)(double*, double*, double*, double*, double*, int, int, double, double, int, int*, int*) =
		(void (*)(double*, double*, double*, double*, double*, int, int, double, double, int, int*, int*))GetProcAddress(dll, "fcttask");	
//solving with manzhuk
	std::list<Variable>::iterator it;
	std::cout.precision(3);
		for(int i = 1; i <= n; ++i)
			z1[i] = z[i] = 0.0;

	for(it = system->variables.begin(); it != system->variables.end(); ++it)
	{
		z[it->id] = it->initial;
		z1[it->id] = fabs(z[it->id]);
		std::cout<<it->name<< " ["<<it->id<<"] "<<" = "<<it->initial<<"\n";
	}
	for(int i = 1; i <= m; ++i)
		px[i] = px1[i] = 0.0;
	
//int stdout_copy = _dup(1);
//_close(1);
//int file1 = open("out.txt", 0);

	manzhuk(z, px, z1, px1, f, rj1, rj2, t, t0, tk, h, hmn, hmx, eps, &tkv, n, m, nm, ncon, &nbad, &ier, ip, fcttask, global_outtask);

//_close(file1);
//_dup2(stdout_copy, 1);
//_close(stdout_copy);

//free dll
	FreeLibrary(dll);
//free memory
	delete z;
	delete px;
	delete z1;
	delete px1;
	delete f;
	delete rj1;
	delete rj2;
	if(writeFile)
	{
		outFile->close();
		delete outFile;
		delete outTextStream;
	}
}


Solver::~Solver(void)
{
}
