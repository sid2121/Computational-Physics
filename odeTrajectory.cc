#include <iostream>
#include <math.h>
#include <stdlib.h>    // atoi, atof
#include <fstream>
#include <vector>

using namespace std;

double kconstant;   // gloabl variable. (not recommended, but ok for small program)

//====================================================================
struct str_state{
   double time;
   double x;
   double y;
   double vx;
   double vy;
} ;   // need a semicolon for struct.

//====================================================================
struct str_dxdt{
   double dxdt;
   double dydt;
   double dvdtX;
   double dvdtY;
} ;   // need a semicolon for struct.

//====================================================================
str_dxdt derivs(str_state s) {
   str_dxdt a;

   a.dxdt=s.vx;    // dx/dt
   a.dydt=s.vy;    // dy/dt
   a.dvdtX=-kconstant*s.vx ;    // dvx/dt
   a.dvdtY=-9.8-kconstant*s.vy ;    // dvy/dt

   return a;
}

//====================================================================
vector<str_state> Euler(str_state s0,double tmax, double dt) {

   vector<str_state> statevector;

   str_state s=s0;    // set initial state...
   for (double t=0.0; t<tmax; t=t+dt) {
      s.time=t;
      str_dxdt d = derivs(s);
      
      str_state snext;
      snext.time=t;
      snext.x= s.x + d.dxdt * dt;
      snext.y= s.y + d.dydt * dt;
      snext.vx= s.vx + d.dvdtX * dt;
      snext.vy= s.vy + d.dvdtY * dt;
   
      statevector.push_back(s); //  sae y value in a vector to return
      //   update the state values...
      s=snext;
      // if(s.y < -10000.0) break;
      if(s.y < 0.0) break;
   }

   // cout<<"Euler:  returns "<<yvec.size()<<" y values."<<endl;

   return statevector;
}

//====================================================================
void Trajectory(string outID){

  double tmax=10000.0;
  double dt=0.01;

  double v0=300.0;
  double theta=30.0*3.1415/180.0;

  //  save the initial state in a structure s_state.
  str_state s;
  s.x=0.0;
  s.y=0.0;
  s.vx=v0*cos(theta);
  s.vy=v0*sin(theta);

  //  return value is a vector of states...
  vector<str_state> outEuler=Euler(s,tmax,dt);

  string outname="odeTraj_"+outID+".txt";
  ofstream outfile(outname);

  int npoints=outEuler.size();
  for(int i=0; i<npoints; i++){
     outfile<<"  "<<outEuler[i].time ;
     outfile<<"  "<<outEuler[i].x<<"  "<<outEuler[i].y ;
     outfile<<"  "<<outEuler[i].vx<<"  "<<outEuler[i].vy ;
     outfile<<endl;
  }

  outfile.close();

   return;
}
//====================================================================
int main() {

  kconstant=0.0;
  Trajectory("K000");  

  kconstant=0.005;
  Trajectory("K005");

  return 0;
}
