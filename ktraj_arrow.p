set xlabel "x"
set ylabel "y"

factor=5.0

plot  "gplotdir/odeTraj_K000a.txt" using 2:3:($4*factor):($5*factor)  title "k=0.00" with vectors filled head ,\
     "gplotdir/odeTraj_K005a.txt" using 2:3:($4*factor):($5*factor) title "k=0.005"  with vectors filled head ,\
     "gplotdir/odeTraj_K01a.txt" using 2:3:($4*factor):($5*factor) title "k=0.01" with vectors filled head ,\
     "gplotdir/odeTraj_K02a.txt" using 2:3:($4*factor):($5*factor) title "k=0.02" with vectors filled head ,\
     "gplotdir/odeTraj_K04a.txt" using 2:3:($4*factor):($5*factor) title "k=0.04"  with vectors filled head ,\
     "gplotdir/odeTraj_K08a.txt" using 2:3:($4*factor):($5*factor) title "k=0.08"  with vectors filled head ,\
     0 
