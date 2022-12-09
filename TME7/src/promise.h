#include <iostream>
#include <semaphore.h>


template<typename T>
class promise {
    private:
        sem_t lock_get;
        T result;

    public:
        promise() {
            if(sem_init(&lock_get, 1, 0) < 0) {
                perror("sem_init");
                exit(1);
            }

            //result = nullptr;
        }

        ~promise() {
            sem_destroy(&lock_get);
        }

        T get_result() {
            sem_wait(&lock_get); // initial = 0
            return result;
        }

        void set_result(T *e) {
            result = *e;
            sem_post(&lock_get);
        }

};