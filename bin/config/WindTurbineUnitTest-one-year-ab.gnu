set terminal jpeg size 1280,800 enhanced font calibri 20
set output 'output\WindTurbineUnitTest-one-year-ab.jpeg' 
set title "Income/expense balance by 20kW wind turbine" font "calibri,30"
set xlabel "Month" font "calibri,24"
set ylabel "Yen" font "calibri,24"
set data style linespoints
set grid ytics lc rgb "#bbbbbb" lw 1 lt 0
set grid xtics lc rgb "#bbbbbb" lw 1 lt 0
set xrange [0:13]    # as and if needed
#set yrange [0:*]  # as and if needed
#set multiplot 
plot 'output\WindTurbineUnitTest-one-year-ab.txt' using 1:2 title "Account balance" linecolor rgbcolor "blue"
#unset multiplot