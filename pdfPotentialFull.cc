#include <iostream>
#include <fstream>
#include <math.h>
#include <cstdlib>   // for rand() on archer.
#include <iomanip>   // for setw() in cout, 

// #include "zzhist.h"   // my own histogram package
// #include <gsl/gsl_math.h>
// #include <gsl/gsl_sf_gamma.h>

using namespace std;


// template <size_t size_x, size_t size_y>
void calculateVoltageMapSimple(int nmax, double (&V)[100][100]) {

   cout<<"  calculateVoltageMapSimple   nmax="<<nmax<<endl;
   int niter=1000;
   // set boundary condition
   for(int x=0; x<nmax; x++) {
     for(int y=0; y<nmax; y++) {
        V[x][y]=0.0;
        if(x==0) V[x][y]=100.0;   //  100 volots at x=0. (boundary condition)
     }
   }

   for(int iter=0; iter<niter; iter++) {
      //   loop over grid points except for boundaries...
      //   x, y are integer index of grid point.
      //   To keep the voltage=0 at the boudary, x=0, x=nmax, y=0, y=nmax are excluded.
      for(int x=1; x<(nmax-1); x++) {
          for(int y=1; y<(nmax-1); y++) {
             V[x][y]=0.25*(V[x+1][y] + V[x-1][y] + V[x][y-1] + V[x][y+1]);
          }  // end of y loop
      }  // end of x loop 
   }  // end of iter loop

   cout<<"writing vmapSimple.txt..."<<endl;
   ofstream outfile;
   outfile.open("vmapSimple.txt");

   for(int x=0; x<nmax; x=x+2) {
   for(int y=0; y<nmax; y=y+2) {
     outfile<<"   "<<x<<"   "<<y<<"   "<<V[x][y]<<endl;
   }
   }
   outfile.close();

   // insert two empty lines before going to new x line.
   // to disconnect a line from one end of y to another.
   cout<<"writing vmapSimple2.txt..."<<endl;
   ofstream outfile2;
   outfile2.open("vmapSimple2.txt");

   for(int x=0; x<nmax; x=x+2) {
   for(int y=0; y<nmax; y=y+2) {
     outfile2<<"   "<<x<<"   "<<y<<"   "<<V[x][y]<<endl;
   }
      outfile2<<"   "<<endl;
      outfile2<<"   "<<endl;
   }
   outfile2.close();



   return;
}


// template <size_t size_x, size_t size_y>
void calculateVoltageMapLineCap(int nmax, double (&V)[100][100]) {

   cout<<"  calculateVoltageMapLineCap   nmax="<<nmax<<endl;
   int niter=1000;
   // set boundary condition
   for(int x=0; x<nmax; x++) {
     for(int y=0; y<nmax; y++) {
        V[x][y]=0.0;
        if(y==30 && x>20 && x<80) V[x][y]=100.0;   // 
        if(y==70 && x>20 && x<80) V[x][y]=-100.0;  // `
     }
   }

   for(int iter=0; iter<niter; iter++) {
      //   loop over grid points except for boundaries...
      //   x, y are integer index of grid point.
      for(int x=1; x<(nmax-1); x++) {
          for(int y=1; y<(nmax-1); y++) {
             if(y==30 && x>20 && x<80) continue; // skip at capacitor line
             if(y==70 && x>20 && x<80) continue; // skip at capacitor line
             V[x][y]=0.25*(V[x+1][y] + V[x-1][y] + V[x][y-1] + V[x][y+1]);
          }  // end of y loop
      }  // end of x loop 
   }  // end of iter loop

   cout<<"writing vmapLineCap.txt..."<<endl;

   ofstream outfile;
   outfile.open("vmapLineCap.txt");

   for(int x=0; x<nmax; x=x+2) {
   for(int y=0; y<nmax; y=y+2) {
     outfile<<"   "<<x<<"   "<<y<<"   "<<V[x][y]<<endl;
   }
   }
   outfile.close();

   return;
}

// template <size_t size_x, size_t size_y>
void calculateVoltageMapBoxCap(int nmax, double (&V)[100][100]) {

   cout<<"  calculateVoltageMapBoxCap   nmax="<<nmax<<endl;
   int niter=1000;
   // set boundary condition
   for(int x=0; x<nmax; x++) {
     for(int y=0; y<nmax; y++) {
        V[x][y]=0.0;
        if((y>25 && y<35) && (x>20&&x<80)) V[x][y]=+100.0;   //  100 volots at x=0.`
        if((y<75 && y>65) && (x>20&&x<80)) V[x][y]=-100.0;   //  100 volots at x=0.`
     }
   }

   for(int iter=0; iter<niter; iter++) {
      //   loop over grid points except for boundaries...
      //   x, y are integer index of grid point.
      for(int x=1; x<(nmax-1); x++) {
          for(int y=1; y<(nmax-1); y++) {
             if((y>25 && y<35) && (x>20 && x<80)) continue;
             if((y<75 && y>65) && (x>20 && x<80)) continue;
             V[x][y]=0.25*(V[x+1][y] + V[x-1][y] + V[x][y-1] + V[x][y+1]);
          }  // end of y loop
      }  // end of x loop 
   }  // end of iter loop
 
   cout<<"writing vmapBoxCap.txt..."<<endl;

   ofstream outfile;
   outfile.open("vmapBoxCap.txt");

   for(int x=0; x<nmax; x=x+2) {
   for(int y=0; y<nmax; y=y+2) {
     outfile<<"   "<<x<<"   "<<y<<"   "<<V[x][y]<<endl;
   }
   }
   outfile.close();

   return;
}

//template <size_t size_x, size_t size_y>
void calculateEfieldMap(int nmax, double (&V)[100][100],
      double (&EX)[100][100],double (&EY)[100][100]){

   cout<<"calculate E-field map...   nmax="<<nmax<<endl;

   int nn=0;
   for(int x=1; x<(nmax-1); x++) {
   for(int y=1; y<(nmax-1); y++) {
   //   if((nn%1000)==0) cout<<"  nn  "<<nn<<"  x "<<x<<"   y "<<y<<endl;
     EX[x][y]=(V[x+1][y]-V[x-1][y])/2.0;
     EY[x][y]=(V[x][y+1]-V[x][y-1])/2.0;
   }
   }

   cout<<"writing efieldmap.txt..."<<endl;

   ofstream outfile;
   outfile.open("efieldmap.txt");

   for(int x=1; x<(nmax-1); x=x+5) {
   for(int y=1; y<(nmax-1); y=y+5) {
     outfile<<"   "<<x<<"   "<<y<<"   "<<EX[x][y]<<"   "<<EY[x][y]<<endl;
   }
   }
   outfile.close();

   return;
}

// template <size_t size_x, size_t size_y>
void calculateChargeMap(int nmax, 
         double (&EX)[100][100], double (&EY)[100][100], 
         double (&Q)[100][100]){
   cout<<"calculate charge map..."<<endl;

   // double Q[nmax][nmax];
   for(int x=1; x<(nmax-1); x++) {
   for(int y=1; y<(nmax-1); y++) {
     double qx=(EX[x+1][y]-EX[x-1][y])/2.0;
     double qy=(EY[x][y+1]-EY[x][y-1])/2.0;
     Q[x][y]=qx+qy;
   }
   }

   cout<<"writing chargemap.txt..."<<endl;
   ofstream outfile;
   outfile.open("chargemap.txt");

   // for(int x=1; x<(nmax-1); x=x+1) {
   for(int x=1; x<98; x=x+1) {
   for(int y=1; y<(nmax-1); y=y+1) {
     outfile<<"   "<<x<<"   "<<y<<"   "<<Q[x][y]<<endl;
   }
   }
   outfile.close();

   return ;
}

////////////////////////////////////////////////////////////////////////
//     main porgram
// -------------------
int main()
{

   int nGrid=100;



   double V[100][100];
   calculateVoltageMapSimple(nGrid,V);



   double VLINE[100][100];
   calculateVoltageMapLineCap(nGrid,VLINE);

   

   double VBOX[100][100];
   calculateVoltageMapBoxCap(nGrid,VBOX);

   double EX[100][100];
   double EY[100][100];
   calculateEfieldMap(nGrid,VBOX,EX,EY);

   double Q[100][100];
   calculateChargeMap(nGrid,EX,EY,Q);

   return 0;
}

