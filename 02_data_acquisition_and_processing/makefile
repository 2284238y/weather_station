SHELL = /bin/bash

CXX = g++ -std=c++17
CXXFLAGS = -Wall -g -pthread

objects = main.o threads.o work.o

output: $(objects)
	$(CXX) $(CXXFLAGS) main.o threads.o work.o -o output

main.o : threads.h work.h
	$(CXX) $(CXXFLAGS) -c main.cpp

threads.o : threads.h work.h
	$(CXX) $(CXXFLAGS) -c threads.cpp

work.o : work.h
	$(CXX) $(CXXFLAGS) -c work.cpp

.PHONY : clean
clean :
	rm $(objects) output
