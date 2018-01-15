//
//  g++ -std-c++11 zzhist.cc mainExperimentMany.cc 
//
#include <iostream>
#include <fstream>
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
Data SimulateOneExperiment(int expNo) {
  Data data;
   // define 10 points where we measure y-value.
  double x[10]={1.,2.,3.,4.,5.,6.,7.,8.,9.,10};

  for(int i=0; i<10; i++) {
     double ytrue=0.3*x[i]+2.0;
     double sigma=0.1;
     double ymeas=ytrue+zzrandG(0.0, sigma);
     Point p;
     p.x=x[i];
     p.ytrue=ytrue;
     p.ymeas=ymeas;
     p.yerror=sigma;
     // save a point in data.
     data.xyvector.push_back(p);
  }

  data.experimentNumber=expNo;
  int n=data.xyvector.size();
  cout<<"  expriment number = "<<expNo<<"  no of points ="<<n<<endl; 

  return data;
}

//====================================================================
void doOneExperiment(int expNo){

  Data d=SimulateOneExperiment(expNo);

  // write data in output file
  string fname="mydata/experiment_"+to_string(expNo)+".txt";
  ofstream outfile(fname);
  // check the status of the output file. If error, just return t caller.
     if(outfile.is_open()) {
         cout<<"output file "<<fname<<" is created"<<endl;
     }
     else {
         cout<<"error:  output file "<<fname<<" is not open."<<endl;
         cout<<"a sub-direcory mydata is required.  do mkdir mydata"<<endl;
         return;
     }
  
  int npoints=d.xyvector.size();
  cout<<" data points = "<<npoints<<endl;
  for (int i=0; i<npoints; i++) {
      double x=d.xyvector[i].x;
      double ymeas=d.xyvector[i].ymeas;
      double ytrue=d.xyvector[i].ytrue;;
      double yerror=d.xyvector[i].yerror;
      cout<<setw(10)<<x<<setw(10)<<ytrue<<setw(10)<<ymeas<<setw(10)<<yerror<<endl;
      outfile<<setw(10)<<x<<setw(10)<<ytrue<<setw(10)<<ymeas<<setw(10)<<yerror<<endl;
  }
  outfile.close();

  return;
}

//====================================================================
int main() {

  int nExperiments=1000;
  for(int i=0; i<nExperiments; i++) {
     int expNumber=i;
     doOneExperiment(expNumber);
  }  

  return 0;
}
