#include <iostream>
#include <semaphore.h>


template<typename T>
class promise {
    private:
        sem_t lock_get;
        sem_t lock_set;
        T result;

    public:
        promise() {
            if(sem_init(&lock_get, 1, 0) < 0) {
                perror("sem_init");
                exit(1);
            }

            if(sem_init(&lock_set, 1, 1) < 0) {
                perror("sem_init");
                exit(1);
            }
            result = nullptr;
        }

        ~promise() {
            sem_destroy(&lock_get);
            sem_destroy(&lock_set);
        }

        T *get_result() {
            sem_wait(&lock_get); // initial = 0
            sem_post(&lock_set); //1 sem
            return &result;
        }

        void set_result(T *e) {
            sem_wait(&lock_set);
            result = e;
            sem_post(&lock_get);
        }

};