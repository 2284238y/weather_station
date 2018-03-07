#include <iostream>
#include <string>

#include <cstdlib>
#include <ctime>
#include <string>

#include "work.h"

double Work::buff_temp[100] = {};
double Work::buff_pres[100] = {};
double Work::buff_hum[100] = {};
double Work::ave_temp = 0;
double Work::ave_pres = 0;
double Work::ave_hum = 0;
std::string Work::message = "Default";
std::string Work::current_weather = "Default";

Work::Work(std::string task) : todo(task) {}

Work::~Work() {}

void Work::run() {
    if (todo == "get") {
		//std::cout << "Getting data..." << std::endl;
		Work::Get();
    } else if (todo == "process") {
		//std::cout << "Processing data..." << std::endl;
		Work::Process();
    } else if (todo == "write") {
		//std::cout << "Writing data..." << std::endl;
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

	
	while (1) {
		for (int i = 0; i < 10; i++) {
			int r = rand() % 15;
			read_temp[i] = r;
			read_pres[i] = 0.8*r;
			read_hum[i] = 0.2*r;
		}
	
        // update ring buffers
        for (int i = n_ring-10; i < n_ring; i++) {
			buff_temp[i] = read_temp[i-(n_ring-10)];
		    buff_pres[i] = read_pres[i-(n_ring-10)];
			buff_hum[i] = read_hum[i-(n_ring-10)];
		}
		
		if (n_ring <= 90) {
			n_ring += 10;
		} else if (n_ring == 100) {
			n_ring = 10;
		}

		if (n_tph <=90) {
			n_tph += 10;
		}
	}
	
}

void Work::Process() {
	// calculate averages
	while (1) {
		for (int i = 0; i < n_tph; i++) {
			sum_temp += buff_temp[i];
			sum_pres += buff_pres[i];
			sum_hum += buff_hum[i];
			
		}
		ave_temp = sum_temp/n_tph;
		ave_pres = sum_pres/n_tph;
		ave_hum = sum_hum/n_tph;

		sum_temp = 0;
		sum_pres = 0;
		sum_hum = 0;

        // calculate current weather
		if (ave_temp > 7) {
			current_weather =  "good";
		} else {
			current_weather =  "bad";
		}

        // calculate message
		if (current_weather == "good") {
			message = "It's good weather, have a great day";
		} else {
			message = "It's bad weather, but have a great day anyway";
		}
	}
}

void Work::Write() {
	while (1) {
		std::cout << "Temperature is: " << ave_temp << std::endl;
		std::cout << "Pressure is: " << ave_pres << std::endl;
		std::cout << "Humidity is: " << ave_hum << std::endl;
	  
		std::cout << "The current weather is: " << current_weather << std::endl;
		std::cout << "Message is: " << message << std::endl;
	}
}
