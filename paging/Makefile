CC=g++
CXX=g++
CXXFLAGS=-I. -g -std=c++11 -Wall -pedantic

.DEFAULT_GOAL := all

.PHONY : all
all: main.o algorithms.o utils.o memory_utils.o
	@echo "Compiling"
	@$(CC) $(CXXFLAGS) -o main main.o algorithms.o utils.o memory_utils.o
	@echo "Compilation complete"

clean: 
	rm -rf *.o
	rm -rf ./main
	
