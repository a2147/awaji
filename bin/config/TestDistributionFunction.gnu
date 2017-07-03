set terminal jpeg size 800,600 enhanced font calibri 20
set output 'output\TestDistributionFunction.jpeg' 
set title "Test of Distribution of Energy Consumption" font "calibri,20"
set xlabel "x" font "calibri,15"
set ylabel "y" font "calibri,15"
set data style linespoints
set grid ytics lc rgb "#bbbbbb" lw 1 lt 0
set grid xtics lc rgb "#bbbbbb" lw 1 lt 0
#set xrange [0:13]    # as and if needed
#set yrange [0:*]  # as and if needed
#set multiplot 
plot 'output\TestDistributionFunction.txt' #using 1:2 title "Production"
#replot 'output\Objective2D.txt' using 1:3 title "Consumption"#
#unset multiplot