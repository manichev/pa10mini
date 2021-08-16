//fcttask.h

extern "C"
#if defined( WIN32 )
__declspec(dllexport)
#endif
void fcttask(double z[],double px[],double f[],double rj1[],double rj2[],int n,int m,double t,double h,int ncon,int *nbad,int ip[]);
