#ifndef WORK_H
#define WORK_H

#include <string>
#include "threads.h"

class Work : public Threads {
 public:
	Work(std::string a);
	~Work();
	void run() override;
 private:
	std::string todo;
	static double buff_temp[100];
	static double buff_pres[100];
	static double buff_hum[100];
	static double ave_temp;
	static double ave_pres;
	static double ave_hum;
	static std::string message;
	static std::string current_weather;
	double read_temp_pres[20], read_temp[10], read_pres[10], read_hum[10];
	double sum_temp = 0, sum_pres = 0, sum_hum = 0;
	int n_tph = 10;
	int n_ring = 10;
	void Get();
	void Process();
	void Write();
};

#endif //WORK_H
