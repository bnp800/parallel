mode = 0;
MAKE = make

all: run test clean

run: main run_generator
	./main ../test1/a.txt ../test1/b.txt ../test/c.txt $(mode)

main: blockMult.cpp ../test1/matrix.cpp
	g++ blockMult.cpp ../test1/matrix.cpp -o main -lpapi

run_generator:
	cd ../test1/ && $(MAKE) run_generateMatrix

test: ../test1/makefile
	cd ../test1/ && $(MAKE) run_testing

clean:
	rm ./main
