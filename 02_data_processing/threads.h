#ifndef THREADS_H
#define THREADS_H

class Threads{
    public:
        Threads();
        virtual ~Threads();
        void create();
        virtual void run();
        void join();
    private:
        static void* exec(void* object);
        pthread_t id;
};

#endif // THREADS_H
