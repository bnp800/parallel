mode = 1;
MAKE = make
DIR = ../test1/
all: run test clean

run: main run_generator
	./main $(DIR)a.txt $(DIR)b.txt $(DIR)c.txt $(mode)

main: blockMult.cpp ../test1/matrix.cpp
	g++ blockMult.cpp $(DIR)matrix.cpp -o main -lpapi

run_generator:
	cd $(DIR) && $(MAKE) run_generateMatrix

test: ../test1/makefile
	cd $(DIR) && $(MAKE) run_testing

clean:
	rm ./main
