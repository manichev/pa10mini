#include "ctest_manzhuk.h"
#include "manzhuk/manzhuk.h"

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

static ctest_ManZhuk ManZhukTest;
FILE *f01,*f02,*f03;

void global_fcttask(double *z, double *px, double *f, double *rj1, double *rj2, int n,
                    int m, double t, double h, int ncon, int *nbad, int *ip)
{
    switch (ManZhukTest.m_currentTest) {
    case Duffing:
        ManZhukTest.fcttaskDuff(z, px, f, rj1, rj2, n, m, t, h, ncon, nbad, ip);
        break;
    case LC:
        ManZhukTest.fcttaskLC(z, px, f, rj1, rj2, n, m, t, h, ncon, nbad, ip);
        break;
    case Dib15i:
        ManZhukTest.fcttaskDib(z, px, f, rj1, rj2, n, m, t, h, ncon, nbad, ip);
        /*if (ManZhukTest.Jdib == 1)
            ManZhukTest.fcttaskDibI1J1(z, px, f, rj1, rj2, n, m, t, h, ncon, nbad, ip);
        else if (ManZhukTest.Jdib == 2)
            ManZhukTest.fcttaskDibI1J2(z, px, f, rj1, rj2, n, m, t, h, ncon, nbad, ip);*/
        break;
    default:
        break;
    }
}

void global_outtask(double *z, double *px, int n, int m, double t, double t0,
                    double tk, double h, double *tkv, int ncon, int *ip)
{
    switch (ManZhukTest.m_currentTest) {
    case Duffing:
        ManZhukTest.outtaskDuff(z, px, n, m, t, t0, tk, h, tkv, ncon, ip);
        break;
    case LC:
        ManZhukTest.outtaskLC(z, px, n, m, t, t0, tk, h, tkv, ncon, ip);
        break;
    case Dib15i:
        ManZhukTest.outtaskDib(z, px, n, m, t, t0, tk, h, tkv, ncon, ip);
        break;
        default:
        break;
    }
}

ctest_ManZhuk::ctest_ManZhuk()
{
    pi4 = atan(1.0);
    eps = 1e-3;
}

void ctest_ManZhuk::initTestCase()
{

}

// "Static size" * factor
void ctest_ManZhuk::memalloc(int factor)
{
    rj1 = new double[250 * factor * factor];
    rj2 = new double[250 * factor * factor];
    ip = new int[10000 * factor];
    z = new double[50 * factor];
    px = new double[50 * factor];
    z1 = new double[50 * factor];
    xp1 = new double[50 * factor];
    f = new double[50 * factor];

    ki = new double[20 * factor];
    kAl = new double[20 * factor];
    kd = new double[20 * factor];
    kp = new double[20 * factor];
    C0 = new double[20 * factor];
    Cp0 = new double[20 * factor];

    y0 = new double[20 * factor];
    Y = new double[20 * factor];
    y1 = new double[20 * factor];
    y2 = new double[20 * factor];
    v0 = new double[20 * factor];
    v1 = new double[20 * factor];
    v2 = new double[20 * factor];
    P1 = new double[20 * factor];
    Pp1 = new double[20 * factor];
    P1I = new double[20 * factor];
    P1dI = new double[20 * factor];
    P1d = new double[20 * factor];
}

void ctest_ManZhuk::memfree()
{
    delete [] rj1;
    delete [] rj2;
    delete [] ip;
    delete [] z;
    delete [] px;
    delete [] z1;
    delete [] xp1;
    delete [] f;
    delete [] y0;
    delete [] Y;
    delete [] y1;
    delete [] y2;
    delete [] v0;
    delete [] v1;
    delete [] v2;
    delete [] P1;
    delete [] Pp1;
    delete [] P1I;
    delete [] P1dI;
    delete [] P1d;
}

void ctest_ManZhuk::tstDuffing()
{
    m_currentTest = Duffing;
    f01 = fopen("task001.rez", "wt");
    f02 = fopen("grtask001.csv", "wt");
    memalloc();
    om = 1e0;
    fprintf(f01, "        relative tolerance - eps=%e pi4=%e\n", eps, pi4);
    nm = 1;
    fprintf(f01, "        number of method - nm=%d\n", nm);
    t0 = 0e0;
    tk = 250e0;
    tstartp = 240e0;//time for start printing
    tendp = 245e0;//time for end printing
    deltatp = 1e0;//step for printing
    fprintf(f01, " tstartp=%e deltatp=%e tendp=%e\n", tstartp, deltatp, tendp);
    hmn = 1e-10;
    hmx = tk / 10e0;
    n = 2;
    m = 2;
    z[1] = 0e0;
    z[2] = 0e0;
    z1[1] = fabs(z[1]);
    z1[2] = fabs(z[2]);

    manzhuk(z, px, z1, xp1, f, rj1, rj2, t, t0, tk, h, hmn, hmx, eps,
            &tkv, n, m, nm, ncon, &nbad, &ier, ip, global_fcttask, global_outtask);

    fprintf(f01, "ier= %d \n", ier);
    printf("ier= %d \n", ier);
    for(i = 1; i <= 16; i++)
        fprintf(f01, "%d ", ip[i]);
    fprintf(f01, "\n");
    for(i = 1; i <= 16; i++)
        printf("%d ", ip[i]);
    printf("\n");
    fclose(f01);
    fclose(f02);
    memfree();
}

//task001 task002 - Duffing equation
void ctest_ManZhuk::fcttaskDuff(double z[], double px[], double f[], double rj1[],
                             double rj2[], int n, int m, double t, double h, int ncon, int *nbad, int *ip)
{
    (void)rj2; (void)(h); (void)(ncon); (void)(nbad); (void)(m); (void)(ip);

    f[1] = px[1]-z[2];
        rj1[1*n+1] = 1;
    f[2] = px[2]-0.5*z[1]+0.25*z[2]+0.5*z[1]*z[1]*z[1]-0.3*cos(t);
        rj1[2*n+2] = 1;
    return;
}
void ctest_ManZhuk::outtaskDuff(double *z, double *px, int n, int m, double t, double t0,
                             double tk, double h, double *tkv, int ncon, int *ip)
{
    (void)(n); (void)(m); (void)(tk); (void)(t0); (void)(h); (void)(ip);

    if (ncon == 0) fprintf(f01, "           Duffing equations, t, x1, x2, px1, px2\n");
    if (ncon == 0) fprintf(f02, "\"t\",  \"x1\",  \"x2\",  \"px1\",  \"px2\"\n");
    // Start print of tabulation results
    if (ncon == 0) tkp = deltatp;

    auto endPrint = [&]() {
        // End print of tabulation results
        fprintf(f02, "%e,   %e,  %e,  %e,  %e\n", t, z[1], z[2], px[1], px[2]);
        return;
    };

    if (deltatp == 0) {
        endPrint();
    }
    if (t <= tkp) {
        if ((tkp < *tkv) && (*tkv >= t))
            *tkv = tkp;
        if (t < tstartp)
            endPrint();
        if (t > tendp)
            endPrint();
        if (t == *tkv)
            fprintf(f01, "  %e   %e  %e  %e  %e\n", t, z[1], z[2], px[1], px[2]);
    }
    tkp = tkp + deltatp;
}

void ctest_ManZhuk::tstLC()
{
    m_currentTest = LC;
    f01 = fopen("taskLC.rez", "wt");
    f02 = fopen("grtaskLC.csv", "wt");
    memalloc();
    om = 1e0;
    fprintf(f01, "        relative tolerance - eps=%e pi4=%e\n", eps, pi4);
    nm = 3;
    fprintf(f01, "        number of method - nm=%d\n", nm);
    t0 = 0e0;
    tk = 10e0;
    tstartp = 0e0; //time for start printing
    tendp = 10e0; //time for end printing
    deltatp = 1e-1; //step for printing
    fprintf(f01, " tstartp=%e deltatp=%e tendp=%e\n", tstartp, deltatp, tendp);
    hmn = 1e-12;
    hmx = tk;
    n = 2;
    m = 2;
    z[1] = 0e0;
    z[2] = 0e0;
    z1[1] = fabs(z[1]);
    z1[2] = fabs(z[2]);

    manzhuk(z, px, z1, xp1, f, rj1, rj2, t, t0, tk, h, hmn, hmx, eps,
            &tkv, n, m, nm, ncon, &nbad, &ier, ip, global_fcttask, global_outtask);

    fprintf(f01, "ier= %d \n", ier);
    printf("ier= %d \n", ier);
    for(i = 1; i <= 16; i++)
        fprintf(f01, "%d ", ip[i]);
    fprintf(f01, "\n");
    for(i = 1; i <= 16; i++)
        printf("%d ", ip[i]);
    printf("\n");
    fclose(f01);
    fclose(f02);
    memfree();
}

void ctest_ManZhuk::fcttaskLC(double *z,double *px,double *f,double *rj1,double *rj2,
                       int n,int m,double t,double h,int ncon,int *nbad,int *ip)
{
/*k1:=1.0
k2:=1.0
x1'-k1*x2=0
x2'+k2*x1=0
x1==1
x2==0*/
    f[1] = px[1]-z[2];
    rj1[1*n+1] = 1;
    f[2] = px[2]+z[1]+1+z[2];
    rj1[2*n+2] = 1;
}

void ctest_ManZhuk::outtaskLC(double *z, double *px, int n,int m, double t, double t0,
                              double tk, double h, double *tkv, int ncon, int *ip)
{
    (void)(n); (void)(m); (void)(tk); (void)(t0); (void)(h); (void)(ip);

    if (ncon == 0)
        fprintf(f01, "LC ODE, t, x1, x2, px1, px2\n");
    if (ncon == 0)
        fprintf(f02, "\"t\",  \"x1\",  \"x2\",  \"px1\",  \"px2\"\n");
    // Start print of tabulation results
    if (ncon == 0)
        tkp = deltatp;

    auto endPrint = [&]() {
        // End print of tabulation results
        fprintf(f02, "%e,   %e,  %e,  %e,  %e\n", t, z[1], z[2], px[1], px[2]);
        return;
    };

    if (deltatp == 0)
        endPrint();

    if (t <= tkp) {
        if ((tkp < *tkv) && (*tkv >= t))
            *tkv = tkp;

        if (t < tstartp)
            endPrint();

        if (t > tendp)
            endPrint();

        if (t == *tkv)
            fprintf(f01, "  %e   %e  %e  %e  %e\n", t, z[1], z[2], px[1], px[2]);
    }
    tkp = tkp + deltatp;
}

void ctest_ManZhuk::tstDIB()
{
    double param[13] = {0, 2, 0.01, 0.05, 3.5, 1.2, 0.01, 0.05, 600, 1500, 0.000025, 0.000045, 0.22};

    memalloc(IZv);

    int k = 1;
    int Jdib_ini = 2;
    for (int i = 2; i <= (1 + Jdib_ini); ++i) {
        ki[k++] = param[i];
    }
    for (int i = (2 + Jdib_ini), k = 1; i <= (1 + 2 * Jdib_ini); ++i) {
        kAl[k++] = param[i];
    }

    for (int i = (2 + 2 * Jdib_ini) , k = 1; i <= (1 + 3 * Jdib_ini); ++i) {
        kd[k++] = param[i];
    }

    for (int i = (2 + 3 * Jdib_ini), k = 1; i <= (1 + 4 * Jdib_ini); ++i) {
        kp[k++] = param[i];
    }

    for (int i = (2 + 4 * Jdib_ini), k = 1; i <= (1 + 5 * Jdib_ini); ++i) {
        C0[k++] = param[i];
    }

    k = 1;
    for (int i = 1; i <= Jdib; ++i) {
        z[k++] = C0[i];
    }
    for (int i = 1; i <= Jdib; ++i) {
        z[k++] = y0[i];
    }
    z[k++] = M0;
    z[k++] = Al0;
    for (int i = 1; i <= Jdib; ++i) {
        z[k++] = Y[i];
    }
    for (int i = 1; i <= Jdib; ++i) {
        z[k++] = P1[i];
    }
    for (int i = 1; i <= Jdib * IZv; ++i) {
        z[k++] = P1I[i];
    }
    for (int i = 1; i <= Jdib; ++i) {
        z[k++] = P1d[i];
    }
    for (int i = 1; i <= Jdib * IZv; ++i) {
        z[k++] = P1dI[i];
    }

    Mp0 = 0;
    for (int i = 1; i <= Jdib; ++i) {
        Cp0[i] = -ki[Jdib] * C0[Jdib] * M0; // Верно ли это? ki и C0 не меняются
        Mp0 = Mp0 + ki[Jdib] * C0[Jdib] * M0;
        Pp1[i] = ki[Jdib] * C0[Jdib] * M0; // Верно ли это? ki и C0 не меняются
    }
    Mp0 = -Mp0;

    k = 1;
    for (int i = 1; i <= Jdib; ++i) {
        px[k++] = Cp0[i];
    }
    for (int i = 1; i <= Jdib; ++i) {
        px[k++] = y0[i];
    }
    px[k++] = Mp0;
    px[k++] = Al0;
    for (int i = 1; i <= Jdib; ++i) {
        px[k++] = Y[i];
    }
    for (int i = 1; i <= Jdib; ++i) {
        px[k++] = Pp1[i];
    }
    for (int i = 1; i <= Jdib * IZv; ++i) {
        px[k++] = P1I[i];
    }
    for (int i = 1; i <= Jdib; ++i) {
        px[k++] = P1d[i];
    }
    for (int i = 1; i <= Jdib * IZv; ++i) {
        px[k++] = P1dI[i];
    }

    m_currentTest = Dib15i;
    f01 = fopen("taskDib15i.rez", "wt");
    f02 = fopen("taskDib15i.csv", "wt");
    f03 = fopen("grtaskDib15i.csv", "wt");
    om = 1e0;
    fprintf(f01, "        relative tolerance - eps=%e pi4=%e\n", eps, pi4);
    nm = 3;
    fprintf(f01, "        number of method - nm=%d\n", nm);
    t0 = 0e0;
    tk = 100e0;
    tstartp = 0e0; //time for start printing
    tendp = 100e0; //time for end printing
    deltatp = 1e0; //step for printing
    fprintf(f01, " tstartp=%e deltatp=%e tendp=%e\n", tstartp, deltatp, tendp);
    hmn = 1e-10;
    // h = 1e-6;
    hmx = tk;
    m = n = 2 + (2 * IZv + 3) * Jdib;
    ncon = 2;
    ier = -1;
    z1[0] = 0; //fabs(z[0]);
    z1[1] = 0; //fabs(z[1]);
    z1[2] = 0; //fabs(z[2]);
    z1[3] = 0; //fabs(z[3]);
    z1[4] = 0; //fabs(z[4]);
    z1[5] = 0; //fabs(z[5]);
    z1[6] = 0; //fabs(z[6]);
    z1[7] = 0; //fabs(z[7]);
    z1[8] = 0; //fabs(z[8]);
    z1[9] = 0; //fabs(z[9]);
    z1[10] = 0; //fabs(z[10]);

    f[1]=0.1;
    f[2]=0.9;

    manzhuk(z, px, z1, xp1, f, rj1, rj2, t, t0, tk, h, hmn, hmx, eps,
            &tkv, n, m, nm, ncon, &nbad, &ier, ip, global_fcttask, global_outtask);

    fprintf(f01, "ier= %d \n", ier);
    printf("ier= %d \n", ier);
    for(i = 1; i <= 16; i++)
        fprintf(f01, "%d ", ip[i]);
    fprintf(f01, "\n");
    for(i = 1; i <= 16; i++)
        printf("%d ", ip[i]);
    printf("\n");
    fclose(f01);
    fclose(f02);
    fclose(f03);
    memfree();
}

inline void
ctest_ManZhuk::fcttaskDibI1J2(double *z, double *px, double *f, double *rj1, double *rj2,
                              int n, int m, double t, double h, int ncon, int *nbad, int *ip)
{
    f[1] = px[1] + ki[1] * z[1] * z[5] - kAl[1] * z[6] * z[3];
    rj1[1 * n + 1] = 1e0;
    rj2[1 * n + 1] = ki[1] * z[5];
    rj2[1 * n + 2] = 0;
    rj2[1 * n + 3] = - kAl[1] * z[6];
    rj2[1 * n + 5] = ki[1] * z[1];
    rj2[1 * n + 6] = - kAl[1] * z[3];

    f[2] = px[2] + ki[2] * z[2] * z[5] - kAl[2] * z[6] * z[3];
    rj1[2 * n + 2] = 1.0;
    rj2[2 * n + 2] = ki[2] * z[5];
    rj2[2 * n + 3] = - kAl[2] * z[6];
    rj2[2 * n + 5] = ki[2] * z[2];
    rj2[2 * n + 6] = - kAl[2] * z[3];


    f[3] = px[3] - ki[1] * z[1] * z[5] +
            kd[1] * z[3] + kAl[1] * z[6] * z[3];
    rj1[3 * n + 3] = 1.0;
    rj2[3 * n + 1] = - ki[1] * z[5];
    rj2[3 * n + 3] = kd[1] + kAl[1] * z[6];
    rj2[3 * n + 5] = - ki[1] * z[1];
    rj2[3 * n + 6] = kAl[1] * z[3];

    f[4] = px[4] - ki[2] * z[2] * z[5] +
            kd[2] * z[4] + kAl[2] * z[6] * z[4];
    rj1[4 * n + 4] = 1.0;
    rj2[4 * n + 2] = - ki[2] * z[5];
    rj2[4 * n + 4] = kd[2] + kAl[2] * z[6];
    rj2[4 * n + 5] = - ki[2] * z[2];
    rj2[4 * n + 6] = kAl[2] * z[4];

    double Sum1 = 0;
    Sum1 = ki[1] * z[1] * z[5] + ki[2] * z[2] * z[5];

    double Sum2 = 0;
    Sum2 = kp[1] * z[3] * z[5] + kp[2] * z[4] * z[5];

    f[5] = px[5] + ki[1] * z[1] * z[5] + ki[2] * z[2] * z[5] + kp[1] * z[3] * z[5] + kp[2] * z[4] * z[5];
    rj1[5 * n + 5] = 1.0;
    rj2[5 * n + 1] = ki[1] * z[5];
    rj2[5 * n + 2] = ki[2] * z[5];
    rj2[5 * n + 3] = kp[1] * z[5];
    rj2[5 * n + 4] = kp[2] * z[5];
    rj2[5 * n + 5] = ki[1] * z[1] + ki[2] * z[2] + kp[1] * z[3] + kp[2] * z[4];

    double Sum = 0;
    Sum += kAl[1] * z[3] * z[4];
    Sum += kAl[2] * z[4] * z[6];

    f[6] = px[6] + kAl[1] * z[3] * z[4] + kAl[2] * z[4] * z[6];
    rj1[6 * n + 6] = 1.0;
    rj2[6 * n + 3] = kAl[1] * z[4];
    rj2[6 * n + 4] = kAl[1] * z[3] + kAl[2] * z[6];
    rj2[6 * n + 6] = kAl[2] * z[4];


    f[7] = px[7] - kp[1] * z[3] * z[5];
    rj1[7 * n + 7] = 1.0;
    rj2[7 * n + 3] = - kp[1] * z[5];
    // rj2[7 * n + 7] = 1.0;
    rj2[7 * n + 5] = - kp[1] * z[3];

    f[8] = px[8] - kp[2] * z[4] * z[5];
    rj1[8 * n + 8] = 1.0;
    rj2[8 * n + 4] = - kp[2] * z[5];
    rj2[8 * n + 5] = - kp[2] * z[4];
    // rj2[8 * n + 8] = 1.0;

    f[9] = px[9] - ki[1] * z[1] * z[5] + kp[1] * z[9] * z[5] + kAl[1] * z[6] * z[9] + kd[1] * z[9];
    rj1[9 * n + 9] = 1.0;
    rj2[9 * n + 1] = - ki[1] * z[5];
    rj2[9 * n + 5] = kp[1] * z[9] - ki[1] * z[1];
    rj2[9 * n + 6] = kAl[1] * z[9];
    rj2[9 * n + 9] = kp[1] * z[5] + kAl[1] * z[6] + kd[1];

    f[10] = px[10] - ki[2] * z[2] * z[5] + kp[2] * z[10] * z[5] + kAl[2] * z[6] * z[10] + kd[2] * z[10];
    rj1[10 * n + 10] = 1.0;
    rj2[10 * n + 2] = - ki[2] * z[5];
    rj2[10 * n + 5] = - ki[2] * z[2] + kp[2] * z[10];
    rj2[10 * n + 6] = kAl[2] * z[10];
    rj2[10 * n + 10] = kp[2] * z[5] + kAl[2] * z[6] + kd[2];

    f[11] = px[11] - kAl[1] * z[6] * z[9] - kd[1] * z[9];
    rj1[11 * n + 11] = 1.0;
    rj2[11 * n + 6]  = - kAl[1] * z[9];
    rj2[11 * n + 9] = - kAl[1] * z[6] - kd[1];

    f[12] = px[12] - kAl[2] * z[6] * z[10] - kd[2] * z[10];
    rj1[12 * n + 12] = 1.0;
    rj2[12 * n + 6]  = - kAl[2] * z[10];
    rj2[12 * n + 10] = - kAl[2] * z[6] - kd[2];
}

inline void
ctest_ManZhuk::fcttaskDibI1J1(double *z, double *px, double *f, double *rj1, double *rj2,
                              int n, int m, double t, double h, int ncon, int* nbad, int ip[])
{
    // z[1]=C1, z[2]=y01,z[3]=M, z[4]=AL, z[5]=Y1, z[6]=P11, z[7]=P1d1
    f[1] = px[1] + ki[1] * z[1]*z[3] - kAl[1] * z[4] * z[2] ;
    rj1[1 * n + 1] = 1.0;

    rj2[1 * n + 1] = ki[1] * z[3];
    rj2[1 * n + 2] = -kAl[1] * z[4];
    rj2[1 * n + 3] = ki[1] * z[1];
    rj2[1 * n + 4] = -kAl[1] * z[2];

    f[2] = px[2] - ki[1] * z[1]*z[3] + kd[1] * z[2] + kAl[1] * z[4] * z[2];
    rj1[2 * n + 2] = 1.0;

    rj2[2 * n + 1] = -ki[1] * z[3];
    rj2[2 * n + 2] = kd[1] + kAl[1] * z[4];
    rj2[2 * n + 3] = -ki[1] * z[1];
    rj2[2 * n + 4] = kAl[1] * z[2];

    f[3] = px[3] + ki[1] * z[1] * z[3] + kp[1] * z[2] * z[3];
    rj1[3 * n + 3] = 1.0;

    rj2[3 * n + 1] = ki[1] * z[3];
    rj2[3 * n + 2] = kp[1] * z[3];
    rj2[3 * n + 3] = kp[1] * z[2];

    f[4] = px[4] + kAl[1] * z[2] * z[4];
    rj1[4 * n + 4] = 1.0;

    rj2[4 * n + 2] = kAl[1] * z[4];
    rj2[4 * n + 4] = kAl[1] * z[2];

    f[5] = px[5] - kp[1] * z[2] * z[3];
    rj1[5 * n + 5] = 1.0;

    rj2[5 * n + 2] = -kp[1] * z[3];
    rj2[5 * n + 3] = -kp[1] * z[2];

    f[6] = px[6] - ki[1] * z[1] * z[3] + kp[1] * z[6] * z[3] + kAl[1] * z[4] * z[6] + kd[1] * z[6];
    rj1[6 * n + 6] = 1.0;

    rj2[6 * n + 1] = -ki[1] * z[3];
    rj2[6 * n + 3] = -ki[1] * z[1] + kp[1] * z[6];
    rj2[6 * n + 4] = kAl[1] * z[6];
    rj2[6 * n + 6] = kp[1] * z[3] + kAl[1] * z[4]+ kd[1];

    f[7] = px[7] - kAl[1] * z[6] * z[4] - kd[1] * z[6];
    rj1[7 * n + 7] = 1.0;

    rj2[7 * n + 4] = -kAl[1] * z[6];
    rj2[7 * n + 6] = -kAl[1] * z[4]-kd[1];

    return;
}

inline void
ctest_ManZhuk::fcttaskDib(double *z, double *px, double *f, double *rj1, double *rj2,
                          int n, int m, double t, double h, int ncon, int *nbad, int *ip)
{
    int k = 1;
    for (int i = 1; i <= Jdib; ++i) {
        f[k++] = px[i] + ki[i] * z[i] * z[2 * Jdib + 1] - kAl[i] * z[2 * Jdib + 2] * z[Jdib + 1]; // А здесь ki идет по i // z[Jdib] - верно ли, что по j?
    }

    for (int i = Jdib + 1; i <= 2 * Jdib; ++i) {
        // xp(i)-ki(i-j)*x(i-j)*x(2*j+1)+kd(i-j)*x(i)+kAl(i-j)*x(2*j+2)*x(i)];
        f[k++] = px[i] - ki[i - Jdib] * z[i - Jdib] * z[2 * Jdib + 1] +
                kd[i - Jdib] * z[i] + kAl[i - Jdib] * z[2 * Jdib + 2] * z[i];
    }
    double Sum1 = 0;
    for (int i = 1; i <= Jdib; ++i) {
        Sum1 = Sum1 + ki[i] * z[i] * z[2 * Jdib + 1];
    }
    double Sum2 = 0;
    for (int i = 1; i <= Jdib; ++i) {
        Sum2 = Sum2 + kp[i] * z[Jdib + i] * z[2 * Jdib + 1];
    }
    f[k++] = px[2 * Jdib + 1] + Sum1 + Sum2;

    double Sum = 0;
    for (int i = 1; i <= Jdib; ++i) {
        Sum += kAl[i] * z[Jdib + i] * z[2 * i + 2];
    }
    f[k++] = px[2 * Jdib + 2] + Sum;

    for (int i = 2 * Jdib + 3; i <= (3 * Jdib + 2); ++i) {
        f[k++] = px[i] - kp[i - 2 * Jdib - 2] * z[i - Jdib - 2] * z[2 * Jdib + 1];
    }

    // rez = [rez; xp(i)-ki(i-3*j-2)*x(i-3*j-2)*x(2*j+1)+kp(i-3*j-2)*x(i)*x(2*j+1)+kAl(i-3*j-2)*x(2*j+2)*x(i)+kd(i-3*j-2)*x(i)];
    for (int i = (3 * Jdib + 3); i <= (4 * Jdib + 2); ++i) {
        f[k++] = px[i] - ki[i - 3 * Jdib - 2] * z[i - 3 * Jdib - 2] * z[2 * Jdib + 1] +
                kp[i - 3 * Jdib - 2] * z[i] * z[2 * Jdib + 1] +
                kAl[i - 3 * Jdib - 2] * z[2 * Jdib + 2] * z[i] + kd[i - 3 * Jdib - 2] * z[i];
    }

    for (int ii = 1; ii <= IZv - 1; ++ii) {
        for (int i = (3 + ii) * Jdib + 3; i <= ((4 + ii) * Jdib + 2); ++i) {
            f[k++] = px[i] - ki[i - (3 + ii) * Jdib - 2] * z[i - Jdib] * z[2 * Jdib + 1] +
                    kp[i - (3 + ii) * Jdib - 2] * z[i] * z[2 * Jdib + 1] +
                    kAl[i - (3 + ii) * Jdib - 2] * z[2 * Jdib + 2] * z[i] +
                    kd[i - (3 + ii) * Jdib - 2] * z[i];
        }
    }

    for (int i = (3 + IZv) * Jdib + 3; i <= ((4 + IZv) * Jdib + 2); ++i) {
        f[k++] = px[i] - kAl[i-(3 + IZv) * Jdib - 2] * z[2 * Jdib + 2] * z[i - IZv * Jdib] -
                kd[i - (3 + IZv) * Jdib - 2] * z[i - IZv * Jdib];
    }

    for (int i = 1; i <= n; i++) {
        rj1[i * n + i] = 1e0;
    }

    int AA, BB;
    for (int ii = 1; ii <= IZv - 1; ii++) {
        AA = (3 + IZv + ii) * Jdib + 3;
        BB = (4 + IZv + ii) * Jdib + 2;

        for (int i = AA; i <= BB; ++i) {
            f[k++] = px[i] - kAl[i - (3 + IZv + ii) * Jdib - 2] * z[2 * Jdib + 2] * z[i - IZv * Jdib] -
                    kd[i - (3 + IZv + ii) * Jdib - 2] * z[i - IZv * Jdib];
        }
    }
}

inline void ctest_ManZhuk::outtaskDib(double *z, double *px, int n, int m, double t, double t0,
                                      double tk, double h, double *tkv, int ncon, int *ip)
{
    (void)px; (void)(m); (void)(tk); (void)(t0); (void)(h); (void)(ip);

    if (ncon == 0) { // fprintf(f01, "t, x1, x2, x3, x4, x5, x6, x7\n");
        fprintf(f01, "t");
        fprintf(f02, "t");
        for (int i = 1; i <= n; ++i) {
            fprintf(f01, ", x%d", i);
            fprintf(f02, ",x%d", i);
        }
        fprintf(f01, "\n");
        fprintf(f02, "\n");
    }
    if (ncon == 0)
        fprintf(f03, "\"t\",  \"x1\",  \"x2\",  \"x3\",  \"x4\",  \"x5\",  \"x6\",  \"x7\"\n");

    // Start print of tabulation results
    if (ncon == 0)
        tkp = deltatp;

    auto endPrint = [&]() {
        // End print of tabulation results
        fprintf(f03, " %e   %e  %e  %e  %e %e  %e  %e\n", t, z[1], z[2], z[3], z[4], z[5], z[6], z[7]);
        return;
    };

    if (deltatp == 0)
        endPrint();

    if (t <= tkp) {
        if ((tkp < *tkv) && (*tkv >= t))
            *tkv = tkp;

        if (t < tstartp)
            endPrint();

        if (t > tendp)
            endPrint();

        if (t == *tkv) {
            fprintf(f01, "%e,", t);
            fprintf(f02, "%e,", t);
            for (int i = 1; i < n; ++i) {
                fprintf(f01, " %e", z[i]);
                fprintf(f02, "%e,", z[i]);
            }
            fprintf(f01, " %e", z[n]);
            fprintf(f02, "%e", z[n]);
            fprintf(f01, "\n");
            fprintf(f02, "\n");
        }
    }

    tkp = tkp + deltatp;
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "C");

    ManZhukTest.initTestCase();
    ManZhukTest.tstDuffing();
    printf("\nDuffing test - PASS\n");
    ManZhukTest.tstLC();
    printf("\nLC test - PASS\n");
    ManZhukTest.tstDIB();
    printf("\nDIB test - PASS\n");

    return 0;
}
