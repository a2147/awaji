set terminal jpeg size 1280,800 enhanced font calibri 20
set output 'output\SolarPanelUnitTest-one-year.jpeg' 
set title "Energy production by 4kW solar panel" font "calibri,30"
set xlabel "Month" font "calibri,24"
set ylabel "Energy (kWh)" font "calibri,24"
set data style linespoints
set grid ytics lc rgb "#bbbbbb" lw 1 lt 0
set grid xtics lc rgb "#bbbbbb" lw 1 lt 0
#set xrange [0:13]    # as and if needed
set yrange [0:*]  # as and if needed
set xrange [0:13]
set multiplot 
plot 'output\SolarPanelUnitTest-one-year.txt' using 1:2 title "Production",\
	'output\SolarPanelUnitTest-one-year.txt' using 1:3 title "Consumption" linecolor rgbcolor "blue"
unset multiplot