extern "C" {
    #include <pthread.h>
}
#include <iostream>
#include "threads.h"


// Constructors and Destructors
Threads::Threads() {}

Threads::~Threads() {}

// Static functions

void* Threads::exec(void* object) {
    ((Threads*)object)-> run();
    return 0;
}

// Non-static functions
void Threads::create() {
  //std::cout << "Creating thread " << id << "..." << std::endl;
    int ret;
    if ((ret = pthread_create(&id,0,&Threads::exec,this) != 0)) {
        throw "Cannot create thread";
    }
}

void Threads::run() {}

void Threads::join() {
    pthread_join(id,0);
    //std::cout << "Thread " << id << " joined" << std::endl;
}
