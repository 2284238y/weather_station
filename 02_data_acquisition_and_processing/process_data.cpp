extern "C" {
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>
}

#include <iostream>
#include <cstring>
#include <cstdlib>

#include "process_data.h"

double ProcessData::buff_hum[100] = {};
double ProcessData::buff_temp[100] = {};
double ProcessData::buff_pres[100] = {};
double ProcessData::ave_hum = 0;
double ProcessData::ave_temp = 0;
double ProcessData::ave_pres = 0;
std::string ProcessData::message = "Default";
std::string ProcessData::hum_weather = "Default";
std::string ProcessData::temp_weather = "Default";
std::string ProcessData::pres_weather = "Default";

ProcessData::ProcessData(std::string task) : todo(task) {}

ProcessData::~ProcessData() {}

void ProcessData::run() {
    if (todo == "get") {
		ProcessData::Get();
    } else if (todo == "process") {
		ProcessData::Process();
    } else if (todo == "write") {
		ProcessData::Write();
    }
}

//*  This method reads data from the i2c buffer
void ProcessData::Get() {
	//*  Initialise sensor read buffers and i2c file
	uint8_t buf1[4];
	uint8_t buf2[4];
	int file;

	//*  Open the i2c bus
	if((file = open("/dev/i2c-1", O_RDWR))< 0 ) {
	    std::cout << "cannot open bus" << std::endl;
	};
	

	//* Start infinite Loop
	while (1) {
		//*  Open the temp/hum i2c sensor address
		if (ioctl(file,I2C_SLAVE,0x27)<0) {
			std::cout << "cannot access humidity/temperature sensor address" << std::endl;
		}
		  
		//*  Read four bytes into temp/hum sensor buffer
		if(read(file,buf1,4) != 4) {
			std::cout << "Failure reading humidity/temperature data" << std::endl;
		}
		  
		//*  Bit manipulation and convert to values 
		double read_hum = (buf1[0] << 8) | buf1[1];
		double humidity = read_hum / 16382.0 * 100.0;

		double read_temp = (buf1[2] << 6) | (buf1[3] >> 2);
		double temperature = read_temp / 16382.0 * 165.0 - 40;    
		  
		//*  Add values to ring buffers
		buff_hum[n_ring] = humidity;
		buff_temp[n_ring] = temperature;

		
		//*  This sections reapeats the above for the pressure sensor
		if (ioctl(file,I2C_SLAVE,0x60)<0) {
			std::cout << "cannot access pressure sensor address" << std::endl;
		}
		
		if(read(file,buf2,4) != 4) {
			std::cout << "Problem reading pressure data" << std::endl;
		}
		  
		double read_pres = (buf2[1] << 16) | (buf2[2] << 8) | buf2[3];
		double pressure = read_pres/6400;

		buff_pres[n_ring] = pressure;

		
		//*  update ring buffer index being written to
		if (n_ring < 99) {
			n_ring += 1;
		} else if (n_ring == 99) {
			n_ring = 1;
		}

		//*  Update the size of the ring buffer (for averaging calculations)
		if (n_tph < 100) {
			n_tph += 1;
		}

		//*  Wait 1s until next read
		sleep(1);
	}
}

//* This method proceses the data
void ProcessData::Process() {
	while (1) {
		//*  sum up the values in the buffers
		for (int i = 0; i < n_tph; i++) {
			sum_hum += buff_hum[i];
			sum_temp += buff_temp[i];
			sum_pres += buff_pres[i];
		}

		//* Average the buffers to get an n_tph-point average
		ave_hum = sum_hum/n_tph;
		ave_temp = sum_temp/n_tph;
		ave_pres = sum_pres/n_tph;

		//*  Reset the sumations to zero
		sum_hum = 0;
		sum_temp = 0;
		sum_pres = 0;

		//*  Identify what the weather is like
		if (ave_hum > 60) {
			hum_weather = "Uncomfortably Wet";
		} else if ((ave_hum > 25) && (ave_hum <= 60)) {
			hum_weather = "Comfortable";
		} else if (ave_hum <= 25) {
			hum_weather = "Uncomfortable Dry";
		}

		if (ave_temp > 20) {
			temp_weather = "Hot";
		} else if ((ave_temp > 10) && (ave_temp <= 20)) {
			temp_weather = "Warm";
		} else if ((ave_temp > 0) && (ave_temp <= 10)) {
			temp_weather = "Cold";
		} else if (ave_temp <= 0) {
			temp_weather = "Very Cold";
		}

        if (ave_pres > 1030) {
			pres_weather = "Very Dry";
		} else if ((ave_pres > 1010) && (ave_pres <= 1030)) {
			pres_weather = "Fair";
		} else if ((ave_pres > 990) && (ave_pres <= 1010)) {
			pres_weather = "Change";
		} else if ((ave_pres > 970) && (ave_pres <= 990)) {
			pres_weather = "Rain";
		} else if (ave_pres <= 970) {
			pres_weather = "Stormy";
		}



		//*  Calculate a message based on the weather		
		if (temp_weather == "Hot") {
			message = "It's good weather, have a great day";
		} else {
			message = "It's bad weather, but have a great day anyway";
		}

		//* wait 5s until next calculation
		sleep(5);
	}
}

//*  This method writes the data to the database
void ProcessData::Write() {
	while (1) {
		std::cout << "Humidity: " << ave_hum <<  "%" << std::endl;
		std::cout << "Temperature: " << ave_temp << " degrees C" << std::endl;
		std::cout << "Pressure: " << ave_pres << " milibar" << std::endl;

		std::cout << "Current weather : " << temp_weather << std::endl;
		std::cout << message << std::endl;

		sleep(5);
	}
}
