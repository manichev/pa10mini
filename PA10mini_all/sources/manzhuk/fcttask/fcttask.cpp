#include "fcttask.h"
#include <cmath>

void fcttask(double z[], double px[], double f[], double rj1[], double rj2[], int n, int m, double t, double h, int ncon, int *nbad, int ip[])
{
    f[1] = px[1]-z[2];
    rj1[1*n+1] = 1;
    f[2] = px[2]-((-1)*z[1]+1e+016*(1-pow(z[1], 2))*z[2]);
    rj1[2*n+2] = 1;
}
