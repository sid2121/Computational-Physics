#include <iostream>
#include <math.h>
#include <stdlib.h>    // atoi, atof
#include <fstream>
#include <vector>

using namespace std;

//====================================================================
double yprime(double t, double y) {
   double yp=-y*y*y+sin(t);
   return yp;
}

//====================================================================
vector<double> Euler(double y0,double tmax, double dt) {

   cout<<"Euler   y0="<<y0<<"   tmax="<<tmax<<"   dt="<<dt<<endl;

   vector<double> yvec;

   double y=y0;
   for (double t=0.0; t<tmax; t=t+dt) {
      double ynext=y+yprime(t,y)*dt;
      yvec.push_back(y); //  sae y value in a vector to return
      // cout<<" Euler  "<<t<<"   "<<y<<endl;
      //   update y value...
      y=ynext;
   }

   cout<<"Euler:  returns "<<yvec.size()<<" y values."<<endl;

   return yvec;
}

//====================================================================
vector<double> RK4(double y0,double tmax, double dt) {

   cout<<"RK4   y0="<<y0<<"   tmax="<<tmax<<"   dt="<<dt<<endl;

   vector<double> yvec;

   double y=y0;
   for (double t=0.0; t<tmax; t=t+dt) {
      double k1=dt*yprime(t,y);
      double k2=dt*yprime(t+dt/2.0,y+k1/2.0);
      double k3=dt*yprime(t+dt/2.0,y+k2/2.0);
      double k4=dt*yprime(t+dt,y+k3);
      double ynext=y+(k1/6.0+k2/3.0+k3/3.0+k4/6.0);
      yvec.push_back(y); //  sae y value in a vector to return
      // cout<<"  RK4  "<<t<<"   "<<y<<endl;
      //   update y value...
      y=ynext;
   }

   cout<<"RK4:  returns "<<yvec.size()<<" y values."<<endl;
   return yvec;
}


//====================================================================
int main() {

  double tmax=10.0;
  double dt=0.001;
  double y0=0.0;

  vector<double> outEuler=Euler(y0,tmax,dt);
  vector<double> outRK4=RK4(y0,tmax,dt);

  ofstream outfile("odeSimple.txt");

  int i=-1;
  for(double t=0.0; t<tmax; t=t+dt){
     i++;   //  a counter to access values in vector...
     outfile<<"  "<<t<<"  "<<outEuler[i]<<"  "<<outRK4[i]<<endl;
  }

  outfile.close();

  return 0;
}
