#!/bin/bash
set -e

g++ -std=c++11 -o wave1d hw9wave1D.cc

#  run for string wave (option 1) with tmax 200
./wave1d  200  1 

#  rename output txt files...
mv wave1Dfirst.txt wave1Dfirst_string.txt
mv wave1Dfull.txt  wave1Dfull_string.txt

#  create gif file with gnuplot
gnuplot<<EOF
reset
set terminal gif animate delay 10.0
set output "string_wave.gif"
stats "wave1Dfull_string.txt" nooutput
set yrange [-0.15:0.15]
do for [i=1:int(STATS_blocks)] {plot "wave1Dfull_string.txt" index i-1 using 2:3 with lines}
EOF


#  run for sine wave (option 2) with tmax 200
./wave1d  200  2

#  rename output txt files...
mv wave1Dfirst.txt wave1Dfirst_sine.txt
mv wave1Dfull.txt  wave1Dfull_sine.txt

#  create gif file with gnuplot
gnuplot<<EOF
reset
set terminal gif animate delay 10.0
set output "sine_wave.gif"
stats "wave1Dfull_sine.txt" nooutput
set yrange [-0.15:0.15]
do for [i=1:int(STATS_blocks)] {plot "wave1Dfull_sine.txt" index i-1 using 2:3 with lines}
EOF

#  end of run1D.sh
