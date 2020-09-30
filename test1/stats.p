set terminal svg size 600,500
set output "stats.svg"
set title 'stats'
set xlabel 'running mode 0-ijk,1-ikj,2-kij,3-jik,4-jki,5-kji'
set ylabel 'avg time in seconds'
set xtics 0,1,5
plot 'stats.dat' with line
