#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include <sys/mman.h>
#include <sys/wait.h>

#include "promise.h"

#define N 10
//idée:
//un objet future/promise qui propose un get_result, bloquant tant que le resultat n'est pas disponible

int main(int argc, char *argv[]) {
    promise<int> *v;
    void *addr = mmap(NULL, sizeof(v), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
     v = new (addr) promise<int>();

    switch (fork()) { //1
        case -1:
            perror("fork 1");
            return EXIT_FAILURE;

        case 0: {
            for(int i = 0; i < N; ++i) {
                std:: cout << "GET - " << v->get_result() << std::endl;
            }
            exit(EXIT_SUCCESS);
        }
        
        default:
            break;
        }


    switch (fork()) { //2
        case -1:
            perror("fork 1");
            return EXIT_FAILURE;

        case 0: {
            int tmp;
            
            for(int i = 0; i < N; ++i) {
                tmp = i;
                v->set_result(&tmp);
                std::cout << "SET - " << tmp << std::endl;
                sleep(1);
            }
            exit(EXIT_SUCCESS);
        }

        default:
            break;
    }

    wait(0);
    wait(0);
    return 0;
}