#! /bin/bash

cat << EOS | gnuplot
set terminal png
set out 'min.png'
p [0:0.6][0:0.6] \
  'mindist.dat' u 1:2, \
  x / sqrt(1 + x ** 2)
set out 'orbit.png'
set view 40, 120, 1.25
sp [-0.1:1][-1:1][-0.5:0.5] \
  'orbit.dat' using 1:2:3 index 0 with lines, \
  'orbit.dat' using 1:2:3 index 1 with lines, \
  'orbit.dat' using 1:2:3 index 2 with lines, \
  'orbit.dat' using 1:2:3 index 3 with lines
EOS
