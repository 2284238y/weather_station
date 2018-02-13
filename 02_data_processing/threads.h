#ifndef THREADS_H
#define THREADS_H

#include "work.h"

class Threads{
    public:
        Threads();
        virtual ~Threads();
        static void* exec(void* object);
        void create();
        void run();
        void join();
    private:
        static int s_num;
        pthread_t m_id;
};

#endif // THREADS_H
