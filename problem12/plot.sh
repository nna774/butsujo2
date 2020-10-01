#! /bin/bash

cat << EOS | gnuplot
set terminal png
set out 'orbit.png'
p \
  'orbit.dat' index 0 with lines, \
  'orbit.dat' index 1 with lines, \
  'orbit.dat' index 2 with lines, \
  'orbit.dat' index 3 with lines, \
  'orbit.dat' index 4 with lines
EOS
