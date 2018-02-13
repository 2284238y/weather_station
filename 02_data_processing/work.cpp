#include <iostream>
#include "work.h"

using namespace std;

void work_get_data() {
    cout << "Getting data..." << endl;
//     char buffer[5];
//     int bytes = 5;
//     int file = open("/dev/i2c-15",O_RDWR);
//     if (file<0) {
//         throw "Cannot open i2c bus";
//     };
//     int address = 0x58;
//     if (ioctl(file,I2C_SLAVE,address)<0) {
//         throw "Cannot access address";
//     };
//     read(file,buffer,bytes);
//     cout << buffer << endl;
}

void work_process_data() {
    cout << "Processing data..." << endl;
}

void work_broadcast_data() {
    cout << "Broadcasting data..." << endl;
}
