mode = 0
modelist = 0 1 2 3 4 5
MAKE = make
DIR = ../test1/
all: run test clean
src1 = a.txt
src2 = b.txt
dst = c.txt 
dir = ../test2/
st = stats_
stlist = time L1_miss_rate L2_miss_rate cycles FLOP TLB
sts = .dat
avg.cpp = avg.cpp
avg.o = avg
run_num = 5

report: stats avg draw clean
avg: com_avg
	for n in $(stlist); do \
	$(DIR)$(avg.o) $(st)$$n$(sts) $(run_num); \
	done

com_avg:
	cd $(DIR) && g++ $(avg.cpp) -o $(avg.o)

draw:
	gnuplot plot.p

stats: main run_generator
	for n in $(modelist); do \
	./main $(DIR)$(src1) $(DIR)$(src2) $(DIR)$(dst) $$n; \
	./main $(DIR)$(src1) $(DIR)$(src2) $(DIR)$(dst) $$n; \
	./main $(DIR)$(src1) $(DIR)$(src2) $(DIR)$(dst) $$n; \
	./main $(DIR)$(src1) $(DIR)$(src2) $(DIR)$(dst) $$n; \
	./main $(DIR)$(src1) $(DIR)$(src2) $(DIR)$(dst) $$n; \
	done

run: main run_generator
	./main $(DIR)$(src1) $(DIR)$(src2) $(DIR)$(dst) $(mode)

main: blockMult.cpp ../test1/matrix.cpp
	g++ blockMult.cpp $(DIR)matrix.cpp -o main -I/${PAPI_DIR}/include -L/${PAPI_DIR}/lib -lpapi

run_generator:
	cd $(DIR) && $(MAKE) run_generateMatrix

test: ../test1/makefile
	cd $(DIR) && $(MAKE) run_testing

clean:
	rm stats*

