#! /bin/bash

cat << EOS | gnuplot
set terminal png
set out 'graph.png'
p 'oddf.dat' t 'odd' with lp, \
  'evenf.dat' t 'even' with lp
EOS
