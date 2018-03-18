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

double Work::buff_temp[100] = {};
double Work::buff_pres[100] = {};
double Work::buff_hum[100] = {};
double Work::ave_temp = 0;
double Work::ave_pres = 0;
double Work::ave_hum = 0;
std::string Work::message = "Default";
std::string Work::current_weather = "Default";
int Work::flag_get = 0;
int Work::flag_process = 0;

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
	char buf[4];
	int file;
		
	if((file = open("/dev/i2c-1", O_RDWR))< 0 ) {
	    std::cout << "cannot open bus" << std::endl;
	};
	
	while (1) {
		if (ioctl(file,I2C_SLAVE,0x27)<0) {
			std::cout << "cannot access address" << std::endl;
		};
		
		if(read(file,buf,4) != 4) {
			std::cout << "Failure reading data" << std::endl;
		}

        int read_temp = (buf[2] << 6) | (buf[3] >> 2);
		double temperature = read_temp / 16382.0 * 165.0 - 40;
		
		int read_hum = (buf[0] << 10) | (buf[1] << 2);
		read_hum = read_hum >> 2;
		double humidity = read_hum / 16382.0 * 100.0;
	
		buff_temp[n_ring] = temperature;
		buff_hum[n_ring] = humidity;
		
		if (n_ring < 99) {
			n_ring += 1;
		} else if (n_ring == 99) {
			n_ring = 1;
		}

		if (n_tph < 100) {
			n_tph += 1;
		}

		flag_get = 1;

		sleep(1);
	}
}

void Work::Process() {
		while (1) {
			for (int i = 0; i < n_tph; i++) {
				sum_temp += buff_temp[i];
				sum_hum += buff_hum[i];
			}
		  
			ave_temp = sum_temp/n_tph;
			ave_hum = sum_hum/n_tph;

			sum_temp = 0;
			sum_hum = 0;

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

			flag_process = 1;

			sleep(5);
	}
}

void Work::Write() {
		while (1) {
			std::cout << "Temperature is: " << ave_temp << std::endl;
			std::cout << "Humidity is: " << ave_hum << std::endl;

			std::cout << "The current weather is: " << current_weather << std::endl;
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
