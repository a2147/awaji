set terminal jpeg size 1280,800 enhanced font calibri 20
set output 'output\WindTurbineUnitTest-one-month-ab.jpeg' 
set title "Income/expense balance by 20kW wind turbine in July 2012" font "calibri,30"
set xlabel "Day of month" font "calibri,24"
set ylabel "Yen" font "calibri,24"
set data style linespoints
set grid ytics lc rgb "#bbbbbb" lw 1 lt 0
set grid xtics lc rgb "#bbbbbb" lw 1 lt 0
#set yrange [0:*]  # as and if needed
set xrange [0:32]
plot 'output\WindTurbineUnitTest-one-month-ab.txt' using 1:2 title "Account balance" linecolor rgbcolor "blue"

