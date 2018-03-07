extern "C" {
    #include <fcntl.h>
    #include <linux/i2c-dev.h>
    #include <sys/ioctl.h>
    #include <unistd.h>
}
#include <cstdlib>
#include <iostream>
#include <string>
#include "work.h"

int main() {
    Work get_data("get");
    Work process_data("process");
    Work broadcast_data("write");

    get_data.create();
    process_data.create();
    broadcast_data.create();

    get_data.join();
    process_data.join();
    broadcast_data.join();

}
