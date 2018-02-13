SHELL = /bin/bash

CXX = g++ -std=c++17
CXXFLAGS = -Wall -g -pthread

objects = main.o threads.o

output: $(objects)
	$(CXX) $(CXXFLAGS) main.o threads.o -o output

main.o : threads.h
	$(CXX) $(CXXFLAGS) -c main.cpp

threads.o : threads.h
	$(CXX) $(CXXFLAGS) -c threads.cpp

.PHONY : clean
clean :
	rm $(objects) output
