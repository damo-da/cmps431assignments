CC=g++
CXX=g++
CXXFLAGS=-I. -g -std=c++11 -Wall -pedantic

.PHONY : all
all: utils.o run.o main.o
	@echo "Compiling"
	$(CC) $(CXXFLAGS) -o main main.o run.o utils.o
	@echo "Compilation complete"

clean: 
	rm -rf utils.o run.o main.o
	rm -rf ./main
	