#! /bin/bash

cat << EOS | gnuplot
set terminal png
set out 'orbit.png'
p 'orbit.dat' index 0 u 1:2 title 'euler', \
  'orbit.dat' index 1 u 1:2 title 'RK2', \
  'orbit.dat' index 2 u 1:2 title 'RK4', \
  'orbit.dat' index 3 u 1:2 title 'symp'
EOS
