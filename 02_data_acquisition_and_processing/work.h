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
	static double ave_temp;
	double read_temp[10];
	double size;
	double sum;
	int n_tph = 0;
	int n_graph = 0;
	std::string message = "Hello";
	std::string current_weather = "Happy Face";
	void Get();
	void Process();
	void Write();
};

#endif //WORK_H
