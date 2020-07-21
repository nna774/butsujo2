#! /bin/bash

cat << EOS | gnuplot
set terminal png
set out 'graph.png'
p 'pde1ddif.txt' with lines
set out 'graph-x10.png'
p 'pde1ddif-x10.txt' with lines
set term gif animate optimize delay 6 size 480,360
set output 'movie.gif'
do for [i=0:29] {
  p [0:10][0:1] 'pde1ddif.txt' index i with lines
}
EOS
