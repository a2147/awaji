set terminal jpeg size 1600,900 enhanced font calibri 20
set output 'output\Objective3D.jpeg'
set title "Energy production at the Awaji Island different sources" font "calibri,26"
set xlabel "Month" font "calibri,20"
set ylabel "Energy (MWh)" font "calibri,20"
set data style linespoints
set grid ytics lc rgb "#bbbbbb" lw 1 lt 0
set grid xtics lc rgb "#bbbbbb" lw 1 lt 0
set xrange [0:13]
set yrange [0:22000]
set multiplot
plot 'output\Objective3D.txt' using 1:2 title "10000 residental solar panels - 27.63%",\
	'output\Objective3D.txt' using 1:3 title "CEF+Kandens wind farm - 31.31%",\
	'output\Objective3D.txt' using 1:4 title "Kandens solar farm - 17.18%",\
	'output\Objective3D.txt' using 1:5 title "500 private solar farms - 21.48%",\
	'output\Objective3D.txt' using 1:6 title "Consumption in 53075 houses"
unset multiplot
