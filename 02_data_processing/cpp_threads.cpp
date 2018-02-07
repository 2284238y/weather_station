#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <pthread.h>
#include "cpp_threads.h"

// using namespace std;
//
// int CppThreads::num = 0;
//
// CppThreads::CppThreads(){
//     id = num++;
//     cout << id << endl;
// }
//
// void CppThreads::Create(){
//     pthread_create(&id, 0, &CppThreads::Exec, this);
// }
//
// void* CppThreads::Exec(void* arg){
//     ((CppThreads*)arg)->CppThreads::Run();
//     return 0;
// }
//
// void CppThreads::Run() {
//
// void CppThreads::Join(){
//     pthread_join(id, NULL);
// }
