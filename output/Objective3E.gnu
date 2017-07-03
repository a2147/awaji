set terminal jpeg size 1600,900 enhanced font calibri 20
set output 'output\Objective3E.jpeg'
set title "Smart Grid at the Awaji Island - sufficiency ratio 97.59%" font "calibri,26"
set xlabel "Month" font "calibri,20"
set ylabel "Energy (MWh)" font "calibri,20"
set data style linespoints
set grid ytics lc rgb "#bbbbbb" lw 1 lt 0
set grid xtics lc rgb "#bbbbbb" lw 1 lt 0
set xrange [0:13]
set yrange [0:22000]
set multiplot
plot 'output\Objective3E.txt' using 1:2 title "Agregated energy production",\
	'output\Objective3E.txt' using 1:3 title "Consumption in 53075 house"  linecolor rgbcolor "blue"
unset multiplot
