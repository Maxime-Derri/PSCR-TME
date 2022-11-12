#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <thread>
#include <chrono>

#include "sig_battle.hpp"

int vie_tmp; //mauvaise implementation

void handle_sigint(int sig) {
    --vie_tmp;
    if(!vie_tmp) {
        vie_tmp = -1;
        std::cout << "ouch" << std::endl;
        exit(1);
    }
}


void battle::attaque(pid_t adversaire) {
    //setting handler (and global vie_tmp for passing param...)
    vie_tmp = vie;
    if(signal(SIGINT, handle_sigint) == SIG_ERR) {
        perror("signal");
    }

    //sending SIGINT signal to adversaire
    if(kill(adversaire, SIGINT) < 0) {
        //adversaire is dead
        std::cout << adversaire << " is dead" << std::endl;
        exit(0);
    }
    vie = vie_tmp;
    vie_tmp = -1;

    std::this_thread::sleep_for(std::chrono::seconds(rand() % TIME));
}

void battle::defense() {
    signal(SIGINT, SIG_IGN); //ignoring SIGINT

    std::this_thread::sleep_for(std::chrono::seconds(rand() % TIME));
}

void battle::combat(pid_t adversaire) {
    while(1) {
        std::cout << getpid() << ": loop" << std::endl;
        defense();
        attaque(adversaire);
    }
}
