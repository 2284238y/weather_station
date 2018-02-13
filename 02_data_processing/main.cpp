extern "C" {
    #include <fcntl.h>
    #include <linux/i2c-dev.h>
    #include <sys/ioctl.h>
    #include <unistd.h>
}
#include <cstdlib>
#include <iostream>
#include "threads.h"

using namespace std;

int main() {
    Threads get_data;
    Threads process_data;
    Threads broadcast_data;
    get_data.create();
    process_data.create();
    broadcast_data.create();
    get_data.join();
    process_data.join();
    broadcast_data.create();


}
