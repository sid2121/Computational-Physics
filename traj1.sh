#!/bin/bash
set -e

# chmod u+x traj1.sh
# to change this sh file to executable (x-mode)...
# ./traj1.sh
# to execute this shell script...

echo "compiling range1.cc and execute..."

g++ -std=c++11 range1.cc
./a.out

echo "starting gnuplot..."

gnuplot <<EOF
set terminal pngcairo
set output "traj1.png"

set xlabel "X (m)"
set ylabel "Y (m)"

plot "xytraj_10.txt" using 3:4 with lines, \
     "xytraj_20.txt" using 3:4 with lines, \
     "xytraj_30.txt" using 3:4 with lines
EOF

#  display a plot using "display"...
echo "display is starting. CTRL-C in this window to terminate it."

display traj1.png

# end of traj.sh
