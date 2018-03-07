#include <iostream>
#include <string>

#include <cstdlib>
#include <ctime>
#include <string>

#include "work.h"

double Work::buff_temp[100] = {};
double Work::ave_temp = 0;

Work::Work(std::string task) : todo(task) {}

Work::~Work() {}

void Work::run() {
    if (todo == "get") {
      std::cout << "Getting data..." << std::endl;
      Work::Get();
    } else if (todo == "process") {
      std::cout << "Processing data..." << std::endl;
      Work::Process();
    } else if (todo == "write") {
      std::cout << "Writing data..." << std::endl;
      Work::Write();
    }
}

void Work::Get() {
	/*
        // get p-t values
        int bytes = 20;
        int file = open("/dev/i2c-?",O_RDWR);
        if (file<0) {
            throw "Cannot open i2c bus";
        };
        int address = ?;
        if (ioctl(file,I2C_SLAVE,address)<0) {
            throw "Cannot access address";
        };
        read(file,read_temp_pres,bytes);
	// split into two arrays
        std::cout << read_temp << std::endl;
	std::cout << read_pres << std::endl;
    
        // get h values
        int bytes = 10;
        int file = open("/dev/i2c-?",O_RDWR);
        if (file<0) {
            throw "Cannot open i2c bus";
        };
        int address = ?;
        if (ioctl(file,I2C_SLAVE,address)<0) {
            throw "Cannot access address";
        /};
        read(file,read_hum,bytes);
        std::cout << read_hum << stendl;
	*/

	
	
	for (int i = 0; i < 10; i++) {
	  int r_t = rand() % 15;
	  read_temp[i] = r_t;
	 }
	
        // update ring buffers
        for (int i = 0; i < 10; i++) {
	  buff_temp[n_tph+i] = read_temp[i];
	}
	if (n_tph < 100) {
	  n_tph += 10;
	}
	for (int i = 0; i < 10; i++) {
	  std::cout << buff_temp[n_tph] << std::endl;
	}
}

void Work::Process() {
	  // calculate averages
	  for (int i = 0; i < n_tph; i++) {
	    sum += buff_temp[i];
	  }
	  ave_temp = sum/n_tph;

        // calculate current weather
	if (ave_temp > 10) {
	  std::string current_weather =  "Happy Face";
	} else {
	  std::string current_weather =  "Sad Face";
	}

        // calculate message
	 if (current_weather == "Happy Face") {
	   std::string message = "It's good weather, have a great day";
	 } else {
	   std::string message = "It's bad weather, but have a great day anyway";
	 }
}

void Work::Write() {
	  std::cout << "Temperature is: " << ave_temp << std::endl;
	  
	  std::cout << "The current weather is: " << current_weather << std::endl;
	  std::cout << "Message is: " << message << std::endl;
}
