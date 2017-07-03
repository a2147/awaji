set terminal jpeg size 1280,800 enhanced font calibri 20
set output 'output\SolarPanelUnitTest-one-year-6.jpeg' 
set title "Energy production by various solar panels and average consumption" font "calibri,30"
set xlabel "Month" font "calibri,24"
set ylabel "Energy (kWh)" font "calibri,24"
set data style linespoints
set grid ytics lc rgb "#bbbbbb" lw 1 lt 0
set grid xtics lc rgb "#bbbbbb" lw 1 lt 0
#set xrange [0:13]    # as and if needed
set yrange [0:*]  # as and if needed
set xrange [0:13]
set multiplot 
plot 'output\SolarPanelUnitTest-one-year-6.txt' using 1:2 title "Production 3kW solar panel",\
	'output\SolarPanelUnitTest-one-year-6.txt' using 1:3 title "Production 4kW solar panel",\
	'output\SolarPanelUnitTest-one-year-6.txt' using 1:4 title "Production 5kW solar panel",\
	'output\SolarPanelUnitTest-one-year-6.txt' using 1:5 title "Production 6kW solar panel",\
	'output\SolarPanelUnitTest-one-year-6.txt' using 1:6 title "Production 8kW solar panel",\
	'output\SolarPanelUnitTest-one-year-6.txt' using 1:7 title "Production 10kW solar panel",\
	'output\SolarPanelUnitTest-one-year-6.txt' using 1:8 title "Consumption"
unset multiplot