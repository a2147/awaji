set terminal jpeg size 1280,800 enhanced font calibri 20
set title "Flux of solar radiation during 2008-2012" font "calibri,30"
set xlabel "Month" font "calibri,24"
set ylabel "Solar radiation (kWh/m2)" font "calibri,24"
set data style linespoints
set grid ytics lc rgb "#bbbbbb" lw 1 lt 0
set grid xtics lc rgb "#bbbbbb" lw 1 lt 0
set xrange [0:13]    # as and if needed
set yrange [0:*]
set output 'output\SolarPanelUnitTest-function.jpeg' 
set multiplot
plot 'output\SolarPanelUnitTest-function.txt'  using 1:2 title "Perfect weather conditions",\
	'output\SolarPanelUnitTest-function.txt'  using 1:3 title "Awaji Island weather in 2008",\
	'output\SolarPanelUnitTest-function.txt'  using 1:4 title "Awaji Island weather in 2009",\
	'output\SolarPanelUnitTest-function.txt'  using 1:5 title "Awaji Island weather in 2010",\
	'output\SolarPanelUnitTest-function.txt'  using 1:6 title "Awaji Island weather in 2011",\
	'output\SolarPanelUnitTest-function.txt'  using 1:7 title "Awaji Island weather in 2012"
unset multiplot
