#include <iostream>
//#include <linux/i2c-dev.h>
#include "cpp_threads.h"

using namespace std;

int main(){
    CppThreads getData;
    CppThreads processData;
    CppThreads broadcastData;
    CppThreads updateGui;

    getData.Create();

    return 0;
}