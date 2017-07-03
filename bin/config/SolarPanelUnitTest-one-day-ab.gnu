set terminal jpeg size 1280,800 enhanced font calibri 20
set output 'output\SolarPanelUnitTest-one-day-ab.jpeg' 
set title "Income/expense balance by 4kW solar panel on 12 April 2012" font "calibri,30"
set xlabel "Hour" font "calibri,24"
set ylabel "Yen" font "calibri,24"
set data style linespoints
set grid ytics lc rgb "#bbbbbb" lw 1 lt 0
set grid xtics lc rgb "#bbbbbb" lw 1 lt 0
#set yrange [0:*]  # as and if needed
plot 'output\SolarPanelUnitTest-one-day-ab.txt' using 1:2 title "Account balance" linecolor rgbcolor "blue"
