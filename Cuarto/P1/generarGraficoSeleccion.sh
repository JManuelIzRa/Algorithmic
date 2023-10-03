#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "graficoOrdenacion.eps"
set key right bottom
set xlabel "Numero de elementos."
#X
set ylabel "Tiempos (microsegundos)"
#Y
plot 'datosFinales.txt' using 1:2 t "Tiempo Real" w l, 'datosFinales.txt' using 1:3 t "Tiempo Estimado" w l 
_end_
