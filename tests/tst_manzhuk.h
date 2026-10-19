#include "manzhuk/manzhuk.h"

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <QObject>
#include <QtTest/qtest.h>

enum TestName {
    Notest, Duffing, LC, RC, RLC, VanDerPole, Dib15i
};

class tst_ManZhuk : public QObject
{
    Q_OBJECT
public:
    explicit tst_ManZhuk();
    friend void global_fcttask(double *z,double *px,double *f,double *rj1,double *rj2,
                               int n,int m,double t,double h,int ncon,int *nbad,int *ip);
    friend void global_outtask(double *z,double *px,int n,int m,double t,double t0,
                               double tk,double h,double *tkv,int ncon,int *ip);

private slots:
    void initTestCase();
    void tstDuffing();
    void tstLC();
    void tstDIB();

private:
    //task001 task002 - Duffing equation
    inline void fcttaskDuff(double *z,double *px,double *f,double *rj1,double *rj2,
                           int n,int m,double t,double h,int ncon,int *nbad,int *ip);
    inline void outtaskDuff(double *z,double *px,int n,int m,double t,double t0,
                           double tk,double h,double *tkv,int ncon,int *ip);

    inline void fcttaskLC(double *z,double *px,double *f,double *rj1,double *rj2,
                           int n,int m,double t,double h,int ncon,int *nbad,int *ip);
    inline void outtaskLC(double *z,double *px,int n,int m,double t,double t0,
                           double tk,double h,double *tkv,int ncon,int *ip);

    inline void fcttaskDib(double *z,double *px,double *f,double *rj1,double *rj2,
                           int n,int m,double t,double h,int ncon,int *nbad,int *ip);
    inline void outtaskDib(double *z,double *px,int n,int m,double t,double t0,
                           double tk,double h,double *tkv,int ncon,int *ip);

    inline void fcttaskDibI1J2(double *z,double *px,double *f,double *rj1,double *rj2,
                           int n,int m,double t,double h,int ncon,int *nbad,int *ip);

    inline void fcttaskDibI1J1(double *z,double *px,double *f,double *rj1,double *rj2,
                           int n,int m,double t,double h,int ncon,int *nbad,int *ip);

    void memalloc(int factor = 1); // "Static size" * factor
    void memfree();

public:
    TestName m_currentTest = Notest;
    int IZv = 10;
    int Jdib = 2;

private:
    // Common variables for manzhuk ODE systems solver
    // double rj1[2500], rj2[2500];
    double *rj1, *rj2;
    double t, t0, tk, h, hmn, hmx, eps, tkv; // z[500], px[500], z1[500], xp1[500], f[500],
    double *z, *px, *z1, *xp1, *f;
    int n, nm, m, ncon, nbad, ier, *ip; //ip[10000];
    // FILE *f01,*f02;
    // Tasks&tests for ODE sets
    int i;
    double pi4, om, tstartp, tendp, deltatp, tkp;
    double mu0, mu1;
    double c1, c2, l, r;
    double mu;
    double c01, c02, c03, l01, l02, l03, a;
    double b, g, a1, a11, a12, a13, a21, a22, a23, a31, a32, a33;

    // Dib problem
    // double ki[200], kAl[200], kd[200], kp[200], C0[200], Cp0[200];
    double *ki, *kAl, *kd, *kp, *C0, *Cp0;
    double M0 = 1.5, Mp0 = 0;
    double Al0 = 0.012;
    // double y0[200], Y[200], y1[200], y2[200], v0[200], v1[200], v2[200], P1[200], Pp1[200], P1I[200], P1dI[200], P1d[200];
    double *y0, *Y, *y1, *y2, *v0, *v1, *v2, *P1, *Pp1, *P1I, *P1dI, *P1d;
    int TotalTime = 100;
};
