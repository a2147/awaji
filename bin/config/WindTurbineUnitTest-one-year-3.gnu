set terminal jpeg size 1280,800 enhanced font calibri 20
set output 'output\WindTurbineUnitTest-one-year-3.jpeg' 
set title "Energy production by various wind turbines and average consumption" font "calibri,30"
set xlabel "Month" font "calibri,24"
set ylabel "Energy (kWh)" font "calibri,24"
set data style linespoints
set grid ytics lc rgb "#bbbbbb" lw 1 lt 0
set grid xtics lc rgb "#bbbbbb" lw 1 lt 0
set xrange [0:13]    # as and if needed
set yrange [0:*]  # as and if needed
set multiplot 
plot 'output\WindTurbineUnitTest-one-year-3.txt' using 1:2 title "Production 5kW wind turbine",\
	'output\WindTurbineUnitTest-one-year-3.txt' using 1:3 title "Production 10kW wind turbine",\
	'output\WindTurbineUnitTest-one-year-3.txt' using 1:4 title "Production 20kW wind turbine",\
	'output\WindTurbineUnitTest-one-year-3.txt' using 1:5 title "Consumption"
unset multiplot