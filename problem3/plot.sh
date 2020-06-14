#! /bin/bash

cat << EOS | gnuplot
set terminal png
set out 'orbit.png'
p [x=-3:0.5][y=-3:3] 'RK2.dat' with linespoints, \
                     'RK2_polar.dat' with linespoints, \
                     'RK4.dat' with linespoints
EOS
