extern "C" {
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>
}

#include <iostream>
#include <cstring>
#include <cstdlib>

#include "work.h"

double Work::buff_hum[100] = {};
double Work::buff_temp[100] = {};
double Work::buff_pres[100] = {};
double Work::ave_hum = 0;
double Work::ave_temp = 0;
double Work::ave_pres = 0;
std::string Work::message = "Default";
std::string Work::current_weather = "Default";

Work::Work(std::string task) : todo(task) {}

Work::~Work() {}

void Work::run() {
    if (todo == "get") {
		Work::Get();
    } else if (todo == "process") {
		Work::Process();
    } else if (todo == "write") {
		Work::Write();
    }
}

void Work::Get() {
	uint8_t buf1[4];
	uint8_t buf2[6];
	int file;
		
	if((file = open("/dev/i2c-1", O_RDWR))< 0 ) {
	    std::cout << "cannot open bus" << std::endl;
	};
	
	while (1) {
		if (ioctl(file,I2C_SLAVE,0x27)<0) {
			std::cout << "cannot access humidity/temperature sensor address" << std::endl;
		};
		
		if(read(file,buf1,4) != 4) {
			std::cout << "Failure reading humidity/temperature data" << std::endl;
		}

		double read_hum = (buf1[0] << 8) | buf1[1];
		double humidity = read_hum / 16382.0 * 100.0;

        double read_temp = (buf1[2] << 6) | (buf1[3] >> 2);
		double temperature = read_temp / 16382.0 * 165.0 - 40;    
	
		buff_hum[n_ring] = humidity;
		buff_temp[n_ring] = temperature;

	    if (ioctl(file,I2C_SLAVE,0x60)<0) {
			std::cout << "cannot access pressure sensor address" << std::endl;
		}
		
		if(read(file,buf2,6) != 6) {
			std::cout << "Problem reading pressure data" << std::endl;
		}

	    double read_pres = (buf2[1] << 16) | (buf2[2] << 8) | buf2[3];
		double pressure = read_pres/6400000;

		buff_pres[n_ring] = pressure;
		
		if (n_ring < 99) {
			n_ring += 1;
		} else if (n_ring == 99) {
			n_ring = 1;
		}

		if (n_tph < 100) {
			n_tph += 1;
		}

		sleep(1);
	}
}

void Work::Process() {
		while (1) {
			for (int i = 0; i < n_tph; i++) {
				sum_hum += buff_hum[i];
				sum_temp += buff_temp[i];
				sum_pres += buff_pres[i];
			}
		  
			ave_hum = sum_hum/n_tph;
			ave_temp = sum_temp/n_tph;
			ave_pres = sum_pres/n_tph;

			sum_hum = 0;
			sum_temp = 0;
			sum_pres = 0;

			if (ave_temp > 10) {
				current_weather = "good";
			} else {
				current_weather = "bad";
			}
		
			if (current_weather == "good") {
				message = "It's good weather, have a great day";
			} else {
				message = "It's bad weather, but have a great day anyway";
			}

			sleep(5);
	}
}

void Work::Write() {
		while (1) {
			std::cout << "Humidity: " << ave_hum <<  "%" << std::endl;
			std::cout << "Temperature: " << ave_temp << " degrees C" << std::endl;
			std::cout << "Pressure: " << ave_pres << " bar" << std::endl;

			std::cout << "Current weather : " << current_weather << std::endl;
			std::cout << message << std::endl;

			sleep(5);

			/*
			  Outputs are:
			  ave_temp (Single value)
			  ave_hum (single value)
			  ave_pres (single(value)
			  current_weather (probably something like sunny, rainy, hot, stormy. Represented in the web app by icons?)
			  message (General message to be displayed)
			*/
	}
}
