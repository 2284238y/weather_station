#include <cstdlib>
#include <iostream>
#include "process_data.h"

int main() {
    ProcessData read_data("get");
    ProcessData process_data("process");

    read_data.create();
    process_data.create();

    read_data.join();
    process_data.join();

}
