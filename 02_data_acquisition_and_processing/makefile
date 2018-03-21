SHELL = /bin/bash

CXX = g++ -std=c++17
CXXFLAGS = -Wall -g -pthread

objects = main.o threads.o process_data.o

output: $(objects)
	$(CXX) $(CXXFLAGS) $(objects) -o output

main.o : threads.h process_data.h
	$(CXX) $(CXXFLAGS) -c main.cpp

threads.o : threads.h process_data.h
	$(CXX) $(CXXFLAGS) -c threads.cpp

process_data.o : process_data.h
	$(CXX) $(CXXFLAGS) -c process_data.cpp

.PHONY : clean
clean :
	rm $(objects) output
