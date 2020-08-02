#! /bin/bash

cat << EOS | gnuplot
set terminal png
set out 'graph.png'
p [0:10][0:0.9] 'implicit.txt' with p, \
for [i=0:5] 1/sqrt(4 * pi * 0.1 * (i + 1)) * exp(-(x - 5) ** 2/(4 * 0.1 * (i + 1))) with lines title sprintf('t=%d', i)
set out 'errors.png'
p 'errors.txt' index 0 with p t 'L = 5/3', \
  'errors.txt' index 1 with p t 'L = 1/3'
EOS
