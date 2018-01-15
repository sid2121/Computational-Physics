#!/bin/bash
set -e

g++ -std=c++11 -o wave2d hw9wave2D.cc

#  run for membrane wave with tmax 200
#  the name of executable is wave2d, created with -o option
./wave2d  200 

#  rename output txt files...
mv wave2Dfirst.txt wave2Dfirst_membrane.txt
mv wave2Dfull.txt  wave2Dfull_membrane.txt

#  create gif file with gnuplot
gnuplot<<EOF
reset
set terminal gif animate delay 10.0
set output "membrane_wave.gif"
stats "wave2Dfull_membrane.txt" nooutput
set zrange [-1:1]
do for [i=1:int(STATS_blocks)] {splot "wave2Dfull_membrane.txt" index i-1 using 2:3:4 with lines}
EOF

#  end of run2D.sh
