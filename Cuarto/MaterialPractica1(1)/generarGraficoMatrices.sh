#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "graficoMatrices.eps"
set key right bottom
set xlabel "Orden matriz"
#X
set ylabel "Tiempos (microsegundos)"
#Y
plot 'datosFinalesM.txt' using 1:2 t "Tiempo Real", 'datosFinalesM.txt' using 1:3 t "Tiempo Estimado" w l 
_end_
