#include <iostream>
#include <fstream>
#include <math.h>
#include <cstdlib>   // for rand() on archer.
#include <iomanip>   // for setw() in cout, 

#include "zzhist.h"   // my own histogram package
#include "zzrand.h"   // gaussian random number generator

using namespace std;

// ==========================================================================
double mcintegral2d(int ntry,double radius){
   // area of a disk...
   double total=0.;
   double accepted=0.;
   double r2=radius*2.0;
   for (int i=0; i<ntry; i++) {
      double x=r2*zzrandU()-radius;  // x in [-radius,radius]
      double y=r2*zzrandU()-radius;  // y in [-radius,radius]
      double r=sqrt(x*x+y*y);
      total++;
      if(r<radius) accepted++;
   }
   double area=r2*r2*accepted/total;
   return area;
}

// ==========================================================================
double mcintegral3d(int ntry,double radius){
   //  volume of sphere...   to be coded...
   double total=0.;
   double accepted=0.;
   double r2=radius*2.0;
   for (int i=0; i<ntry; i++) {
      double x=r2*zzrandU()-radius;  // x in [-radius,radius]
      double y=r2*zzrandU()-radius;  // y in [-radius,radius]
      double z=r2*zzrandU()-radius;  // y in [-radius,radius]
      double r=sqrt(x*x+y*y+z*z);
      total++;
      if(r<radius) accepted++;
   }
   double volume=r2*r2*r2*accepted/total;

   return volume;
}

// ==========================================================================
void testMCintegralSimple() {

   double pi=acos(-1.0);   // 3.14159
   cout<<"  pi="<<setprecision(10)<<pi<<endl;;
   double radius=1.0;   
   double trueArea=pi*radius*radius;
   double trueVolume=(4.0/3.0)*pi*(radius*radius*radius);

   int ntry=100;
   double area=mcintegral2d(ntry,radius);
   double deltaA=area-trueArea;
   cout<<" MC integral  ntry="<<ntry<<"   area="<<area<<"   dleta="<<deltaA<<endl;

   ntry=10000;
   area=mcintegral2d(ntry,radius);
   deltaA=area-trueArea;
   cout<<" MC integral  ntry="<<ntry<<"   area="<<area<<"   dleta="<<deltaA<<endl;

   ntry=1000000;
   area=mcintegral2d(ntry,radius);
   deltaA=area-trueArea;
   cout<<" MC integral  ntry="<<ntry<<"   area="<<area<<"   dleta="<<deltaA<<endl;

   ntry=100;
   double volume=mcintegral3d(ntry,radius);
   double deltaV=volume-trueVolume;   
   cout<<" MC integral  ntry="<<ntry<<"   volume="<<volume<<"   dletaV="<<deltaV<<endl;

   ntry=10000;
   volume=mcintegral3d(ntry,radius);
   deltaV=volume-trueVolume;
   cout<<" MC integral  ntry="<<ntry<<"   volume="<<volume<<"   dletaV="<<deltaV<<endl;

   ntry=1000000;
   volume=mcintegral3d(ntry,radius);
   deltaV=volume-trueVolume;
   cout<<" MC integral  ntry="<<ntry<<"   volume="<<volume<<"   dletaV="<<deltaV<<endl;

  return;
}

// ==========================================================================
void testMCintegralMany() {

   string outname="mcintegral1k.txt";
   ofstream outfile(outname);

   double pi=acos(-1.0);   // 3.14159
   cout<<"  pi="<<setprecision(10)<<pi<<endl;;
   double radius=1.0;
   double trueArea=pi*radius*radius;
   double trueVolume=(4.0/3.0)*pi*(radius*radius*radius);

   int ntry=10;
   int counter=-1;
   // do MC integrals with five different number of tries.
   // For each, rpeat the integral ten times to see the variation of values.
   for (int i=0; i<5; i++) {
      ntry=ntry*10;  // produce ntry=100, 1000, 10000, 100000, 1000000 
      for(int j=0; j<100; j++) {
          counter++;
          double area=mcintegral2d(ntry,radius);
          double deltaA=(area-trueArea)/trueArea;

          double volume=mcintegral3d(ntry,radius);
          double deltaV=(volume-trueVolume)/trueVolume;;

          cout<<"  "<<counter<<"  ntry "<<ntry<<"  deltaA "<<deltaA<<"  deltaV "<<deltaV<<endl;

          outfile<<"  "<<counter<<"  "<<ntry<<"  "<<deltaA<<"  "<<deltaV<<endl;;

      }  // end of j-loop.
   }  // end of i-loop..

   double r2=radius*2.0;
   double efficiency2D=trueArea/(r2*r2);
   double efficiency3D=trueVolume/(r2*r2*r2);
   cout<<"   estimated efficiencies  2D "<<efficiency2D<<"   3D "<<efficiency3D<<endl;

   return ;
}
// ==========================================================================
int main() {

   int seed=98720;
   srand(seed);      // define a seed for random number generation...
   cout<<"  "<<endl;
   cout<<"Random number seed is set to "<<seed<<" in main program"<<endl;

   // monte carlo integration...
   testMCintegralSimple();

   testMCintegralMany();

   return 0;
}
