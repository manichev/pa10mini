#include "manzhuk/manzhuk.h"

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <QObject>
#include <QtTest/qtest.h>

enum TestName {
    Notest, Duffing, RC, RLC, VanDerPole
};

class tst_ManZhuk : public QObject
{
    Q_OBJECT
public:
    explicit tst_ManZhuk();
    friend void global_fcttask(double z[],double px[],double f[],double rj1[],double rj2[],int n,int m,double t,double h,int ncon,int *nbad,int ip[]);
    friend void global_outtask(double z[],double px[],int n,int m,double t,double t0,double tk,double h,double *tkv,int ncon,int ip[]);

private slots:
    void initTestCase();
    void tstDuffing();

private:
    //task001 task002 - Duffing equation
    inline void fcttask001(double z[],double px[],double f[],double rj1[],double rj2[],int n,int m,double t,double h,int ncon,int *nbad,int ip[]);
    inline void outtask001(double z[],double px[],int n,int m,double t,double t0,double tk,double h,double *tkv,int ncon,int ip[]);

public:
    TestName m_currentTest = Notest;

private:
    // Common variables for manzhuk ODE systems solver
    double rj1[2500], rj2[2500];
    double z[50], px[50], z1[50], xp1[50], f[50], t, t0, tk, h, hmn, hmx, eps, tkv;
    int n, nm, m, ncon, nbad, ier, ip[10000];
    FILE *f01,*f02;
    // Tasks&tests for ODE sets
    int i;
    double pi4, om, tstartp, tendp, deltatp, tkp;
    double mu0, mu1;
    double c1, c2, l, r;
    double mu;
    double c01, c02, c03, l01, l02, l03, a;
    double b, g, a1, a11, a12, a13, a21, a22, a23, a31, a32, a33;
};

//#include "tst_manzhuk.moc"
