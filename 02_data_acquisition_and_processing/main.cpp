#include <cstdlib>
#include <iostream>
#include "process_data.h"

int main() {
    ProcessData read_data("get");
    ProcessData process_data("process");
    ProcessData write_data("write");

    read_data.create();
    process_data.create();
    write_data.create();

    read_data.join();
    process_data.join();
    write_data.join();

}
