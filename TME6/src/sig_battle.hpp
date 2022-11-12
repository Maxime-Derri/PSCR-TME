#pragma once
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>

#define TIME 5

class battle {
    private:

    public:
        int vie;
        battle(int v): vie(v) {
            srand(time(NULL)); //setting seed for rand()
        }
        void attaque(pid_t adversaire);
        void defense();
    void combat(pid_t adversaire);

        
};

void handle_sigint(int sig);