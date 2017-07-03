set terminal jpeg size 1280,800 enhanced font calibri 20
set title "Rate of Investment for various wind turbines during 2003-2012" font "calibri,30"
set xlabel "Year" font "calibri,24"
set ylabel "Total account balance (man yen)" font "calibri,24"
set data style linespoints
set grid ytics lc rgb "#bbbbbb" lw 1 lt 0
set grid xtics lc rgb "#bbbbbb" lw 1 lt 0
#set xrange [0:13]    # as and if needed
set yrange [*:100]
set output 'output\WindTurbineRateOfInterest.jpeg' 
set multiplot
plot 'output\WindTurbineRateOfInterest.txt' using 1:2 title "12kW wind turbine -4.28%",\
	'output\WindTurbineRateOfInterest.txt' using 1:3 title "15kW wind turbine -1.75%",\
	'output\WindTurbineRateOfInterest.txt' using 1:4 title "20kW wind turbine 0.05%"
unset multiplot
