set terminal svg size 600,500
set output "time_32.svg"
set title "time_32"
set ylabel 'avg run time (ms)'
plot 'stats_time.dat' with line


set terminal svg size 600,500
set output "cycles_32.svg"
set title "cycles_32"
set ylabel 'total cycles_32'
plot 'stats_cycles.dat' with line

set terminal svg size 600,500
set output "L1_miss_rate_32.svg"
set title 'L1_miss_rate_32'
set ylabel 'L1_miss_rate'
plot 'stats_L1_miss_rate.dat' with line

set terminal svg size 600,500
set output "L2_miss_rate_32.svg"
set title 'L2_miss_rate_32'
set ylabel 'L2_miss_rate'
plot 'stats_L2_miss_rate.dat' with line

set terminal svg size 600,500
set output "FLOP_32.svg"
set title "FLOP_32"
set ylabel 'FLOPS'
plot 'stats_FLOP.dat' with line

set terminal svg size 600,500
set output "TLB_32.svg"
set title "TLB_32"
set ylabel 'TLB access'
plot 'stats_TLB.dat' with line





