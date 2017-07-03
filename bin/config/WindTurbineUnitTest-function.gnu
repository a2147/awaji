set terminal jpeg size 1280,800 enhanced font calibri 20
set output 'output\WindTurbineUnitTest-function.jpeg' 
set title "Power curve of 20kW wind turbine" font "calibri,30"
set xlabel "Wind speed (m/s)" font "calibri,24"
set ylabel "Power (kW)" font "calibri,24"
set data style linespoints
set grid ytics lc rgb "#bbbbbb" lw 1 lt 0
set grid xtics lc rgb "#bbbbbb" lw 1 lt 0
set xrange [0:30]    # as and if needed
set yrange [0:23]  # as and if needed
plot 'output\WindTurbineUnitTest-function.txt' using 1:2 title "Simulation output" linecolor rgbcolor "blue"
