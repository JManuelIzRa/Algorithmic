#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "graficoComparativo.eps"
set key right bottom
set xlabel "Numero de elementos"
#X
set ylabel "Tiempos"
#Y
plot 'datosFinalesFusion.txt' using 1:2 t "Tiempo Fusion" w l, 'datosFinalesQuicksort.txt' using 1:3 t "Tiempo Quicksort" w l 
_end_
