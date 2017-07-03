set terminal jpeg size 1280,800 enhanced font calibri 20
set output 'output\Objective3A.jpeg' 
set title "Total income/expense of 10000 households" font "calibri,20"
set xlabel "Month" font "calibri,15"
set ylabel "Man yen" font "calibri,15"
set data style linespoints
set grid ytics lc rgb "#bbbbbb" lw 1 lt 0
set grid xtics lc rgb "#bbbbbb" lw 1 lt 0
#set yrange [0:12]  # as and if needed
set xrange [0:13]  # as and if needed
set multiplot 
plot 'output\Objective3A.txt' using 1:2 title "Income",\
	'output\Objective3A.txt' using 1:3 title "Expense" linecolor rgbcolor "blue"
unset multiplot