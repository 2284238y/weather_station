#ifndef CPP_THREADS_H
#define CPP_THREADS_H

class CppThreads{
    public:
        CppThreads();
        virtual ~CppThreads(){};
        void Create();
        static void* Exec(void* arg);
        void Run();
        void Join();
    private:
        static int num;
        pthread_t id;
};

#endif // CPP_THREADS_H
