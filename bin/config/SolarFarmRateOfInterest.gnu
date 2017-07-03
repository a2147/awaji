set terminal jpeg size 1280,800 enhanced font calibri 20
set title "Rate of Investment for 73kW solar farm during 2003-2012" font "calibri,30"
set xlabel "Year" font "calibri,24"
set ylabel "Total account balance (man yen)" font "calibri,24"
set data style linespoints
set grid ytics lc rgb "#bbbbbb" lw 1 lt 0
set grid xtics lc rgb "#bbbbbb" lw 1 lt 0
#set xrange [0:13]    # as and if needed
#set yrange [0:*]
set output 'output\SolarFarmRateOfInterest.jpeg' 
set multiplot
plot 'output\SolarFarmRateOfInterest.txt' using 1:2 title "73kW solar farm 30.08%",\
	'output\SolarFarmRateOfInterest.txt' using 1:3 title "73kW solar incl. 4.5% bank loan 15.20%"
unset multiplot
