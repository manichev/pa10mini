#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <limits>

auto DOUBLE_EPS1 = std::numeric_limits<double>::min();

 void dlur(int,int,int,int,int,int,int,int,int,int,int,double ar[],int ip[],double,int*);
 void dlur1(int,int,int,int,int,int,int,int,int,int,double*,int*,double,double,double,double,double,int*);
 void dpoh(int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,double*,int*,double,double,double,double,double,int*);


//common variables for manzhuk ODE systems solver
extern    double rj1[],rj2[];
extern  double z[],px[],z1[],xp1[],f[],t,t0,tk,h,hmn,hmx,eps,tkv;
extern  int n,nm,m,ncon,nbad,ier,ip[];
extern    FILE *f01,*f02;
/*_____________________________________________________________________

     PROCEDURE     DLUR DLUR1 DPOH   
  _____________________________________________________________________*/
void dlur(int n,int m,int na11,int nj,int nb,int nbxp,int ndz,int nzr,int ndx,int nxr,int nip,double ar[],int ip[],double ah,int *ier)
{
 double rm,ra,r1,con0,conmst;
 int ki1,i,kk,m1,m2,k,kl1,nl2,ir1,nal,n1,n2,nl1,kl2,nu1,nau;
 int kau,kp,nu2,ikl,ku1,ku2,ilu,npa,kpa,ik,il;
 int ir3,ill,jp2,jp1,ir,jpa2,jpa1,iu,iru3,itu;
 int inz,inb,in1,ik1,in2,ina,i1,inzr;
       con0=0e0;
       conmst=1e-200;
       ki1=nip+n;
       for(i=nip+1;i<=ki1;i++) ip[i]=i-nip;
       n1=(n-1)*n+nj;
       n2=2*n;
       m1=(m-1)*n+na11;
       m2=na11-nj;
       for(k=1;k<=n;k++)
    { kl1=k*n+nj;
      ir1=kl1-n;
      kk=ir1+k;
      nal=kk+m2;
      nl2=kk+1;
      nl1=ir1+1;
      kl2=kk-1;
      nu1=kl1+k;
      nau=nu1+m2;
      kau=m1+k;
      kp=n1+k;
      nu2=k+nj;
      ikl=nu2-1;
      ku1=kp;
      ku2=kk-n;
      ilu=nl1;
      npa=na11+k;
      kpa=kau;
      rm=con0;
      ik=k;
      for(il=kk;il<=kl1;il++)
       { r1=con0;
         if(k==1) goto u15;
         ikl=ikl+1;
         ir3=ikl;
         for(ill=nl1;ill<=kl2;ill++)
        {r1=r1+ar[ir3]*ar[ill];
            ir3=ir3+n;}
u15:           if(k>m) goto u20;
         r1=r1+ar[nal]*ah;
         nal=nal+1;
u20:          ar[il]=ar[il]-r1;
         ra=fabs(ar[il]);
         if(rm>ra) goto u25;
         ik=il-ir1;
         rm=ra;
u25:           ;}
      if(k==n) goto u65;
      if(ik==k) goto u40;
      ir=ip[k+nip];
      ip[k+nip]=ip[ik+nip];
      ip[ik+nip]=ir;
      jp2=ik+nj;
      for(jp1=nu2;jp1<=kp;jp1=jp1+n)
        {r1=ar[jp1];
         ar[jp1]=ar[jp2];
         ar[jp2]=r1;
         jp2=jp2+n;}
      jpa2=ik+na11;
      for(jpa1=npa;jpa1<=kpa;jpa1=jpa1+n)
       { r1=ar[jpa1];
         ar[jpa1]=ar[jpa2];
         ar[jpa2]=r1;
         jpa2=jpa2+n;}
u40:      ;
    for(il=nl2;il<=kl1;il++)
        { if(fabs(ar[kk])<conmst) goto u1000;
          ar[il]=ar[il]/ar[kk];
      }
      for(iu=nu1;iu<=ku1;iu=iu+n)
        { r1=con0;
         if(k==1) goto u55;
         ilu=ilu+n;
         iru3=ilu;
         for(itu=nu2;itu<=ku2;itu=itu+n)
        {r1=r1+ar[itu]*ar[iru3];
             iru3=iru3+1;}
u55:           if(nau>kau) goto u60;
         r1=r1+ar[nau]*ah;
         nau=nau+n;
u60:           ar[iu]=ar[iu]-r1;
        }
u65:        ;}
    for(i=1;i<=m;i++) ar[i+nxr]=ar[i+nbxp];
    inz=nzr+1;
    for(i=1;i<=n;i++)
      { inb=nb+ip[i+nip];
       r1=con0;
       if(i==1) goto u80;
       in1=i+nj;
       ik1=n*i-n2+in1;
       in2=nzr+1;
       for(ir=in1;ir<=ik1;ir=ir+n)
         { r1=r1+ar[ir]*ar[in2];
           in2=in2+1;}
u80:         ina=i+na11;
       for(i1=1;i1<=m;i1++)
         { r1=r1+ar[ina]*ar[i1+nxr];
           ina=ina+n;}
       ar[inz]=ar[inb]-r1;
       inz=inz+1;}
    inz=ndz+n+1;
    inzr=nzr+n;
    for(i=n;i>=1;i--)
      { inz=inz-1;
       r1=con0;
       kk=n*i-n+i+nj;
       if(i==n) goto u100;
       ik1=kk+n;
       in1=n1+i;
       in2=ndz+n;
       for(ir=in1;ir>=ik1;ir=ir-n)
         { r1=r1+ar[ir]*ar[in2];
           in2=in2-1;}
u100:        if(fabs(ar[kk])<conmst) goto u1000;
        ar[inz]=(ar[inzr]-r1)/ar[kk];
        inzr=inzr-1;}
       for(i=1;i<=m;i++) ar[i+ndx]=ar[i+nxr]-ar[i+ndz]*ah;
       return;
u1000:       (*ier)=8;
       return;
}

void dlur1(int n,int m,int na11,int nj,int nip,int na22,int nj1,int nip1,int na21,int na12,double ar[],int ip[],double a11,double a12,double a21,double a22,double ah,int *ier)
{
double rm,ra,r1,con0,conmst;
int ki1,ki2,i,n1n,m1n,k,kn,k1n,kl1,kk,nal,nl2,ir1,kl2,nu1;
int nau,kau,kp,nu2,ikl,ku1,ku2,ilu,nl1,npa,kpa;
int kka21,kl1a21,nl2a21,ikla21,nu1a12,ku1a12,ilua12; //,npa12,kpa12;
int naua,ik,il,ir3,ill,nala,ir,jp2,jp1,jpa1,jpa2;
int iu,iru3,itu,nl1a12,kl2a12,npa21,kpa21,nu2a21,ku2a21,jpa21,jp21;
      con0=0e0;
       conmst=1e-200;
       ki1=nip+n;
       ki2=nip1+n;
       for(i=nip+1;i<=ki1;i++) ip[i]=i-nip;
       for(i=nip1+1;i<=ki2;i++) ip[i]=i-nip1;
       n1n=(n-1)*n;
       m1n=(m-1)*n;
       for(k=1;k<=n;k++)
     {
      kn=k*n;
      k1n=(k-1)*n;
      kl1=kn+nj;
      ir1=kl1-n;
      kk=ir1+k;
      nal=k1n+k+na11;
      nl2=kk+1;
      nl1=ir1+1;
      kl2=kk-1;
      nu1=kl1+k;
      nau=kn+k+na11;
      kau=m1n+k+na11;
      kp=n1n+k+nj;
      nu2=k+nj;
      ikl=nu2-1;
      ku1=kp;
      ku2=kk-n;
      ilu=nl1;
      npa=k+na11;
      kpa=kau;
      kka21=k1n+1+na21;
      kl1a21=k1n+n+na21;
      nl2a21=kka21;
      ikla21=na21;
      nu1a12=k+na12;
      ku1a12=m1n+k+na12;
      ilua12=1-n+na12;
      // npa12=k+na12; // ToDo: doesn't used
      // kpa12=m1n+na12; // ToDo: doesn't used
      naua=k+na11;
      rm=con0;
      ik=k;
      for(il=kk;il<=kl1;il++)
      {
         r1=con0;
         if(k==1) goto r20;
         ikl=ikl+1;
         ir3=ikl;
         for(ill=nl1;ill<=kl2;ill++)
         {
            r1=r1+ar[ir3]*ar[ill];
            ir3=ir3+n;
         }
r20:           if(k>m) goto r25;
         r1=r1+ar[nal]*a11*ah;
         nal=nal+1;
r25:           ar[il]=ar[il]-r1;
         ra=fabs(ar[il]);
         if(rm>ra) goto r30;
         ik=il-ir1;
         rm=ra;
r30:           ;}
         nala=k1n+1+na22;
         for(il=kka21;il<=kl1a21;il++)
          {
        r1=con0;
        if(k==1) goto r40;
        ikla21=ikla21+1;
        ir3=ikla21;
        for(ill=nl1;ill<=kl2;ill++)
        {
          r1=r1+ar[ir3]*ar[ill];
          ir3=ir3+n;
        }
r40:              if(k>m) goto r45;
        r1=r1+ar[nala]*a21*ah;
        nala=nala+1;
r45:              ar[il]=ar[il]-r1;
            }
      if(k==n) goto r90;
      if(ik==k) goto r65;
      ir=ip[k+nip];
      ip[k+nip]=ip[ik+nip];
      ip[ik+nip]=ir;
      jp2=ik+nj;
      for(jp1=nu2;jp1<=kp;jp1=jp1+n)
       { r1=ar[jp1];
         ar[jp1]=ar[jp2];
         ar[jp2]=r1;
         jp2=jp2+n;}
      jpa2=ik+na11;
      for(jpa1=npa;jpa1<=kpa;jpa1=jpa1+n)
        { r1=ar[jpa1];
         ar[jpa1]=ar[jpa2];
         ar[jpa2]=r1;
         jpa2=jpa2+n;}
r65:        for(il=nl2;il<=kl1;il++)
       { if(fabs(ar[kk])<conmst) goto r1000;
         ar[il]=ar[il]/ar[kk];}
      for(iu=nu1;iu<=ku1;iu=iu+n)
      {
         r1=con0;
         if(k==1) goto r80;
         ilu=ilu+n;
         iru3=ilu;
         for(itu=nu2;itu<=ku2;itu=itu+n)
           {r1=r1+ar[itu]*ar[iru3];
             iru3=iru3+1;}
r80:           if(nau>kau) goto r85;
         r1=r1+ar[nau]*a11*ah;
         nau=nau+n;
r85:          ar[iu]=ar[iu]-r1;}
r90:        for(il=nl2a21;il<=kl1a21;il++)
     {  if(fabs(ar[kk])<conmst) goto r1000;
          ar[il]=ar[il]/ar[kk];}
      for(iu=nu1a12;iu<=ku1a12;iu=iu+n)
          {    r1=con0;
        if(k==1) goto r105;
        ilua12=ilua12+n;
        iru3=ilua12;
        for(itu=nu2;itu<=ku2;itu=itu+n)
        {  r1=r1+ar[itu]*ar[iru3];
               iru3=iru3+1;}
r105:             if(naua>kau) goto r110;
        r1=r1+ar[naua]*a12*ah;
        naua=naua+n;
r110:             ar[iu]=ar[iu]-r1;}
      }
      for(k=1;k<=n;k++)
      {
      kn=k*n;
      k1n=(k-1)*n;
      kl1=kn+nj1;
      ir1=kl1-n;
      kk=ir1+k;
      nal=k1n+k+na22;
      nl2=kk+1;
      nl1=ir1+1;
      kl2=kk-1;
      nu1=kl1+k;
      nau=kn+k+na22;
      kau=m1n+k+na22;
      kp=n1n+k+nj1;
      nu2=k+nj1;
      ikl=nu2-1;
      ku1=kp;
      ku2=kk-n;
      ilu=nl1;
      npa=k+na22;
      kpa=kau;
      nl1a12=k1n+1+na12;
      kl2a12=k1n+n+na12;
      ikla21=k-1+na21;
      npa21=k+na21;
      kpa21=n1n+k+na21;
      ilua12=k1n+1+na12;
      nu2a21=k+na21;
      ku2a21=n1n+k+na21;
      rm=con0;
      ik=k;
      for(il=kk;il<=kl1;il++)
        {
         r1=con0;
         if(k==1) goto r125;
         ikl=ikl+1;
         ir3=ikl;
         for(ill=nl1;ill<=kl2;ill++)
          {    r1=r1+ar[ir3]*ar[ill];
            ir3=ir3+n;}
r125:          if(k>m) goto r135;
         r1=r1+ar[nal]*a22*ah;
         nal=nal+1;
         ikla21=ikla21+1;
         ir3=ikla21;
         for(ill=nl1a12;ill<=kl2a12;ill++)
           { r1=r1+ar[ir3]*ar[ill];
            ir3=ir3+n;}
r135:          ar[il]=ar[il]-r1;
         ra=fabs(ar[il]);
         if(rm>ra) goto r140;
         ik=il-ir1;
         rm=ra;
r140:          ;}
      if(k==n) goto r190;
      if(ik==k) goto r160;
      ir=ip[k+nip1];
      ip[k+nip1]=ip[ik+nip1];
      ip[ik+nip1]=ir;
      jp2=ik+nj1;
      for(jp1=nu2;jp1<=kp;jp1=jp1+n)
        { r1=ar[jp1];
         ar[jp1]=ar[jp2];
         ar[jp2]=r1;
         jp2=jp2+n;}
      jpa2=ik+na22;
      for(jpa1=npa;jpa1<=kpa;jpa1=jpa1+n)
        { r1=ar[jpa1];
         ar[jpa1]=ar[jpa2];
         ar[jpa2]=r1;
         jpa2=jpa2+n;}

      jpa21=ik+na21;
      for(jp21=npa21;jp21<=kpa21;jp21=jp21+n)
        { r1=ar[jp21];
         ar[jp21]=ar[jpa21];
         ar[jpa21]=r1;
          jpa21=jpa21+n;}
r160:       for(il=nl2;il<=kl1;il++)
       {if(fabs(ar[kk])<conmst) goto r1000;
          ar[il]=ar[il]/ar[kk];}
     for(iu=nu1;iu<=ku1;iu=iu+n)
        {
         r1=con0;
         if(k==1) goto r175;
         ilu=ilu+n;
         iru3=ilu;
         for(itu=nu2;itu<=ku2;itu=itu+n)
           {r1=r1+ar[itu]*ar[iru3];
             iru3=iru3+1;}
r175:          if(nau>kau) goto r185;
         r1=r1+ar[nau]*a22*ah;
         nau=nau+n;
         ilua12=ilua12+n;
         iru3=ilua12;
         for(itu=nu2a21;itu<=ku2a21;itu=itu+n)
           { r1=r1+ar[itu]*ar[iru3];
            iru3=iru3+1;}
r185:          ar[iu]=ar[iu]-r1;}
r190:       ;}
      return;
r1000:      (*ier)=8;
      return;
}
void dpoh(int n,int m,int na11,int nj,int nb,int nbxp,int ndz,int nzr,int ndx,int nxr,int nip,int na22,int nj1,int nb1,int nbxp1,int ndz1,int nzr1,int ndx1,int nxr1,int nip1,int na21,int na12,double ar[],int ip[],double a11,double a12,double a21,double a22,double ah,int *ier)
{
 int n1n,n2,i,inz,inb,in1,ik1,in2,ina,i1,ir,inzr,kk,ia12,ia;
 double r1,con0,conmst;
    con0=0e0;
    conmst=1e-200;
    n1n=(n-1)*n;
    n2=2*n;
    for(i=1;i<=m;i++) ar[i+nxr]=ar[i+nbxp];
    for(i=1;i<=m;i++) ar[i+nxr1]=ar[i+nbxp1];
    inz=nzr+1;
    for(i=1;i<=n;i++)
     {
       inb=nb+ip[i+nip];
       r1=con0;
       if(i==1) goto p20;
       in1=i+nj;
       ik1=n*i-n2+in1;
       in2=nzr+1;
       for(ir=in1;ir<=ik1;ir=ir+n)
         { r1=r1+ar[ir]*ar[in2];
        in2=in2+1;}
p20:         ina=i+na11;
       for(i1=1;i1<=m;i1++)
         { r1=r1+ar[ina]*ar[i1+nxr];
        ina=ina+n;}
       ar[inz]=ar[inb]-r1;
       inz=inz+1;}
    inz=nzr1+1;
    for(i=1;i<=n;i++)
     {
       inb=nb1+ip[i+nip1];
       r1=con0;
       if(i==1) goto p40;
       in1=i+nj1;
       ik1=n*i-n2+in1;
       in2=nzr1+1;
       for(ir=in1;ir<=ik1;ir=ir+n)
         { r1=r1+ar[ir]*ar[in2];
           in2=in2+1;}
p40:         ina=i+na22;
       for(i1=1;i1<=m;i1++)
         { r1=r1+ar[ina]*ar[i1+nxr1];
           ina=ina+n;}
       ina=i+na21;
       for(i1=1;i1<=n;i1++)
          {r1=r1+ar[ina]*ar[i1+nzr];
           ina=ina+n;}
       ar[inz]=ar[inb]-r1;
       inz=inz+1;}
    inz=ndz1+n+1;
    inzr=nzr1+n;
    for(i=n;i>=1;i--)
    {
       inz=inz-1;
       r1=con0;
       kk=n*i-n+i+nj1;
       if(i==n) goto p65;
       ik1=kk+n;
       in1=n1n+nj1+i;
       in2=ndz1+n;
       for(ir=in1;ir>=ik1;ir=ir-n)
        {  r1=r1+ar[ir]*ar[in2];
           in2=in2-1;}
p65:       if(fabs(ar[kk])<conmst) goto p1000;
       ar[inz]=(ar[inzr]-r1)/ar[kk];
       inzr=inzr-1;}
       inz=ndz+n+1;
       inzr=nzr+n;
       for(i=n;i>=1;i--)
       {
          inz=inz-1;
          r1=con0;
          kk=n*i-n+i+nj;
          if(i==n) goto p80;
          ik1=kk+n;
          in1=n1n+nj+i;
          in2=ndz+n;
          for(ir=in1;ir>=ik1;ir=ir-n)
        { r1=r1+ar[ir]*ar[in2];
              in2=in2-1;}
p80:            ia12=i+na12;
          for(ia=1;ia<=m;ia++)
        { r1=r1+ar[ia12]*ar[ia+ndz1];
              ia12=ia12+n;}
         if(fabs(ar[kk])<conmst) goto p1000;
          ar[inz]=(ar[inzr]-r1)/ar[kk];
          inzr=inzr-1;}
  for(i=1;i<=m;i++) ar[i+ndx1]=ar[i+nxr1]-(ar[i+ndz]*a21+ar[i+ndz1]*a22)*ah;
  for(i=1;i<=m;i++) ar[i+ndx]=ar[i+nxr]-(ar[i+ndz]*a11+ar[i+ndz1]*a12)*ah;
       return;
p1000:       (*ier)=8;
       return;
}
/*_____________________________________________________________________

      procedure           manzhuk        
  _____________________________________________________________________*/

void manzhuk(double z[],double px[],double z1[],double xp1[],double f[],
                   double rj1[],double rj2[],double t, double t0,double tk,
                   double h,double hmn,double hmx,double eps,double *tkv,
                   int n,int m,int nm,int ncon,int *nbad,int *ier,int ip[],
     void fct(double z[],double px[],double f[],double rj1[],double rj2[],
     int n,int m,double t,double h, int ncon,int *nbad,int ip[]),
     void out(double z[],double px[],int n,int m,double t,double t0,double tk,
     double h,double *tkv,int ncon,int ip[]))
{
 double ar[10000];
 int i,j,nmz,nzn,nxn,nxnm2,nxnm3,nzt,nzt1,nzt2,nzt3,nzt4,nzt5;
 int nmz1,na11,nj,na22,nj1,nbxp,nbxp1,nb,nb1,na12,na21,nxr,nxr1;
 int nzr,nzr1,ndx,ndx1,ndz,ndz1,ndar,ndar1,ndarx,nfs,ndzs,ndxs;
 int nlkk,nip,nip1,ii,ia;
 int ipm,ipk,ipkp,ipnu,ih,ih1,ih2,ih3,ipkv,iprh,kolf,kolil,
 ipkor,prwar,sn1,sn2,lkt,lkt1,lkt2,nsm4,ipsav,iprp;
 double tn,tt,ttn,ht,hpred;
 double ah,a11,a12,a21,a22,b1,b2,tv,fcon,fnm,fdz,fp,dp,fconp;
 double r0,r11,r12,r13,r14,r15,r21,r22,r23,r24,r31,r32,r33,
 r41,r42,r51,rxn,rxnm1,rxnm2,rxnm3,ve,vt,vm,zv1,zv2;
 double h1,h2,h3,h4,h5,hv1,hv2;
 double epsp,epd4,epd8,epd16,epd32,epd64,epd128,etr,em4,ee;
 double ra0,ra1,ra2,ra3,ra4,rafp,rafc,radz,radzp;
 double ra11,ra12,ra13,ra14,ra15,ra21,ra22,ra23,ra24,ra31,
 ra32,ra33,ra41,ra42,ra51;
 double con0,con1,con2,con4,con5,con6,con8,con16,con20,con32;
 double con64,con128,cont1,con1t1,con1t2,con1t3,con1t5;
 double conm3,conm7,conm12,conm14,conmst,conmd;

i=j=nmz=nzn=nxn=nxnm2=nxnm3=nzt=nzt1=nzt2=nzt3=nzt4=nzt5=0;
nmz1=na11=nj=na22=nj1=nbxp=nbxp1=nb=nb1=na12=na21=nxr=nxr1=0;
nzr=nzr1=ndx=ndx1=ndz=ndz1=ndar=ndar1=ndarx=nfs=ndzs=ndxs=0;
nlkk=nip=nip1=ii=ia=0;
ipm=ipk=ipkp=ipnu=ih=ih1=ih2=ih3=ipkv=iprh=kolf=kolil=0;
ipkor=prwar=sn1=sn2=lkt=lkt1=lkt2=nsm4=ipsav=iprp=0;
tn=tt=ttn=ht=hpred=0.0e0;
ah=a11=a12=a21=a22=b1=b2=tv=fcon=fnm=fdz=fp=dp=fconp=0.0e0;
r0=r11=r12=r13=r14=r15=r21=r22=r23=r24=r31=r32=r33=0.0e0;
r41=r42=r51=rxn=rxnm1=rxnm2=rxnm3=ve=vt=vm=zv1=zv2=0.0e0;
h1=h2=h3=h4=h5=hv1=hv2=0.0e0;
epsp=epd4=epd8=epd16=epd32=epd64=epd128=etr=em4=ee=0.0e0;
ra0=ra1=ra2=ra3=ra4=rafp=rafc=radz=radzp=0.0e0;
ra11=ra12=ra13=ra14=ra15=ra21=ra22=ra23=ra24=ra31=ra32=ra33=ra41=ra42=ra51=0.0e0;
con0=con1=con2=con4=con5=con6=con8=con16=con20=con32=0.0e0;
con64=con128=cont1=con1t1=con1t2=con1t3=con1t5=0.0e0;
conm3=conm7=conm12=conm14=conmst=conmd=0.0e0;

con0=0e0;con1=1e0;con2=2e0;con4=4e0;con5=5e0;
con6=6e0;con8=8e0;con16=16e0;con20=20e0;con32=32e0;con64=64e0;
con128=128e0;cont1=0.1e0;con1t1=1.1e0;con1t2=1.2e0;con1t3=1.3e0;
con1t5=1.5e0;conm3=1e-3;conm12=1e-12;conmst=1e-200;
a11=-2e0;a12=-0.5e0;a21=8e0;a22=-4e0;b1=2.5e0;b2=-4e0;

         t=t0;
     tn=t0;
     iprp=0;
     if((*ier)==-1)
         iprp=1;
     (*ier)=0;
     if(n<=0||m<0||m>n) (*ier)=1;
     if(hmn<=conmst||hmn>hmx) (*ier)=2;
     if((tk-t0)<hmn) (*ier)=3;
     if(eps<=conm12) (*ier)=4;
     if(nm<1||nm>4) (*ier)=5;
     if(ncon<0||ncon>2) (*ier)=6;
     if(ncon==1&&nmz!=3) (*ier)=6;
     if((*ier)!=0)
         goto d590;
     epsp=eps;
     epd4=epsp/con4;
     epd8=epsp/con8;
     epd16=epsp/con16;
     epd32=epsp/con32;
     epd64=epsp/con64;
     epd128=epsp/con128;
     if(ncon==1)
         goto d20;
//printf("\nMANZHUK-DAE-Solver - http://www.bmstu.ru/ps/~manichev/ \n");
     ih=0;
     if(ncon==2) ih=1;
     ra0=1.41;
     r0=-0.3;
     ra3=2;
     for(i=1;i<=20;i++)
     {
         ra2=ra0*ra0;
         ra1=ra2-ra3;
         ra2=ra1*r0;
         ra0=ra0+ra2;
     }
      conm14=con16*(fabs(ra1)+fabs(ra2))/2e0;
//fprintf(f01," conm14 = %15.8e \n\n",conm14);
      conm7=sqrt(conm14);
      conmd=conm7;
      nmz=3;
      nzn=nmz+n;
      nxn=nzn+n;
      nxnm2=nxn+m;
      nxnm3=nxnm2+m;
      nzt=nxnm3+m;
      nzt1=nzt+m;
      nzt2=nzt1+m;
      nzt3=nzt2+m;
      nzt4=nzt3+m;
      nzt5=nzt4+m;
      nmz1=nzt5+m;
      na11=nmz1+n;
      nj=na11+n*m;
      na22=nj+n*n;
      nj1=na22+n*m;
      nbxp=nj1+n*n;
      nbxp1=nbxp+m;
      nb=nbxp1+m;
      nb1=nb+n;
      na12=nb1+n;
      na21=na12+n*n;
      nxr=na21+n*n;
      nxr1=nxr+m;
      nzr=nxr1+m;
      nzr1=nzr+n;
      ndx=nzr1+n;
      ndx1=ndx+m;
      ndz=ndx1+m;
      ndz1=ndz+n;
      ndar=ndz1+n;
      ndar1=ndar+m;
      ndarx=ndar1+m;
      nfs=ndarx+m;
      ndzs=nfs+2*n;
      ndxs=ndzs+2*n;
      nlkk=21;
      nip=nlkk+n;
      nip1=nip+n;
      for(i=1;i<=20+2*n+m;i++)
          ip[i]=0;
      for(i=1;i<=2*n*m+4*n*n+15*n+18*m+4;i++)
          ar[i]=con0;
      h=hmn;
      if(ih==0&&n>m)
      {
          for(i=m+1;i<=n;i++)
              z[i]=con0;
          for(i=1;i<=m;i++)
              px[i]=con0;
      }
      for(i=1;i<=n;i++)
        for(j=1;j<=m;j++) rj1[i*n+j]=con0;
      for(i=1;i<=n;i++)
        for(j=1;j<=n;j++) rj2[i*n+j]=con0;
      for(i=1;i<=n;i++)
      {
        f[i]=conmd;
        if(fabs(z[i])>conmst)
            f[i]=conmd*fabs(z[i]);
      }
      ncon=0;
      (*nbad)=0;
      fct(z,px,f,rj1,rj2,n,m,t,h,ncon,nbad,ip);
      if((*nbad)==1)
          goto d510;
      ncon=1;
      ipnu=1;
      ipkp=0;
      ipm=0;
      for(i=1;i<=n;i++)
          ar[i+nzn]=z[i];
      for(i=1;i<=m;i++)
          ar[i+ndx1]=px[i];
d5:        ;
      for(i=1;i<=m;i++)
      {
        xp1[i]=px[i];
        px[i]=ar[i+ndx1];
      }
      for(i=1;i<=n;i++) z[i]=ar[i+nzn];
      if(ih==1) goto d80;
      for(i=1;i<=m;i++) px[i]=con0;
      if(n>m)
      {
        for(i=m+1;i<=n;i++)
        { 
          z[i]=con0;
          ar[i+nzn]=con0;
        }
      }
     goto d80;
d10:       ;
        ee=con0;
     for(i=1;i<=m;i++)
     {
       ra0=con1;
       ih1=0;
       if (fabs(px[i])>conmst)
       {
         ra1=fabs(xp1[i]/px[i]);
         ra2=fabs((xp1[i]-px[i])/px[i]);
         for(ii=1;ii<=10;ii++)
         {
           ra0=ra0*con2;
           if(fabs(ra1-ra0)<cont1)
             ih1=1;
         }
          if(ih1==0)
          {
            if(ra2>ee)
              ee=ra2;
          }
        }
     }
     //printf("ee=%15.8e ,h=%15.8e ,ip[1]=%d\n ",ee,h,ip[1]);
     //fprintf(f01,"ee=%15.8e ,h=%15.8e ,ip[1]=%d\n ",ee,h,ip[1]);
     h=h/con2;
     if(ee>conm3)
         goto d5;
     fp=fconp;
     dp=fdz;
     for(i=1;i<=m;i++)
     {
        ar[i+nmz]=fabs(z1[i]);
        z[i]=ar[i+nzn];
        ar[i+nzt]=z[i];
        ar[i+nzt1]=z[i];
        ar[i+nzt2]=z[i];
        ar[i+nzt3]=z[i];
        ar[i+nzt4]=z[i];
        ar[i+nzt5]=z[i];
    }
         hpred=h;
         h1=h;
         h2=h;
         h3=h;
         h4=h;
     h5=h;
         ih=0;
         ih1=0;
         ih2=0;
         ih3=0;
         tt=con0;
         ttn=con0;
     for(i=1;i<=n;i++)
     { 
        z1[i]=z[i];
        ar[i+nzn]=z[i];
     }
     for(i=1;i<=m;i++)
     {
        xp1[i]=px[i];
        ar[i+nxn]=px[i];
        ar[i+nxnm2]=px[i];
        ar[i+nxnm3]=px[i];
     }
     ncon=0;
     out(z,px,n,m,t,t0,tk,h,tkv,ncon,ip);
     ncon=1;
     ipkv=0;
d20:       ;
         ipk=0;
         ipnu=0;
     if(h<hmn)
         h=hmn;
     if(h>hmx)
         h=hmx;
     ipm=nm-1;
     if(nm==4)
         ipm=2;
d30:       ;
         t=tn;
         iprh=0;
         ht=conm14*tn;
         if(h<ht)
             iprh=1;
         if(iprh==0)
             goto d40;
         tt=ttn+h;
         if(tt<ht)
             goto d40;
         iprh=2;
d40:       if(iprh==0)
             t=tn+h;
     if(iprh==2)
         t=tn+tt;
     if((t+h/2e0)<(*tkv))
         goto d60;
     if(fabs(tn-(*tkv))<ht)
         goto d50;
     h=(*tkv)-tn;
     t=tn+h;
d50:     ipkv=1;
d60:       ;
     if((t+h/2e0)<tk)
         goto d80;
     if(fabs(tn-tk)<ht)
         goto d70;
     h=tk-tn;
     t=tn+h;
d70:       ipk=1;
d80:     prwar=0;
     (*tkv)=2e0*tk;
     fnm=con0;
     fdz=con0;
     kolf=0;
     kolil=0;
     ip[1]=0;
     for(i=1;i<=n;i++)
         ar[i+nmz1]=fabs(ar[i+nzn]);
     for(i=1;i<=m;i++)
     {
        ar[i+ndarx]=con0;
        ar[i+ndar1]=con0;
        ar[i+ndar]=con0;
     }
     if(ipm==0) goto d90;
     if(ipm==1) goto d100;
     if(ipm==2) goto d110;
d90:       ah=-con1/h;
     goto d390;
d100:      ah=-con2/h;
     goto d390;
d110:      ah=con1/h;
     goto d240;
d120:      ;
     fp=fconp;
     dp=fdz;
     ipkor=0;
     for(i=1;i<=m;i++)
     {
        lkt=0;
        lkt1=0;
        lkt2=0;
        if(ipm==2)
        {
          rxnm3=ar[i+nxnm3];
          rxnm2=ar[i+nxn];
          rxnm1=px[i];
          rxn=xp1[i];
        }
        else
        {rxnm3=ar[i+nxnm3];
          rxnm2=ar[i+nxnm2];
          rxnm1=ar[i+nxn];
          rxn=px[i];
        }
        r11=rxn-rxnm1;
        r22=rxnm1-rxnm2;
        r33=rxnm2-rxnm3;
        if(rxn<0e0)
            sn1=1;
        else
            sn1=0;
        if(rxnm1<0e0)
            sn2=1;
        else
            sn2=0;
        if(sn1!=sn2)
            lkt=1;
        ra1=fabs(rxn);
        ra2=fabs(rxnm1);
        if(ra1<ra2)
            ra1=ra2;
        ra2=0e0;
        if(ra1>conmst)
            ra2=fabs(r11/ra1);
        if(ra2<conm14)
            lkt=0;
        if(rxnm1<0e0)
            sn1=1;
        else
            sn1=0;
        if(rxnm2<0e0)
            sn2=1;
        else
            sn2=0;
        if(sn1!=sn2)
            lkt1=1;
        ra1=fabs(rxnm1);
        ra2=fabs(rxnm2);
        if(ra1<ra2)
            ra1=ra2;
        ra2=0e0;
        if(ra1>conmst)
            ra2=fabs(r22/ra1);
        if(ra2<conm14)
            lkt1=0;
        if(rxnm2<0e0)
            sn1=1;
        else
            sn1=0;
        if(rxnm3<0e0)
            sn2=1;
        else
            sn2=0;
        if(sn1!=sn2)
            lkt2=1;
        ra1=fabs(rxnm2);
        ra2=fabs(rxnm3);
        if(ra1<ra2)
            ra1=ra2;
        ra2=0e0;
        if(ra1>conmst)
            ra2=fabs(r33/ra1);
        if(ra2<conm14)
            lkt2=0;
        ip[i+nlkk]=lkt+lkt1+lkt2;
        if(ip[i+nlkk]==3)
            ipkor=1;
     }
     if(ipm==1)
         goto d170;
     if(ipkor==0)
         goto d150;
     ip[12]=ip[12]+1;
     ipkp=2;
     for(i=1;i<=m;i++)
     {
        ar[i+ndx1]=px[i];
        px[i]=ar[i+nxn];
     }
     for(i=1;i<=n;i++)
         z[i]=ar[i+nzn];
     ipm=0;
     ipsav=ip[1];
     goto d80;
d130:      ;
     ip[1]=ipsav;
     ipm=2;
     for(i=1;i<=m;i++)
     {
         if(ip[i+nlkk]!=3)
             goto d140;
         xp1[i]=px[i];
d140:      ; }
         ipkp=0;
d150:      r0=h;
     for(i=1;i<=n;i++)
     {  
        z[i]=z1[i];
        ar[i+nzn]=z1[i];
     }
     for(i=1;i<=m;i++)
     {
        ar[i+nxnm3]=px[i];
        ar[i+nxnm2]=px[i];
        if(ipkor==1)
        {
         ar[i+nxnm3]=ar[i+ndx1];
         ar[i+nxnm2]=ar[i+ndx1];
          if(ip[i+nlkk]==3)
          {
           ar[i+nxnm3]=xp1[i];
           ar[i+nxnm2]=xp1[i];
          }
        }
        px[i]=xp1[i];
        ar[i+nxn]=xp1[i];
        if(ar[i+nmz]<fabs(ar[i+nzn]))
            ar[i+nmz]=fabs(ar[i+nzn]);
     }
     ip[3]=ip[3]+1;
     ip[10]=ip[10]+1;
     out(z,px,n,m,t,t0,tk,h,tkv,ncon,ip);
         if(em4>epd16)
             ih=0;
         if(em4>epd16)
             ih1=0;
         if(em4>epd16)
             ih2=0;
     if(em4>epd16)
         ih3=0;
     if(ipkv!=0)
         goto d160;
     if(em4 > epd16)
         goto d160;
     if(fabs(h - hpred) < DOUBLE_EPS1 && em4 > epd32)
         ih=ih+1;
     if(fabs(h - hpred) < DOUBLE_EPS1 && ih < 3 && em4 > epd32)
         goto d160;
     if(em4 > epd32)
         ih = 0;
     if(ih == 0 && em4 > epd32)
         r0=h*con1t1;
     if(em4>epd32)
         goto d160;
     if(fabs(h - hpred) < DOUBLE_EPS1 && em4 > epd64)
         ih1=ih1+1;
     if(fabs(h - hpred) < DOUBLE_EPS1 && ih1 < 3 && em4 > epd64)
         goto d160;
     if(em4>epd64)
         ih1=0;
     if(ih1==0&&em4>epd64)
         r0=h*con1t2;
     if(em4>epd64)
         goto d160;
     if(fabs(h - hpred) < DOUBLE_EPS1 && em4 > epd128)
         ih2=ih2+1;
     if(fabs(h - hpred) < DOUBLE_EPS1 && ih2 < 3 && em4 > epd128)
         goto d160;
     if(em4>epd128)
         ih2=0;
     if(ih2==0&&em4>epd128)
         r0=h*con1t5;
     if(em4>epd128)
         goto d160;
     if(em4<conm7)
         ih3=3;
     if(fabs(h - hpred) < DOUBLE_EPS1)
         ih3=ih3+1;
     if(fabs(h - hpred) < DOUBLE_EPS1 && ih3 < 3)
         goto d160;
     ih3=0;
     r0=h*con2;
d160:    if(etr<epd128) ipm=1;
     goto d230;

d170:    ;
     if(ipkor==0) goto d200;
     ip[12]=ip[12]+1;
         ipkp=1;
     for(i=1;i<=m;i++)
     {
        ar[i+ndx1]=px[i];
        px[i]=ar[i+nxn];
     }
     for(i=1;i<=n;i++)
     {
        ar[i+ndz1]=z[i];
        z[i]=ar[i+nzn];
     }
     ipm=0;
     ipsav=ip[1];
     goto d80;
d180:      ;
     ip[1]=ipsav;
     ipm=1;
     for(i=1;i<=m;i++)
     { 
         if(ip[i+nlkk]!=3)
             goto d190;
         ar[i+ndx1]=px[i];
d190:      ;}
     for(i=1;i<=n;i++)
         z[i]=ar[i+ndz1];
     for(i=1;i<=m;i++)
         px[i]=ar[i+ndx1];
     ipkp=0;
d200:      r0=h;
     for(i=1;i<=n;i++)
     {
         z1[i]=z[i];
         ar[i+nzn]=z[i];
     }
     for(i=1;i<=m;i++)
     {
         xp1[i]=px[i];
         ar[i+nxnm3]=ar[i+nxnm2];
         ar[i+nxnm2]=ar[i+nxn];
         ar[i+nxn]=px[i];
         if(ar[i+nmz]<fabs(ar[i+nzn]))
             ar[i+nmz]=fabs(ar[i+nzn]);
     }
     ip[3]=ip[3]+1;
     ip[8]=ip[8]+1;
     out(z,px,n,m,t,t0,tk,h,tkv,ncon,ip);
         if(etr>epd8)
             ih=0;
         if(etr>epd8)
             ih1=0;
         if(etr>epd8)
             ih2=0;
         if(ipkv!=0)
             goto d210;
         if(etr > epd8)
             goto d210;
         if(fabs(h - hpred) < DOUBLE_EPS1 && etr > epd16)
             ih=ih+1;
         if(fabs(h - hpred) < DOUBLE_EPS1 && ih < 3 && etr > epd16)
             goto d210;
         if(etr>epd16)
             ih=0;
         if(ih == 0 && etr > epd16)
             r0=h*con1t1;
         if(etr > epd16)
             goto d210;
         if(fabs(h - hpred) < DOUBLE_EPS1 && etr > epd32)
             ih1=ih1+1;
         if(fabs(h - hpred) < DOUBLE_EPS1 && ih1 < 3 && etr > epd32)
             goto d210;
         if(etr>epd32)
             ih1=0;
         if(ih1==0&&etr>epd32)
             r0=h*con1t3;
         if(etr>epd32)
             goto d210;
         if(etr<conm7)
             ih2=3;
         if(fabs(h - hpred) < DOUBLE_EPS1)
             ih2=ih2+1;
         if(fabs(h - hpred) < DOUBLE_EPS1 && ih2 < 3)
             goto d210;
         ih2=0;
     r0=h*con2;
d210:    if(etr<epd8)
             goto d230;
         ipm=2;
     goto d230;
d220:      r0=h;
     for(i=1;i<=n;i++)
         ar[i+nzn]=z[i];
     for(i=1;i<=m;i++)
     {
         ar[i+nxn]=px[i];
         if(ar[i+nmz]<fabs(ar[i+nzn]))
             ar[i+nmz]=fabs(ar[i+nzn]);
     }
     ip[3]=ip[3]+1;
     out(z,px,n,m,t,t0,tk,h,tkv,ncon,ip);
     fp=fconp;
     dp=fdz;
     if(ipkv!=0)
         goto d230;
     if(ee>epd4)
         goto d230;
     r0=h*con1t2;
     if(ee>epd8)
         goto d230;
     r0=h*con1t5;
     if(ee>epd16)
         goto d230;
     r0=h*con2;
d230:      ;
     hpred=h;
     if(nm==1)
         ipm=0;
     if(nm==2)
         ipm=1;
     if(nm==3)
         ipm=2;
     h=r0;
     if(h>hmx)
         h=hmx;
     if(h<hmn)
         h=hmn;
     for(i=1;i<=m;i++)
     {
        ar[i+nzt5]=ar[i+nzt4];
        ar[i+nzt4]=ar[i+nzt3];
        ar[i+nzt3]=ar[i+nzt2];
        ar[i+nzt2]=ar[i+nzt1];
        ar[i+nzt1]=ar[i+nzt];
     }
     h5=h4;
     h4=h3;
     h3=h2;
     h2=h1;
     tn=t;
     if(iprh==2)
         tt=con0;
     ttn=tt;
     if(ipkv==1)
         ipkv=0;
     if(ipk==1)
         goto d590;
     goto d30;
d240:     ;
     for(i=1;i<=2*(n*n);i++)
         ar[i+na12]=con0;
     for(i=1;i<=m;i++)
     {
         r11=(a11*ar[i+ndar]+a12*ar[i+ndar1]);
         r22=(a21*ar[i+ndar]+a22*ar[i+ndar1]);
         ar[i+nbxp]=-(px[i]+ah*r11+ar[i+nxn]/con2);
         ar[i+nbxp1]=-(ah*r22+ar[i+ndarx]);
     }
     tv=tn;
     if(iprh==0)
         tv=tn+h/con2;
     if(iprh==2)
         tv=tn+tt/con2;
     for(i=1;i<=n;i++)
     {
         f[i]=conmd;
         if(fabs(z[i])>conmst)
             f[i]=conmd*fabs(z[i]);
     }
     (*nbad)=0;
     nsm4=1;
     fct(z,px,f,rj1,rj2,n,m,tv,h,ncon,nbad,ip);
     if((*nbad)!=0)
         goto d510;
d250:      ia=1;
     for(j=1;j<=m;j++)
     {
         for(i=1;i<=n;i++)
         {
             ar[ia+na11]=rj1[i*n+j];
             /*fprintf(f01,"ia=%d,ar[ia+na11]=%15.8e\n",ia,ar[ia+na11]); */
             ia=ia+1;
         }
     }
     if(iprp==1)
     {
      for(i=1;i<=n;i++) {
          ar[i+nzr1]=f[i];
          ar[i+nzr]=z[i];
      }
      for(i=n;i>=1;i--) {
         ra0=conmd;
         if(fabs(z[i])>conmst)
             ra0=conmd*fabs(z[i]);
         z[i]=z[i]+ra0;
         (*nbad)=0;
         ncon=3;
         fct(z,px,f,rj1,rj2,n,m,tv,h,ncon,nbad,ip);
         ncon=1;
         if((*nbad)==1)
             goto d510;
         for(j=1;j<=n;j++)
             rj2[j*n+i]=(f[j]-ar[j+nzr1])/ra0;
         z[i]=ar[i+nzr];
       }
      for(i=1;i<=n;i++)
          f[i]=ar[i+nzr1];
     }
     for(j=1;j<=n;j++) {
         for(i=1;i<=n;i++)
         {
             ar[ia+na11]=rj2[i*n+j];
             /*fprintf(f01,"ia=%d,ar[ia+na11]=%15.8e\n",ia,ar[ia+na11]);           */
             ia=ia+1;
         }
     }
     for(i=1;i<=n;i++)
         ar[i+nb]=-f[i];
     for(i=1;i<=n;i++)
     {
         f[i]=conmd;
         if(fabs(z1[i])>conmst)
             f[i]=conmd*fabs(z1[i]);
     }
     (*nbad)=0;
     nsm4=2;
     fct(z1,xp1,f,rj1,rj2,n,m,t,h,ncon,nbad,ip);
     if((*nbad)!=0)
         goto d510;
d260:     ia=1;
     for(j=1;j<=m;j++)
     {
         for(i=1;i<=n;i++)
         {
             ar[ia+na22]=rj1[i*n+j];
             /*fprintf(f01,"ia=%d,ar[ia+na22]=%15.8e\n",ia,ar[ia+na22]);           */
             ia=ia+1;
         }
     }
     if(iprp==1)
     {
        for(i=1;i<=n;i++) {
          ar[i+nzr1]=f[i];
          ar[i+nzr]=z1[i];
        }
        for(i=n;i>=1;i--) {
          ra0=conmd;
          if(fabs(z1[i])>conmst)
              ra0=conmd*fabs(z1[i]);
          z1[i]=z1[i]+ra0;
          (*nbad)=0;
          ncon=3;
          fct(z1,xp1,f,rj1,rj2,n,m,t,h,ncon,nbad,ip);
          ncon=1;
          if((*nbad)==1)
              goto d510;
          for(j=1;j<=n;j++)
              rj2[j*n+i]=(f[j]-ar[j+nzr1])/ra0;
          z1[i]=ar[i+nzr];
        }
        for(i=1;i<=n;i++)
          f[i]=ar[i+nzr1];
     }
     for(j=1;j<=n;j++) {
         for(i=1;i<=n;i++) {
             ar[ia+na22]=rj2[i*n+j];
             /*fprintf(f01,"ia=%d,ar[ia+na22]=%15.8e\n",ia,ar[ia+na22]);           */
             ia=ia+1;
         }
     }
     for(i=1;i<=n;i++)
         ar[i+nb1]=-f[i];
     if(ip[1]>1)
         goto d270;
     for(i=1;i<=2*n;i++)
         if(fabs(ar[i+nb])>fnm)
             fnm=fabs(ar[i+nb]);
     for(i=1;i<=2*m;i++)
         if(fabs(ar[i+nbxp])>fnm)
             fnm=fabs(ar[i+nbxp]);
d270:      fcon=con0;
     fconp=con0;
     for(i=1;i<=2*n;i++) {
        if(fabs(ar[i+nb])>fcon)
            fcon=fabs(ar[i+nb]);
        if(fabs(ar[i+nb])>fconp)
            fconp=fabs(ar[i+nb]);
     }
     for(i=1;i<=2*m;i++)
         if(fabs(ar[i+nbxp])>fcon)
             fcon=fabs(ar[i+nbxp]);
     if(ip[1]==0)
         goto d280;
     if(fnm<conmst)
         goto d380;
     radz=con1;
     for(i=1;i<=2*n;i++) {
        ra1=con1;
        ra2=con1;
        ra3=fabs(ar[i+ndz]);
        ra4=fabs(ar[i+ndzs]);
        if(ra3>conmst)
            ra1=ra4/ra3;
        if(ra4>conmst)
            ra2=ra3/ra4;
        if(ra2>ra1)
            ra1=ra2;
        if(radz<ra1)
            radz=ra1;
     }
     rafc=con0;
     if(fnm>conmst)
         rafc=fcon/fnm;
     if(rafc<conm7&&ip[1]==1)
         kolf=1;
     rafp=con1;
     if(fconp>conmst)
         rafp=fp/fconp;
     if(fp<conmst)
         rafp=con1;
     radzp=con1;
     if(fdz>conmst)
         radzp=dp/fdz;
d280:
/*
    fprintf(f01,"fcon= %15.8e fnm= %15.8e fdz=%15.8e h=%15.8e\n",fcon,fnm,fdz,h);

    fprintf(f01,"nb,nb1\n");
    for(i=1;i<=n;i++)fprintf(f01,"%15.8e ",ar[i+nb]);
             fprintf(f01,"\n");
    for(i=1;i<=n;i++)fprintf(f01,"%15.8e ",ar[i+nb1]);
             fprintf(f01,"\n");
      fprintf(f01,"nbxp,nbxp1\n");
     for(i=1;i<=m;i++)fprintf(f01,"%15.8e ",ar[i+nbxp]);
             fprintf(f01,"\n");
     for(i=1;i<=m;i++)fprintf(f01,"%15.8e ",ar[i+nbxp1]);
             fprintf(f01,"\n");
     fprintf(f01,"ndz,ndz1\n");
    for(i=1;i<=n;i++)fprintf(f01,"%15.8e ",ar[i+ndz]);
             fprintf(f01,"\n");
     for(i=1;i<=n;i++)fprintf(f01,"%15.8e ",ar[i+ndz1]);
             fprintf(f01,"\n");
     fprintf(f01,"ndx,ndx1\n");
    for(i=1;i<=m;i++)fprintf(f01,"%15.8e ",ar[i+ndx]);
             fprintf(f01,"\n");
     for(i=1;i<=m;i++)fprintf(f01,"%15.8e ",ar[i+ndx1]);
             fprintf(f01,"\n");
    fprintf(f01,"z,px,z1,xp1\n");
    for(i=1;i<=n;i++)fprintf(f01,"%15.8e ",z[i]);
             fprintf(f01,"\n");
    for(i=1;i<=m;i++)fprintf(f01,"%15.8e ",px[i]);
             fprintf(f01,"\n");
    for(i=1;i<=n;i++)fprintf(f01,"%15.8e ",z1[i]);
             fprintf(f01,"\n");
    for(i=1;i<=m;i++)fprintf(f01,"%15.8e ",xp1[i]);
             fprintf(f01,"\n");
*/
     if(ip[1]<2) goto d290;
     if(radz>con8) goto d290;
     if(fdz<conm7) goto d380;
     if(ip[1]==2) goto d290;
     if(radzp<conmst&&h>4e0*hmn) goto d540;
     if(radzp<0.1e0&&h>4e0*hmn&&kolf!=1) goto d540;
     kolil=kolil+1;
     if(kolil<2) goto d290;
     prwar=1;
     if((radzp>0.1e0||rafp>0.1e0)&&kolf==1)
         prwar=0;
     goto d380;
d290:     (*ier)=0;
     for(i=1;i<=2*n;i++) {
        ar[i+nfs]=fabs(ar[i+nb]);
        ar[i+ndzs]=fabs(ar[i+ndz]);
        ar[i+ndxs]=fabs(ar[i+ndx]);
     }
 dlur1(n,m,na11,nj,nip,na22,nj1,nip1,na21,na12,ar,ip,a11,a12,a21,a22,ah,ier);
     if((*ier)!=0) goto d580;
 dpoh(n,m,na11,nj,nb,nbxp,ndz,nzr,ndx,nxr,nip,na22,nj1,nb1,nbxp1,ndz1,nzr1,ndx1,nxr1,nip1,na21,na12,ar,ip,a11,a12,a21,a22,ah,ier);
         ip[1]=ip[1]+1;
     if((*ier)==8) goto d580;
     if(ip[1]>10) goto d520;
     for(i=1;i<=n;i++) {
            ra0=fabs(ar[i+ndz]);
            ra1=fabs(z[i]);
            if(ra1>conmst) ra0=ra0/ra1;
        if(ra0>conm14||ra1<=conmst) goto d300;
        ar[i+ndz]=con0;
d300:         if(ip[1]<3) goto d310;
        if(fabs(ar[i+ndzs] - con0) < DOUBLE_EPS1 )
            ar[i+ndz]=con0;
d310:         ra0=fabs(ar[i+ndz1]);
            ra1=fabs(z1[i]);
            if(ra1>conmst) ra0=ra0/ra1;
        if(ra0>conm14||ra1<=conmst) goto d320;
        ar[i+ndz1]=con0;
d320:         if(ip[1]<3) goto d330;
        if(fabs(ar[n+i+ndzs] - con0) < DOUBLE_EPS1)
            ar[i+ndz1]=con0;
d330:     ;}
     for(i=1;i<=m;i++) {
        ra2=fabs(px[i]);
        ra3=fabs(ar[i+ndx]);
        if(ra2>conmst) ra3=ra3/ra2;
        if(ra3>conm14||ra2<=conmst) goto d340;
        ar[i+ndx]=con0;
d340:         if(ip[1]<3) goto d350;
        if(fabs(ar[i+ndxs] - con0) < DOUBLE_EPS1)  ar[i+ndx]=con0;
d350:         ra2=fabs(xp1[i]);
            ra3=fabs(ar[i+ndx1]);
            if(ra2>conmst) ra3=ra3/ra2;
        if(ra3>conm14||ra2<=conmst) goto d360;
        ar[i+ndx1]=con0;
d360:         if(ip[1]<3) goto d370;
        if(fabs(ar[n+i+ndxs] - con0) < DOUBLE_EPS1)
            ar[i+ndx1]=con0;
d370:      ;   }
     for(i=1;i<=n;i++)
     {
         z[i]=z[i]+ar[i+ndz];
         z1[i]=z1[i]+ar[i+ndz1];
         if(ar[i+nmz1]<fabs(z[i]))
             ar[i+nmz1]=fabs(z[i]);
         if(ar[i+nmz1]<fabs(z1[i]))
             ar[i+nmz1]=fabs(z1[i]);
     }
     for(i=1;i<=m;i++)
     {
            px[i]=px[i]+ar[i+ndx];
        xp1[i]=xp1[i]+ar[i+ndx1];
            ar[i+ndarx]=ar[i+ndarx]+ar[i+ndx1];
            ar[i+ndar]=ar[i+ndar]+ar[i+ndz];
        ar[i+ndar1]=ar[i+ndar1]+ar[i+ndz1];
        }
         fdz=con0;
     for(i=1;i<=n;i++)
     {
         if(ar[i+nmz1]>conmst)
             ar[i+ndz1]=ar[i+ndz1]/ar[i+nmz1];
         if(ar[i+nmz1]>conmst)
             ar[i+ndz]=ar[i+ndz]/ar[i+nmz1];
         if(fabs(ar[i+ndz])<conm14)
             ar[i+ndz]=con0;
         if(fabs(ar[i+ndz1])<conm14)
             ar[i+ndz1]=con0;
         if(fabs(ar[i+ndz1])>fdz)
             fdz=fabs(ar[i+ndz1]);
         if(fabs(ar[i+ndz])>fdz)
             fdz=fabs(ar[i+ndz]);
     }
     goto d240;
d380:      ;
     ip[2]=ip[2]+ip[1];
     ip[9]=ip[9]+ip[1];
         h1=h;
     for(i=1;i<=m;i++)
         ar[i+nzt]=z1[i];
     goto d560;
d390:     ;
     if(ipm==1)
     {
       for(i=1;i<=m;i++)
           ar[i+nbxp]=-(px[i]+ah*ar[i+ndar]+ar[i+nxn]);
     }
     else
     {
       for(i=1;i<=m;i++)
           ar[i+nbxp]=-(px[i]+ah*ar[i+ndar]);
     }
     for(i=1;i<=n;i++)
     {
        f[i]=conmd;
        if(fabs(z[i])>conmst)
          f[i]=conmd*fabs(z[i]);
     }
     (*nbad)=0;
     fct(z,px,f,rj1,rj2,n,m,t,h,ncon,nbad,ip);
     if((*nbad)!=0)
         goto d510;
d400:      ia=1;
     for(j=1;j<=m;j++)
     {
         for(i=1;i<=n;i++)
         { 
           ar[ia+na11]=rj1[i*n+j];
//fprintf(f01,"rj1: ia=%d,ar[ia+na11]=%15.8e\n",ia,ar[ia+na11]);
           ia=ia+1;
         }
     }
     if(iprp==1)
     {
       for(i=1;i<=n;i++)
       {
         ar[i+nzr1]=f[i];
         ar[i+nzr]=z[i];
       }
       for(i=n;i>=1;i--)
       { 
         ra0=conmd;
         if(fabs(z[i])>conmst)
             ra0=conmd*fabs(z[i]);
         z[i]=z[i]+ra0;
         (*nbad)=0;
         ncon=3;
         fct(z,px,f,rj1,rj2,n,m,t,h,ncon,nbad,ip);
         ncon=1;
         if((*nbad)==1)
             goto d510;
         for(j=1;j<=n;j++)
             rj2[j*n+i]=(f[j]-ar[j+nzr1])/ra0;
         z[i]=ar[i+nzr];
       }
       for(i=1;i<+n;i++)
         f[i]=ar[i+nzr1];
     }
     for(j=1;j<=n;j++)
     {
       for(i=1;i<=n;i++)
       {
         ar[ia+na11]=rj2[i*n+j];
//fprintf(f01,"rj2: ia=%d,ar[ia+na11]=%15.8e\n",ia,ar[ia+na11]);
         ia=ia+1;
       }
     }
     for(i=1;i<=n;i++)
         ar[i+nb]=-f[i];
     if(ip[1]>1)
         goto d410;
     for(i=1;i<=n;i++)
        if(fabs(ar[i+nb])>fnm)
            fnm=fabs(ar[i+nb]);
     for(i=1;i<=m;i++)
        if(fabs(ar[i+nbxp])>fnm)
            fnm=fabs(ar[i+nbxp]);
d410:      fcon=con0;
     fconp=con0;
     for(i=1;i<=n;i++)
     {
        if(fabs(ar[i+nb])>fcon)
            fcon=fabs(ar[i+nb]);
        if(fabs(ar[i+nb])>fconp)
            fconp=fabs(ar[i+nb]);
     }
     for(i=1;i<=m;i++)
       if(fabs(ar[i+nbxp])>fcon)
         fcon=fabs(ar[i+nbxp]);
     if(fnm<conmst)
         goto d480;
     if(ip[1]==0)
         goto d420;
     radz=con1;
     for(i=1;i<=n;i++)
     {
        ra1=con1;
        ra2=con1;
        ra3=fabs(ar[i+ndz]);
        ra4=fabs(ar[i+ndzs]);
        if(ra3>conmst)
            ra1=ra4/ra3;
        if(ra4>conmst)
            ra2=ra3/ra4;
        if(ra2>ra1)
            ra1=ra2;
        if(radz<ra1)
            radz=ra1;
     }
     rafc=con0;
     if(fnm>conmst)
         rafc=fcon/fnm;
     if(rafc<conm7&&ip[1]==1)
         kolf=1;
     rafp=con1;
     if(fconp>conmst)
         rafp=fp/fconp;
     if(fp<conmst)
         rafp=con1;
     radzp=con1;
     if(fdz>conmst)
         radzp=dp/fdz;
d420:      ;
/*
    fprintf(f01,"ip[1]= %d fnm= %15.8e  fcon= %15.8e fdz= %15.8e h= %15.8e \n ",ip[1],fnm,fcon,fdz,h);

    fprintf(f01,"z,px\n");
    for(i=1;i<=n;i++)fprintf(f01,"%15.8e ",z[i]);
             fprintf(f01,"\n");
    for(i=1;i<=m;i++)fprintf(f01,"%15.8e ",px[i]);
             fprintf(f01,"\n");
    fprintf(f01,"nb,nbxp\n");
    for(i=1;i<=n;i++)fprintf(f01,"%15.8e ",ar[i+nb]);
             fprintf(f01,"\n");
    for(i=1;i<=m;i++)fprintf(f01,"%15.8e ",ar[i+nbxp]);
             fprintf(f01,"\n");

     fprintf(f01,"ndz,ndzs\n");
    for(i=1;i<=n;i++)fprintf(f01,"%15.8e ",ar[i+ndz]);
             fprintf(f01,"\n");
    for(i=1;i<=n;i++)fprintf(f01,"%15.8e ",ar[i+ndzs]);
             fprintf(f01,"\n");
      fprintf(f01,"ndx,ndxs,nfs\n");
    for(i=1;i<=m;i++)fprintf(f01,"%15.8e ",ar[i+ndx]);
             fprintf(f01,"\n");
    for(i=1;i<=m;i++)fprintf(f01,"%15.8e ",ar[i+ndxs]);
             fprintf(f01,"\n");
    for(i=1;i<=n;i++)fprintf(f01,"%15.8e ",ar[i+nfs]);
             fprintf(f01,"\n");
*/
     if(ip[1]<2) goto d430;
     if(ipkor==1&&ip[1]==10) goto d480;
     if(radz>con8) goto d430;
     if(fdz<conm7) goto d480;
     if(ip[1]==2) goto d430;
/*
fprintf(f01,"ipm,ip(1)   %d  %d \n",ipm,ip[1]);
fprintf(f01,"kolf,rafp   %15.8e  %15.8e \n",kolf,rafp);
fprintf(f01,"radz,radzp  %15.8e  %15.8e \n",radz,radzp);
*/
     if(radzp<conmst&&h>4e0*hmn) goto d540;
     if(radzp<0.1e0&&h>4e0*hmn&&kolf!=1) goto d540;
     kolil=kolil+1;
     if(kolil<2) goto d430;
     prwar=1;
     if((radzp>0.1e0||rafp>0.1e0)&&kolf==1) prwar=0;
     goto d480;
d430:     (*ier)=0;
     for(i=1;i<=n;i++)
     {
        ar[i+nfs]=fabs(ar[i+nb]);
        ar[i+ndzs]=fabs(ar[i+ndz]);
        ar[i+ndxs]=fabs(ar[i+ndx]);
     }
     dlur(n,m,na11,nj,nb,nbxp,ndz,nzr,ndx,nxr,nip,ar,ip,ah,ier);
     ip[1]=ip[1]+1;
     if((*ier)!=0) goto d580;
     if(ip[1]>10) goto d520;
     for(i=1;i<=n;i++)
     {
            ra0=fabs(ar[i+ndz]);
            ra1=fabs(z[i]);
            if(ra1>conmst) ra0=ra0/ra1;
        if(ra0>conm14||ra1<=conmst) goto d440;
        ar[i+ndz]=con0;
d440:         if(ip[1]<3) goto d450;
        if(fabs(ar[i+ndzs] - con0) < DOUBLE_EPS1)
            ar[i+ndz]=con0;
d450:      ; }
     for(i=1;i<=m;i++)
     {
            ra2=fabs(px[i]);
        ra3=fabs(ar[i+ndx]);
            if(ra2>conmst) ra3=ra3/ra2;
        if(ra3>conm14||ra2<=conmst) goto d460;
        ar[i+ndx]=con0;
d460:         if(ip[1]<3) goto d470;
        if(fabs(ar[i+ndxs] - con0) < DOUBLE_EPS1)
            ar[i+ndx]=con0;
d470:      ; }
     for(i=1;i<=n;i++)
     {
        z[i]=z[i]+ar[i+ndz];
        if(ar[i+nmz1]<fabs(z[i]))
            ar[i+nmz1]=fabs(z[i]);
     }
     for(i=1;i<=m;i++)
     {
        ar[i+ndar]=ar[i+ndar]+ar[i+ndz];
        px[i]=px[i]+ar[i+ndx];
     }
/*
    fprintf(f01,"nmz1,ndz,ndx,ndar\n");
     for(i=1;i<=n;i++)fprintf(f01,"%15.8e ",ar[i+nmz1]);
             fprintf(f01,"\n");
     for(i=1;i<=n;i++)fprintf(f01,"%15.8e ",ar[i+ndz]);
             fprintf(f01,"\n");
     for(i=1;i<=m;i++)fprintf(f01,"%15.8e ",ar[i+ndx]);
             fprintf(f01,"\n");
     for(i=1;i<=m;i++)fprintf(f01,"%15.8e ",ar[i+ndar]);
             fprintf(f01,"\n");
*/
         fdz=con0;
     for(i=1;i<=n;i++)
     {
        if(ar[i+nmz1]>conmst)
            ar[i+ndz]=ar[i+ndz]/ar[i+nmz1];
        if(fabs(ar[i+ndz])<conm14)
            ar[i+ndz]=con0;
        if(fabs(ar[i+ndz])>fdz)
            fdz=fabs(ar[i+ndz]);
     }
     goto d390;
d480:      ;
     ip[2]=ip[2]+ip[1];
     if(ipm==1) ip[7]=ip[7]+ip[1];
     if(ipkp==1) goto d180;
     if(ipkp==2) goto d130;
     if(ipnu==1) goto d10;
         h1=h;
     for(i=1;i<=m;i++) ar[i+nzt]=z[i];
     goto d560;
d490:      ip[5]=ip[5]+1;
     if(h>4e0*hmn) goto d570;
     if(ipm==0) goto d220;
     goto d120;
d500:      ip[13]=ip[13]+1;
     goto d570;
d510:      ip[14]=ip[14]+1;
     goto d550;
d520:      ip[15]=ip[15]+1;
     goto d550;
d540:      ip[16]=ip[16]+1;
d550:      ip[6]=ip[6]+1;
     if(ipm==2)
     {
       if((*nbad)==2&&h<=2e0*hmn&&nsm4==1)
           goto d250;
       if((*nbad)==2&&h<=2e0*hmn&&nsm4==2)
           goto d260;
     }
     else
     {
       if((*nbad)==2&&h<=2e0*hmn)
         goto d400;
     }
     if(h<=hmn)
         goto d580;
     if(ipkp==1)
         ipm=1;
     if(ipkp==2)
         ipm=2;
     goto d570;
d560:    ;
     ee=con0;
         etr=con0;
         em4=con0;
            ra0=h1;
            ra11=ra0/h5;
            ra12=ra0/h4;
            ra13=ra0/h3;
            ra14=ra0/h2;
            ra15=ra0/h1;
            ra21=ra0/(h5+h4);
            ra22=ra0/(h4+h3);
            ra23=ra0/(h3+h2);
            ra24=ra0/(h2+h1);
            ra31=ra0/(h5+h4+h3);
            ra32=ra0/(h4+h3+h2);
            ra33=ra0/(h3+h2+h1);
            ra41=ra0/(h5+h4+h3+h2);
            ra42=ra0/(h4+h3+h2+h1);
            ra51=ra0/(h5+h4+h3+h2+h1);
     for(i=1;i<=m;i++)
     {
            if(ar[i+nmz]>ar[i+nmz1])
                ar[i+nmz1]=ar[i+nmz];
            r11=(ar[i+nzt4]-ar[i+nzt5])*ra11;
            r12=(ar[i+nzt3]-ar[i+nzt4])*ra12;
            r13=(ar[i+nzt2]-ar[i+nzt3])*ra13;
            r14=(ar[i+nzt1]-ar[i+nzt2])*ra14;
            r15=(ar[i+nzt]-ar[i+nzt1])*ra15;
            r21=(r12-r11)*ra21;
            r22=(r13-r12)*ra22;
            r23=(r14-r13)*ra23;
            r24=(r15-r14)*ra24;
            r31=(r22-r21)*ra31;
            r32=(r23-r22)*ra32;
            r33=(r24-r23)*ra33;
            r41=(r32-r31)*ra41;
            r42=(r33-r32)*ra42;
            r51=(r42-r41)*ra51;
        ve=fabs(r24);
        vt=fabs(r33);
        vm=fabs(r51);
        if(ar[i+nmz1]>conmst)
        {
          ve=fabs(ve)/ar[i+nmz1];
          vt=fabs(vt)/ar[i+nmz1];
          vm=fabs(vm)/ar[i+nmz1];
        }
        if(ve>ee)
            ee=ve;
        if(vt>etr)
            etr=vt;
        if(vm>em4)
            em4=vm;
     }
     ee=ee*con2;
     ar[1]=ee;
     etr=etr*con6;
     ar[2]=etr;
         em4=em4*con64;
     ar[3]=em4;
     if(prwar==1&&eps>100e0)
         goto d565;
     if(prwar==1&&ar[1]>conm7)
         goto d500;
d565:     ;
     if(prwar==1)
         ip[11]=ip[11]+1;
     if(prwar==1)
         printf(" warning! fdz>0.01: t=%15.8e ,h=%15.8e ,eps=%15.8e  \n",t,h,ar[1]);
     if(ipm==0)
     {
       if(ee>epsp)
           goto d490;
       goto d220;
     }
     if(ipm==1)
     {
       if(etr>epsp)
           goto d490;
       goto d120;
     }
     if(ipm==2)
     {
       if(em4>epsp)
           goto d490;
       goto d120;
     }
d570:      ;
     h=h/con2;
     for(i=1;i<=n;i++)
     {
        z[i]=ar[i+nzn];
        z1[i]=ar[i+nzn];
     }
     for(i=1;i<=m;i++)
     {
        px[i]=ar[i+nxn];
        xp1[i]=ar[i+nxn];
     }
     hv1=h2/con2;
     hv2=h3/con2;
     for(i=1;i<=m;i++)
     {
            ra0=(h5+h4+h3+hv1);
            ra11=ra0/h5;
            ra12=ra0/h4;
            ra13=ra0/h3;
            ra14=ra0/h2;
            ra0=(h4+h3+hv1);
            ra21=ra0/(h5+h4);
            ra22=ra0/(h4+h3);
            ra23=ra0/(h3+h2);
            ra0=(h3+hv1);
            ra31=ra0/(h5+h4+h3);
            ra32=ra0/(h4+h3+h2);
            ra0=(hv1);
            ra41=ra0/(h5+h4+h3+h2);
        ra1=(ar[i+nzt4]-ar[i+nzt5]);
            ra2=(ar[i+nzt3]-ar[i+nzt4]);
            ra3=(ar[i+nzt2]-ar[i+nzt3]);
            ra4=(ar[i+nzt1]-ar[i+nzt2]);
            r11=ra1*ra11;
            r12=ra2*ra12;
            r13=ra3*ra13;
            r14=ra4*ra14;
            r21=(r12-r11)*ra21;
            r22=(r13-r12)*ra22;
            r23=(r14-r13)*ra23;
            r31=(r22-r21)*ra31;
            r32=(r23-r22)*ra32;
            r41=(r32-r31)*ra41;
        zv1=ar[i+nzt5]+r11+r21+r31+r41;
            ra0=(h5+h4+hv2);
            ra11=ra0/h5;
            ra12=ra0/h4;
            ra13=ra0/h3;
            ra14=ra0/h2;
            ra0=(h4+hv2);
            ra21=ra0/(h5+h4);
            ra22=ra0/(h4+h3);
            ra23=ra0/(h3+h2);
            ra0=(hv2);
            ra31=ra0/(h5+h4+h3);
            ra32=ra0/(h4+h3+h2);
            ra0=(-hv2);
            ra41=ra0/(h5+h4+h3+h2);
            r11=ra1*ra11;
            r12=ra2*ra12;
            r13=ra3*ra13;
            r14=ra4*ra14;
            r21=(r12-r11)*ra21;
            r22=(r13-r12)*ra22;
            r23=(r14-r13)*ra23;
            r31=(r22-r21)*ra31;
            r32=(r23-r22)*ra32;
            r41=(r32-r31)*ra41;
        zv2=ar[i+nzt5]+r11+r21+r31+r41;
            ar[i+nzt5]=ar[i+nzt3];
            ar[i+nzt3]=ar[i+nzt2];
        ar[i+nzt2]=zv1;
        ar[i+nzt4]=zv2;
     }
         h5=hv2;
         h4=h5;
         h3=hv1;
     h2=h3;
     ip[4]=ip[4]+1;
     ip[2]=ip[2]+ip[1];
     if(ipm==2)
         ip[9]=ip[9]+ip[1];
     if(ipm==1)
         ip[7]=ip[7]+ip[1];
     ipk=0;
     ipkv=0;
     ipkp=0;
     goto d30;
d580:      if((*ier)==8)
         goto d540;
d590:      ;
     ipk=0;
     ipkv=1;
     t0=t;
     ncon=1;
     if((*ier)==0)
         return;
     ncon=-1;
     out(z,px,n,m,t,t0,tk,h,tkv,ncon,ip);
         return;
}

