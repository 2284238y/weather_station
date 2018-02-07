#include <iostream>
#include <linux/i2c-dev.h>
#include <pthread.h>
#include "cpp_threads.h"

using namespace std;

int CppThreads::num = 0;

CppThreads::CppThreads(){
    id = num++;
    cout << id << endl;
}

void CppThreads::Create(){
    pthread_create(&id, 0, &CppThreads::Exec, this);
}

void* CppThreads::Exec(void* arg){
    ((CppThreads*)arg)->CppThreads::Run();
    return 0;
}

void CppThreads::Run() {
    if (id == 0) {
        int file_i2c;
        unsigned char buffer[60];
        int length = 2;

        char *filename = "/dev/i2c-9";
        if ((file_i2c = open(filename, 0_RDWR)) < 0) {
            printf("Failed to open the i2c bus");
            return;
        }

        int address = ;
        if



    } else if (id == 1){
        cout << "Processing Data" << endl;
    } else if (id == 2){
        cout << "Broadcasting Data" << endl;
    } else if (id == 3){
        cout << "Updating GUI" << endl;
    }
}

void CppThreads::Join(){
    pthread_join(id, NULL);
}
