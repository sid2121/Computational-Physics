//
//  g++ -std=c++11 mainReadHistogram.cc 
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

// ==========================================================================
int main() {

   string inname="zzh1_hist2.txt";
   ifstream infile(inname);

   //  error checking...
   if(!(infile.is_open())) {
      cout<<"error:  input file "<<inname<<" is not open."<<endl;
      return 1;
   }
 
   string line;
 
   if(infile.is_open()) {
      while (getline(infile,line)) { 
          if(line.size()==0) {continue;}
          // cout<<line<<endl;
          // if linse start with #, skip it...
          if(line.compare(0,1,"#")==0) {continue;}

          double x, y;

          std::istringstream iss(line);
          iss>>x>>y;
          cout<<" x "<<x<<" y "<<y<<endl;

      }
   }

   return 0;
}
