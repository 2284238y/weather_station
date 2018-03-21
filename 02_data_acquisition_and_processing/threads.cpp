extern "C" {
    #include <pthread.h>
}
#include <iostream>
#include "threads.h"


Threads::Threads() {}

Threads::~Threads() {}

//*  Create thread
void Threads::create() {
	std::cout << "Creating thread " << id << "..." << std::endl;
    int ret;
    if ((ret = pthread_create(&id,0,&Threads::exec,this) != 0)) {
		std::cout << "Cannot create thread" << std::endl;
    }
}

//*  Intermittent function to cast thread to run method
void* Threads::exec(void* object) {
    ((Threads*)object)-> run();
    return 0;
}

//*  Override this function in your X.cpp script. The work done by the thread goes in that function.
void Threads::run() {}

//*  Joins the threads
void Threads::join() {
    pthread_join(id,0);
    std::cout << "Thread " << id << " joined" << std::endl;
}
