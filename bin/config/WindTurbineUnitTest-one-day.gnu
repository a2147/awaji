set terminal jpeg size 1280,800 enhanced font calibri 20
set output 'output\WindTurbineUnitTest-one-day.jpeg' 
set title "Energy production by 20kW wind turbine on 12 April 2012" font "calibri,30"
set xlabel "Hour" font "calibri,24"
set ylabel "Energy (kWh)" font "calibri,24"
set data style linespoints
set grid ytics lc rgb "#bbbbbb" lw 1 lt 0
set grid xtics lc rgb "#bbbbbb" lw 1 lt 0
#set yrange [0:2300]
set yrange [0:*]
set xrange [0:25]
set multiplot
plot 'output\WindTurbineUnitTest-one-day.txt' using 1:2 title "Production",\
	'output\WindTurbineUnitTest-one-day.txt' using 1:3 title "Consumption" linecolor rgbcolor "blue"
unset multiplot
