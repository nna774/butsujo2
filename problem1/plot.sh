#! /bin/bash

cat << EOS | gnuplot
set terminal png
set logscale x
set out 'error-per-delta.png'
p 'error.txt' u 1:3, 1/(2*(1+exp(1))) * log((1+exp(1))/exp(1))
set logscale y
set out 'error.png'
p 'error.txt' u 1:2
EOS
