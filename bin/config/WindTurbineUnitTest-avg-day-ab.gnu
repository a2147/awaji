set terminal jpeg size 1280,800 enhanced font calibri 20
set output 'output\WindTurbineUnitTest-avg-day-ab.jpeg' 
set title "Average hourly energy production by 20kW wind turbine" font "calibri,30"
set xlabel "Hour" font "calibri,24"
set ylabel "Yen" font "calibri,24"
set data style linespoints
set grid ytics lc rgb "#bbbbbb" lw 1 lt 0
set grid xtics lc rgb "#bbbbbb" lw 1 lt 0
#set yrange [0:*]  # as and if needed
plot 'output\WindTurbineUnitTest-avg-day-ab.txt' using 1:2 title "Account balance" linecolor rgbcolor "blue"

