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
    promise<std::vector<std::string>> *v;
    void *addr = mmap(NULL, sizeof(v), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
     v = new (addr) promise<std::vector<std::string>>();

    switch (fork()) { //1
        case -1:
            perror("fork 1");
            return EXIT_FAILURE;

        case 0: {
            std::vector<std::string> *tmp;

            for(int i = 0; i < N; ++i) {
                tmp = v->get_result();
                std:: cout << "GET - " << std::endl;
                for(auto &e : *tmp) {
                    std::cout << e << " ";;
                }
                std::cout << std::endl;
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
            std::vector<std::string> tmp;
            tmp = std::vector<std::string>() ;
            
            for(int i = 0; i < N; ++i) {
                tmp.push_back("a");
                v->set_result(&tmp);
                std::cout << "SET - " << std::endl;
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