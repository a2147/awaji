set terminal jpeg size 1280,800 enhanced font calibri 20
set title "Average flux of solar radiation during 2008-2012" font "calibri,30"
set xlabel "Month" font "calibri,24"
set ylabel "Solar radiation (kWh/m2)" font "calibri,24"
set data style linespoints
set grid ytics lc rgb "#bbbbbb" lw 1 lt 0
set grid xtics lc rgb "#bbbbbb" lw 1 lt 0
set xrange [0:13]    # as and if needed
set yrange [0:*]
set output 'output\SolarPanelUnitTest-function-avg.jpeg' 
set multiplot
plot 'output\SolarPanelUnitTest-function-avg.txt'  using 1:2 title "Perfect weather conditions at the Awaji Island",\
	'output\SolarPanelUnitTest-function-avg.txt'  using 1:3 title "5 years average for Awaji Island weather" linecolor rgbcolor "blue"
unset multiplot
