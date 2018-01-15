//
//  c++ 
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <cstdlib>   // for rand() on archer.
#include <iomanip>   // for setw() in cout, 
#include <vector>

#include "zzhist.h"   // my own histogram package
#include "zzrand.h"   // gaussian random number generator

using namespace std;

//====================================================================
struct Point{
    double x;      // 
    double ytrue;  // truth value- we know this in Monte Carlo simulation.
    double ymeas;  // simulated measured value
    double yerror; // estimated error on y-value
};

//====================================================================
struct Data{
   int experimentNumber;
   vector<Point>  xyvector;
};

//====================================================================
struct FitResult{
   double chi2;
   double a;
   double b;
};

//====================================================================
Data readData(int expNo) {

  Data d;  // define return variable.

  // open input file...
  string fname="mydata/experiment_"+to_string(expNo)+".txt";
  ifstream infile(fname);

     if(infile.is_open()) {
        //   cout<<"reading data from input file "<<fname<<endl;
     }
     else {
         cout<<"error:  input file "<<fname<<" is not open."<<endl;
         return d;
     }
   //

   string line;
   if(infile.is_open()) {
      while (getline(infile,line)) {
          // cout<<"line="<<line<<endl;
          if(line.size()==0) {continue;}  // skip an empty line
          if(line.compare(0,1,"#")==0) {continue;}  // skip a comment line
          double x,ytrue,ymeas,yerror;
          std::istringstream iss(line);
          iss>>x>>ytrue>>ymeas>>yerror;
          Point p;
          p.x=x;  p.ytrue=ytrue; p.ymeas=ymeas;  p.yerror=yerror;
          d.xyvector.push_back(p);
      }  // end of while.
   }  // end of if infile open.

   if((expNo%100)==0) {
       cout<<"   "<<d.xyvector.size()<<" xy points read from "<<fname<<endl;
   }
   return d;  
}

//====================================================================
double getchi2(double a, double b, Data data){

   double chi2=0.0;
   int npoints=data.xyvector.size();
   for (int i=0; i<npoints; i++) {
      double x=data.xyvector[i].x;
      double y=data.xyvector[i].ymeas;
      double yerr=data.xyvector[i].yerror;
      double dy=y-(a+b*x);
      chi2=chi2+dy*dy/(yerr*yerr);
   }

   return chi2;
}

//====================================================================
FitResult  myfit1D(Data data){

   // find minimum chi2...  (a=fixed, b=varies)
   double a=2.0;

   double chi2min=10000.;
   double amin=0.0;
   double bmin=0.0;
   double db=0.001;
   for(double b=0.2; b<0.4; b=b+db) {
       double chi2=getchi2(a,b,data);
       if(chi2<chi2min) {chi2min=chi2; amin=a; bmin=b;}
   }

  FitResult f;
  f.chi2=chi2min;
  f.a=amin;
  f.b=bmin;  

  return f;
}

//====================================================================
FitResult myfit2D(Data data){

   // find minimum chi2...  (a=varies, b=varies)
   double chi2min=10000.;
   double amin=0.0;
   double bmin=0.0;
   double da=0.01;
   double db=0.001;
   for(double a=1.5; a<2.5; a=a+da) {
   for(double b=0.2; b<0.4; b=b+db) {
       double chi2=getchi2(a,b,data);
       if(chi2<chi2min) {chi2min=chi2; amin=a; bmin=b;}
   }
   }

   FitResult f;
   f.chi2=chi2min;
   f.a=amin;
   f.b=bmin;

  return f;
}

//====================================================================
int main() {

   // book histograms.
   zzh1 h1a("hist1chi2","1D chis2",30,0.0,30.0);
   zzh1 h1b("hist2chi2","2D chis2",30,0.0,30.0);

   // do fit to multiple  experimental data...
   int nExperiments=1000;
   for(int i=0; i<nExperiments; i++) {
      int expNumber=i;
      Data data=readData(expNumber);

      FitResult r1=myfit1D(data);
      FitResult r2=myfit2D(data);

//      cout<<" 1D fit result:   chi2="<<setw(10)<<r1.chi2<<"  a="<<setw(8)<<r1.a<<"  b="<<setw(8)<<r1.b<<endl;   
//      cout<<" 2D fit result:   chi2="<<setw(10)<<r2.chi2<<"  a="<<setw(8)<<r2.a<<"  b="<<setw(8)<<r2.b<<endl;   

      double weight=1.0;
      double c1=r1.chi2;
      double c2=r2.chi2;
     
      h1a.fill(c1,weight);
      h1b.fill(c2,weight);
    }

   h1a.write();
   h1b.write();

   return 0;
}
