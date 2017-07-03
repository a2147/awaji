set terminal jpeg size 1280,800 enhanced font calibri 20
set title "Rate of Investment for various solar panels during 2003-2012" font "calibri,30"
set xlabel "Year" font "calibri,24"
set ylabel "Total account balance (man yen)" font "calibri,24"
set data style linespoints
set grid ytics lc rgb "#bbbbbb" lw 1 lt 0
set grid xtics lc rgb "#bbbbbb" lw 1 lt 0
#set xrange [0:13]    # as and if needed
#set yrange [0:*]
set output 'output\SolarPanelRateOfInterest.jpeg' 
set multiplot
plot 'output\SolarPanelRateOfInterest.txt' using 1:2 title "3kW solar panel 11.10%",\
	'output\SolarPanelRateOfInterest.txt' using 1:3 title "4kW solar panel 19.20%",\
	'output\SolarPanelRateOfInterest.txt' using 1:4 title "5kW solar panel 26.55%",\
	'output\SolarPanelRateOfInterest.txt' using 1:5 title "6kW solar panel 28.38%",\
	'output\SolarPanelRateOfInterest.txt' using 1:6 title "8kW solar panel 32.59%",\
	'output\SolarPanelRateOfInterest.txt' using 1:7 title "10kW solar panel 37.21%"
unset multiplot
