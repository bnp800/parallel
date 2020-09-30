type = d
mode = 0 
modelist = 0 1 2 3 4 5
source1 = a.txt
source2 = b.txt
dst = c.txt
.PHONY: test run_generateMatrix run_main run_testing
test: run_generateMatrix run_main run_testing

report: run_test cal_avg run_gnuplot

run_test:test
	for n in $(modelist); do\
		./generateMatrix $(source1) $(source2) $(type);\
		./main $(source1) $(source2) $(dst) $$n; \
		./generateMatrix $(source1) $(source2) $(type);\
		./main $(source1) $(source2) $(dst) $$n; \
		./generateMatrix $(source1) $(source2) $(type);\
		./main $(source1) $(source2) $(dst) $$n; \
		./generateMatrix $(source1) $(source2) $(type);\
		./main $(source1) $(source2) $(dst) $$n; \
		./generateMatrix $(source1) $(source2) $(type);\
		./main $(source1) $(source2) $(dst) $$n; \
		./generateMatrix $(source1) $(source2) $(type);\
		./main $(source1) $(source2) $(dst) $$n; \
		./generateMatrix $(source1) $(source2) $(type);\
		./main $(source1) $(source2) $(dst) $$n; \
		./generateMatrix $(source1) $(source2) $(type);\
		./main $(source1) $(source2) $(dst) $$n; \
		./generateMatrix $(source1) $(source2) $(type);\
		./main $(source1) $(source2) $(dst) $$n; \
		./generateMatrix $(source1) $(source2) $(type);\
		./main $(source1) $(source2) $(dst) $$n; \
		./generateMatrix $(source1) $(source2) $(type);\
		./main $(source1) $(source2) $(dst) $$n; \
		done
		

run_gnuplot: stats.p
	gnuplot stats.p

cal_avg: stats.dat avg
	./avg 

avg: avg.cpp
	g++ avg.cpp -o avg

generateMatrix: generateMatrix.cpp
	g++ generateMatrix.cpp -o generateMatrix

run_generateMatrix: generateMatrix
	./generateMatrix $(source1) $(source2) $(type)

main: matrix.cpp main.cpp 
	g++ matrix.cpp main.cpp -o main

run_main: main
	./main $(source1) $(source2) $(dst) $(mode)

testing: test.cpp matrix.cpp
	g++ matrix.cpp test.cpp -o testing

run_testing: testing
	./testing $(source1) $(source2) $(dst)

clean:
	rm generateMatrix 
	rm main
	rm testing
	rm stats.dat
	rm avg
