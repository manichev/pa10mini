#include "tst_manzhuk.h"
#include "manzhuk/manzhuk.h"

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <QObject>
#include <QtTest/qtest.h>

static tst_ManZhuk ManZhukTest;
FILE *f01,*f02;

void global_fcttask(double z[], double px[], double f[], double rj1[], double rj2[], int n,
                    int m, double t, double h, int ncon, int *nbad, int ip[])
{
    switch (ManZhukTest.m_currentTest) {
    case Duffing:
        ManZhukTest.fcttask001(z, px, f, rj1, rj2, n, m, t, h, ncon, nbad, ip);
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

void global_outtask(double z[], double px[], int n, int m, double t, double t0,
                    double tk, double h, double *tkv, int ncon, int ip[])
{
    switch (ManZhukTest.m_currentTest) {
    case Duffing:
        ManZhukTest.outtask001(z, px, n, m, t, t0, tk, h, tkv, ncon, ip);
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

tst_ManZhuk::tst_ManZhuk()
{
    pi4 = atan(1.0);
    eps = 1e-3;
}

void tst_ManZhuk::initTestCase()
{

}

void tst_ManZhuk::tstDuffing()
{
    m_currentTest = Duffing;
    f01 = fopen("task001.rez", "wt");
    f02 = fopen("grtask001.csv", "wt");
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
}
/*
 * k1:=0.5
k2:=0.25
k3:=0.3
kt:=1.0
x1'-x2=0
x2'-k1*x1+k2*x2+k1*x1*x1*x1-k3*cos(kt*t)=0
x1==0
x2==0
 */
//task001 task002 - Duffing equation
void tst_ManZhuk::fcttask001(double z[], double px[], double f[], double rj1[],
                             double rj2[], int n, int m, double t, double h, int ncon, int *nbad, int ip[])
{
    Q_UNUSED(h); Q_UNUSED(ncon); Q_UNUSED(nbad); Q_UNUSED(m); Q_UNUSED(ip)

    /*f[1] = px[1] - z[2];
        rj1[1 * n + 1] = 1e0;
        rj2[1*n+2] = -1e0;
    f[2] = px[2] - 0.5 * z[1] + 0.25e0 * z[2] + 0.5e0 * z[1] * z[1] * z[1] - 0.3 * cos(om * t);
        rj1[2 * n + 2] = 1e0;
        rj2[2 * n + 1] = -0.5e0 + 1.5e0 * z[1] * z[1];
        rj2[2 * n + 2] = 0.25e0;*/
    f[1] = px[1]-z[2];
        rj1[1*n+1] = 1;
    f[2] = px[2]-0.5*z[1]+0.25*z[2]+0.5*z[1]*z[1]*z[1]-0.3*cos(t);
        rj1[2*n+2] = 1;
    return;
}
void tst_ManZhuk::outtask001(double z[], double px[], int n, int m, double t, double t0,
                             double tk, double h, double *tkv, int ncon, int ip[])
{
    Q_UNUSED(n); Q_UNUSED(m); Q_UNUSED(tk); Q_UNUSED(t0); Q_UNUSED(h); Q_UNUSED(ip)

    if (ncon == 0) fprintf(f01, "           Duffing equations, t, x1, x2, px1, px2\n");
    if (ncon == 0) fprintf(f02, "\"t\",  \"x1\",  \"x2\",  \"px1\",  \"px2\"\n");
    // Start print of tabulation results
    if (ncon == 0) tkp = deltatp;
    if (deltatp == 0) goto m20;
    if (t <= tkp) goto m10;
    tkp = tkp + deltatp;

m10:
    if ((tkp < *tkv) && (*tkv >= t)) *tkv = tkp;
    if (t < tstartp) goto m20;
    if (t > tendp) goto m20;
    if (t == *tkv) fprintf(f01, "  %e   %e  %e  %e  %e\n", t, z[1], z[2], px[1], px[2]);

m20:
    // End print of tabulation results
    fprintf(f02, "%e,   %e,  %e,  %e,  %e\n", t, z[1], z[2], px[1], px[2]);
    return;
}

void tst_ManZhuk::tstLC()
{
    m_currentTest = LC;
    f01 = fopen("taskLC.rez", "wt");
    f02 = fopen("grtaskLC.csv", "wt");
    om = 1e0;
    fprintf(f01, "        relative tolerance - eps=%e pi4=%e\n", eps, pi4);
    nm = 3;
    fprintf(f01, "        number of method - nm=%d\n", nm);
    t0 = 0e0;
    tk = 10e0;
    tstartp = 0e0;//time for start printing
    tendp = 10e0;//time for end printing
    deltatp = 1e-1;//step for printing
    fprintf(f01, " tstartp=%e deltatp=%e tendp=%e\n", tstartp, deltatp, tendp);
    hmn = 1e-12;
    hmx = tk;
    n = 2;
    m = 2;
    z[1] = 0e0;
    z[2] = 0e0;
    /*z[3] = 0;
    z[4] = 0;
    z[5] = 0;
    z[6] = 0;
    z[7] = 0;
    z[8] = 0;*/
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
}

void tst_ManZhuk::fcttaskLC(double z[],double px[],double f[],double rj1[],double rj2[],
                       int n,int m,double t,double h,int ncon,int *nbad,int ip[])
{
/*k1:=1.0
k2:=1.0
x1'-k1*x2=0
x2'+k2*x1=0
x1==1
x2==0*/
    /*f[1] = px[1]-z[2];
    rj1[1*n+1] = 1;
    f[2] = px[2]+z[1];
    rj1[2*n+2] = 1;*/
    /*f[1] = px[1]-z[2];
    rj1[1*n+1] = 1;
    f[2] = px[2]-((-1)*z[1]+1e16*(1-pow(z[1], 2))*z[2]);
    rj1[2*n+2] = 1;*/
    f[1] = px[1]-z[2];
    rj1[1*n+1] = 1;
    f[2] = px[2]+z[1]+1+z[2];
    rj1[2*n+2] = 1;
    /*f[1] = z[7]-1;
    f[2] = z[7]-z[5];
    f[3] = z[3]-px[2];
    rj1[3*n+2] = -1;
    f[4] = z[2]-z[6];
    f[5] = z[8]-px[1];
    rj1[5*n+1] = -1;
    f[6] = z[8]-(z[5]-z[6]);
    f[7] = z[4]+z[1];
    f[8] = z[3]-z[1];*/
}

void tst_ManZhuk::outtaskLC(double z[],double px[],int n,int m,double t,double t0,
                       double tk,double h,double *tkv,int ncon,int ip[])
{
    Q_UNUSED(n); Q_UNUSED(m); Q_UNUSED(tk); Q_UNUSED(t0); Q_UNUSED(h); Q_UNUSED(ip)

    if (ncon == 0) fprintf(f01, "LC ODE, t, x1, x2, px1, px2\n");
    if (ncon == 0) fprintf(f02, "\"t\",  \"x1\",  \"x2\",  \"px1\",  \"px2\"\n");
    // Start print of tabulation results
    if (ncon == 0) tkp = deltatp;
    if (deltatp == 0) goto m20;
    if (t <= tkp) goto m10;
    tkp = tkp + deltatp;

m10:
    if ((tkp < *tkv) && (*tkv >= t)) *tkv = tkp;
    if (t < tstartp) goto m20;
    if (t > tendp) goto m20;
    if (t == *tkv) fprintf(f01, "  %e   %e  %e  %e  %e\n", t, z[1], z[2], px[1], px[2]);

m20:
    // End print of tabulation results
    fprintf(f02, "%e,   %e,  %e,  %e,  %e\n", t, z[1], z[2], px[1], px[2]);
    return;
}

void tst_ManZhuk::tstDIB()
{
    double param[13] = {0, 2, 0.01, 0.05, 3.5, 1.2, 0.01, 0.05, 600, 1500, 0.000025, 0.000045, 0.22};

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
    f02 = fopen("grtaskDib15i.csv", "wt");
    om = 1e0;
    fprintf(f01, "        relative tolerance - eps=%e pi4=%e\n", eps, pi4);
    nm = 3;
    fprintf(f01, "        number of method - nm=%d\n", nm);
    t0 = 0e0;
    tk = 100e0;
    tstartp = 0e0;//time for start printing
    tendp = 100e0;//time for end printing
    deltatp = 1e0;//step for printing
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
}

inline void tst_ManZhuk::fcttaskDibI1J2(double z[],double px[],double f[],double rj1[],double rj2[],
                       int n,int m,double t,double h,int ncon,int *nbad,int ip[])
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


    // ii = 1, i = 11
    /*f[11] = px[11] - ki[1] * z[9] * z[5] + kp[1] * z[11] * z[5] + kAl[1] * z[6] * z[11] + kd[1] * z[11];
    rj1[11 * n + 11] = 1.0;
    rj2[11 * n + 5] = - ki[1] * z[9] + kp[1] * z[11];
    rj2[11 * n + 6] = kAl[1] * z[11];
    rj2[11 * n + 9] = - ki[1] * z[5];
    rj2[11 * n + 11] = kp[1] * z[5] + kAl[1] * z[6] + kd[1];

    // ii = 1, i = 12
    f[12] = px[12] - ki[2] * z[10] * z[5] + kp[2] * z[12] * z[5] + kAl[2] * z[6] * z[12] + kd[2] * z[12];
    rj1[12 * n + 12] = 1.0;
    rj2[12 * n + 5] = - ki[2] * z[10] + kp[2] * z[12];
    rj2[12 * n + 6] = kAl[2] * z[12];
    rj2[12 * n + 10] = - ki[2] * z[5];
    rj2[12 * n + 12] = kp[2] * z[5] + kAl[2] * z[6] + kd[2];*/

    // ii = 2, i = 13
    // f[13] = px[13] - ki[3] * z[11] * z[5] + kp[3] * z[13] * z[5] + kAl[3] * z[6] * z[13] + kd[3] * z[13];
    // ii = 2, i = 14
    // f[14] = px[14] - ki[4] * z[12] * z[5] + kp[4] * z[14] * z[5] + kAl[4] * z[6] * z[14] + kd[4] * z[14];

    f[11] = px[11] - kAl[1] * z[6] * z[9] - kd[1] * z[9];
    rj1[11 * n + 11] = 1.0;
    rj2[11 * n + 6]  = - kAl[1] * z[9];
    rj2[11 * n + 9] = - kAl[1] * z[6] - kd[1];

    f[12] = px[12] - kAl[2] * z[6] * z[10] - kd[2] * z[10];
    rj1[12 * n + 12] = 1.0;
    rj2[12 * n + 6]  = - kAl[2] * z[10];
    rj2[12 * n + 10] = - kAl[2] * z[6] - kd[2];

    /*int AA, BB;
    AA = 15;
    BB = 16;

    f[15] = px[15] - kAl[1] * z[6] * z[13] - kd[1] * z[13];
    rj1[15 * n + 15] = 1.0;
    rj2[15 * n + 6] = - kAl[1] * z[13];
    rj2[15 * n + 13] = - kAl[1] * z[6] - kd[1];

    f[16] = px[16] - kAl[2] * z[6] * z[14] - kd[2] * z[14];
    rj1[16 * n + 16] = 1.0;
    rj2[16 * n + 6] = - kAl[2] * z[14];
    rj2[16 * n + 14] = - kAl[2] * z[6] - kd[2];*/
}

void tst_ManZhuk::fcttaskDibI1J1(double z[], double px[], double f[], double rj1[], double rj2[], int n, int m, double t, double h, int ncon, int* nbad, int ip[])
{
    // z[1]=C1, z[2]=y01,z[3]=M, z[4]=AL, z[5]=Y1, z[6]=P11, z[7]=P1d1
    f[1] = px[1] + ki[1] * z[1]*z[3] - kAl[1] * z[4] * z[2] ;
    rj1[1 * n + 1] = 1.0;

    rj2[1 * n + 1] = ki[1] * z[3];
    rj2[1 * n + 2] = -kAl[1] * z[4];
    rj2[1 * n + 3] = ki[1] * z[1];
    rj2[1 * n + 4] = -kAl[1] * z[2];

    f[2] = px[2] - ki[1] * z[1]*z[3] + kd[1]  * z[2] + kAl[1] * z[4] * z[2];
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

    f[6] = px[6] - ki[1] * z[1] * z[3] + kp[1] * z[3] + kAl[1] * z[4] * z[6] + kd[1] * z[6];
    rj1[6 * n + 6] = 1.0;

    rj2[6 * n + 1] = -ki[1] * z[3];
    rj2[6 * n + 3] = -ki[1] * z[1] + kp[1];
    rj2[6 * n + 4] = kAl[1] * z[6];
    rj2[6 * n + 6] = kAl[1] * z[4]+ kd[1];

    f[7] = px[7] - kAl[1] * z[6] * z[4] - kd[1] * z[6];
    rj1[7 * n + 7] = 1.0;

    rj2[7 * n + 4] = -kAl[1] * z[6];
    rj2[7 * n + 6] = -kAl[1] * z[4]-kd[1];

    return;
}

void tst_ManZhuk::fcttaskDib(double z[],double px[],double f[],double rj1[],double rj2[],
                       int n,int m,double t,double h,int ncon,int *nbad,int ip[])
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

    rj1[1] = 1e0;
    rj1[1*n+1] = 1e0;
    rj1[2*n+2] = 1e0;
    rj1[3*n+3] = 1e0;
    rj1[4*n+4] = 1e0;
    rj1[5*n+5] = 1e0;
    rj1[6*n+6] = 1e0;
    rj1[7*n+7] = 1e0;
    rj1[8*n+8] = 1e0;
    rj1[9*n+9] = 1e0;
    rj1[10*n+10] = 1e0;
    rj1[11*n+11] = 1e0;
    rj1[12*n+12] = 1e0;
    rj1[13*n+13] = 1e0;
    rj1[14*n+14] = 1e0;
    rj1[15*n+15] = 1e0;
    rj1[16*n+16] = 1e0;
    rj1[17*n+17] = 1e0;
    rj1[18*n+18] = 1e0;
    rj1[19*n+19] = 1e0;

    int AA, BB;
    for (int ii = 1; ii <= IZv - 1; ii++) {
        AA = (3 + IZv + ii) * Jdib + 3;
        BB = (4 + IZv + ii) * Jdib + 2;

        for (int i = AA; i < BB; ++i) {
            f[k++] = px[i] - kAl[i - (3 + IZv + ii) * Jdib - 2] * z[2 * Jdib + 2] * z[i - IZv * Jdib] -
                    kd[i - (3 + IZv + ii) * Jdib - 2] * z[i - IZv * Jdib];
        }
    }
}

void tst_ManZhuk::outtaskDib(double z[],double px[],int n,int m,double t,double t0,
                       double tk,double h,double *tkv,int ncon,int ip[])
{
    Q_UNUSED(n); Q_UNUSED(m); Q_UNUSED(tk); Q_UNUSED(t0); Q_UNUSED(h); Q_UNUSED(ip)

    if (ncon == 0) fprintf(f01, "t, x1, x2, x3, x4, x5, x6, x7\n");
    if (ncon == 0) fprintf(f02, "\"t\",  \"x1\",  \"x2\",  \"x3\",  \"x4\"\n");
    // Start print of tabulation results
    if (ncon == 0) tkp = deltatp;
    if (deltatp == 0) goto m20;
    if (t <= tkp) goto m10;
    tkp = tkp + deltatp;

m10:
    if ((tkp < *tkv) && (*tkv >= t)) *tkv = tkp;
    if (t < tstartp) goto m20;
    if (t > tendp) goto m20;
    if (t == *tkv) fprintf(f01, " %e %e %e %e %e %e  %e  %e\n", t, z[1], z[2], z[3], z[4], z[5], z[6], z[7]);

m20:
    // End print of tabulation results
    fprintf(f02, " %e   %e  %e  %e  %e %e  %e  %e\n", t, z[1], z[2], z[3], z[4], z[5], z[6], z[7]);
    return;
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setAttribute(Qt::AA_Use96Dpi, true);
    QTEST_SET_MAIN_SOURCE_PATH
    return QTest::qExec(&ManZhukTest, argc, argv);
}
