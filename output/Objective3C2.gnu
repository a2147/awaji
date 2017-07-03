set terminal jpeg size 1600,900 enhanced font calibri 20
set output 'output\Objective3C2.jpeg'
set title "Energetical self-sufficiency ratio for Awaji Island" font "calibri,26"
set xlabel "Month" font "calibri,20"
set ylabel "Energy (MWh)" font "calibri,20"
set data style linespoints
set grid ytics lc rgb "#bbbbbb" lw 1 lt 0
set grid xtics lc rgb "#bbbbbb" lw 1 lt 0
set xrange [0:13]
set yrange [0:22000]
set multiplot
plot 'output\Objective3C2.txt' using 1:2 title "Production 10000 houses - 27.63%",\
 'output\Objective3C2.txt' using 1:3 title "Production 10000 houses + 500 solar farms - 49.11%" linecolor rgbcolor "blue",\
	'output\Objective3C2.txt' using 1:4 title "Consumption in 53075 households"
unset multiplot
