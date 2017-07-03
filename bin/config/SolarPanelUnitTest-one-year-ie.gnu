set terminal jpeg size 1280,800 enhanced font calibri 20
set output 'output\SolarPanelUnitTest-one-year-ie.jpeg' 
set title "Income/expense by 4kW solar panel" font "calibri,30"
set xlabel "Month" font "calibri,24"
set ylabel "Yen" font "calibri,24"
set data style linespoints
set grid ytics lc rgb "#bbbbbb" lw 1 lt 0
set grid xtics lc rgb "#bbbbbb" lw 1 lt 0
#set yrange [0:*]  # as and if needed
set xrange [0:13]
set multiplot 
plot 'output\SolarPanelUnitTest-one-year-ie.txt' using 1:2 title "Income",\
	'output\SolarPanelUnitTest-one-year-ie.txt' using 1:3 title "Expense" linecolor rgbcolor "blue"
unset multiplot