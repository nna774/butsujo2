#! /bin/bash

cat << EOS | gnuplot
set terminal png
set out 'orbit.png'
p 'eps0.dat' with lines, \
  'eps01.dat' with lines, \
  'eps001.dat' with lines, \
  'eps0001.dat' with lines
set logscale x
set logscale y
set out 'T.png'
p 'eps-T.dat' with linespoints
EOS
