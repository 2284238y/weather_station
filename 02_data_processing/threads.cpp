extern "C" {
    #include <pthread.h>
}
#include <iostream>
#include "threads.h"
#include "work.h"

using namespace std;

// Constructors and Destructors
Threads::Threads() {
    m_id = s_num++;
    cout << "Thread " << m_id << " created..." << endl;
}

Threads::~Threads() {}

// Static variables and functions
int Threads::s_num = 0;

void* Threads::exec(void* object) {
    ((Threads *)object)-> run(); //Ask if this is better?
    return 0;
}

// Non-static functions
void Threads::create() {
    int ret;
    if ((ret = pthread_create(&m_id, 0, &Threads::exec, this)) != 0) {
        throw "Failed to create thread)";
    }
}

void Threads::run() {
    if (m_id == 0) {
        cout << "hello1" << endl;
        work_get_data();
    } else if (m_id == 1) {
        cout << "hello2" << endl;
        work_process_data();
    } else if (m_id == 2) {
        cout << "hello3" << endl;
        work_broadcast_data();
    }
}

void Threads::join() {
    pthread_join(m_id, NULL);
}
