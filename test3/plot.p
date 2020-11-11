set terminal svg size 600,500 enhanced background rgb 'white'
set output "time.svg"
set title "time"
set ylabel 'time(s)'
set xlabel 'number of process'
plot 'time.dat' u 1:2 title 'total time' with line,'time.dat' u 1:3  title 'max time' w l 

