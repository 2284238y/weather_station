#ifndef PROCESS_DATA_H
#define PROCESS_DATA_H

#include <string>
#include "threads.h"

class ProcessData : public Threads {
 public:
	ProcessData(std::string a);
	~ProcessData();
	void run() override;
 private:
	std::string todo;
	static double buff_hum[100];
	static double buff_temp[100];
	static double buff_pres[100];
	static double ave_hum;
	static double ave_temp;
	static double ave_pres;
	static std::string message;
	static std::string hum_weather;
	static std::string temp_weather;
	static std::string pres_weather;
    double sum_temp = 0, sum_pres = 0, sum_hum = 0;
	int n_tph = 1;
	int n_ring = 0;
	void Get();
	void Process();
	void Write();
};

#endif //PROCESS_DATA_H
