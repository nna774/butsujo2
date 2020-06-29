#! /bin/bash

cat << EOS | gnuplot
set terminal png
set out 'orbit.png'
p [-0.5:0.5][-0.5:0.5] \
  'non.dat' index 1 with lines
set out 'orbit-kasane.png'
p [-0.5:0.5][-0.5:0.5] \
  'non.dat' index 0 with lines, \
  'non.dat' index 1 with lines, \
  'non.dat' index 2 with lines, \
  'non.dat' index 3 with lines
set out 'rela-orbit.png'
p [-0.5:0.5][-0.5:0.5] \
  'rela.dat' index 1 with lines
set out 'rela-orbit-kasane.png'
p [-0.5:0.5][-0.5:0.5] \
  'rela.dat' index 0 with lines, \
  'rela.dat' index 1 with lines, \
  'rela.dat' index 2 with lines, \
  'rela.dat' index 3 with lines
EOS
