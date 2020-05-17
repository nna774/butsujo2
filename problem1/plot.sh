#! /bin/bash

cat << EOS | gnuplot
set terminal png
set out 'error-per-delta.png'
set logscale x
p 'error.txt' u 1:3 with linespoints, 1/(2*(1+exp(1))) * log((1+exp(1))/exp(1))
set out 'error.png'
set logscale y
p 'error.txt' u 1:2 with linespoints
EOS
