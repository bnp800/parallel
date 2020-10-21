set terminal svg size 600,500
set output "time_optim.svg"
set title "time_optim"
set ylabel 'avg run time (ms)'
plot 'stats_time.dat' with line


set terminal svg size 600,500
set output "cycles_optim.svg"
set title "cycles_optim"
set ylabel 'total cycles_optim'
plot 'stats_cycles.dat' with line

set terminal svg size 600,500
set output "L1_miss_rate_optim.svg"
set title 'L1_miss_rate_optim'
set ylabel 'L1_miss_rate'
plot 'stats_L1_miss_rate.dat' with line

set terminal svg size 600,500
set output "L2_miss_rate_optim.svg"
set title 'L2_miss_rate_optim'
set ylabel 'L2_miss_rate'
plot 'stats_L2_miss_rate.dat' with line

set terminal svg size 600,500
set output "FLOP_optim.svg"
set title "FLOP_optim"
set ylabel 'FLOPS'
plot 'stats_FLOP.dat' with line

set terminal svg size 600,500
set output "TLB_optim.svg"
set title "TLB_optim"
set ylabel 'TLB access'
plot 'stats_TLB.dat' with line





