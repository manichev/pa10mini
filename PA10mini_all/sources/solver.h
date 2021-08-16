#pragma once

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QProgressBar>
#include "daesystem.h"
#include "solverparam.h"
#include "manzhuk/manzhuk.h"

class Solver : public QObject
{
    Q_OBJECT
friend void global_outtask(double z[],double px[],int n,int m,double t,double t0,double tk,double h,double *tkv,int ncon,int ip[]);

public:
    Solver(QObject *parent);
    ~Solver(void);

    void solve();
    void setSystem(DAESystem* system_);

    double get_t0(void) { return t0; };
    void set_t0(double value) { t0 = value; };

    double get_tk(void) { return tk; };
    void set_tk(double value) { tk = value; };

    double get_hmn(void) { return hmn; };
    void set_hmn(double value) { hmn = value; };

    double get_hmx(void) { return hmx; };
    void set_hmx(double value) { hmx = value; };

    double get_eps(void) { return eps; };
    void set_eps(double value) { eps = value; };

    int get_nm(void) { return nm; };
    void set_nm(int value) { nm = value; };

    int get_n(void) { return n; };
    int get_m(void) { return m; };

    bool get_rj2_before(void) { return rj2_before; };
    void set_rj2_before(bool value) { rj2_before = value; };
    DAESystem* get_system(void){return system;};

    void set_outFileName(QString value) { outFileName = value; };

    QVector<QVector<double>> paxData;
    QVector<int> trace;
    QVector<QString> names;
    QVector<QString> dims;
protected:
    inline void outtask(double z[],double px[],int n,int m,double t,double t0,double tk,double h,double *tkv,int ncon,int ip[]);

signals:
    int progressChanged(int);

private:
    QFile* outFile;
    QTextStream* outTextStream;

    DAESystem* system;
    double t0, tk, hmn, hmx, eps;
    double tp, tout; //progress bar signal timing
    int n, m, nm;
    int maxMemSize, maxPoints;
    bool rj2_before;
    QString outFileName;
    bool writeFile;

    void create_fcttask();
};
