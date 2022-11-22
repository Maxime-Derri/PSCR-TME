#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <thread>
#include <chrono>
#include <errno.h>

#include "rsleep.h"

//#include "sig_battle.hpp" -> mauvaise implementation de base a causes de l'attribue vie / handler

#define TIME 2

int vie = 3;

void handler_sigint(int sig) {
    --vie;
    if(!vie) {
        std::cout << getpid() << " bobo" << std::endl;
        exit(1);
    }
}

void handler_luke(int sig) {
    std::cout << "coup bloqué" << std::endl;
}


void attaque(pid_t adversaire) {
    //preparer le handler
    if(signal(SIGINT, handler_sigint) == SIG_ERR) {
        perror("signal | perdu");
        exit(0);
    }

    //envoyer SIGINT a adversaire
    if(kill(adversaire, SIGINT) < 0) {
        //adversaire dead
        std::cout << adversaire << " is dead" << std::endl;

        exit(0);
    }

    //std::this_thread::sleep_for(std::chrono::seconds(rand() % TIME));
    randsleep();
}

void defense(pid_t my_pid) {
    sigset_t old;
    if(my_pid)
        signal(SIGINT, SIG_IGN); //ignorer SIGINT
    else {
        struct sigaction act;
        sigset_t sig;
        
        //sigaction
        sigemptyset(&sig);
        act.sa_flags = 0;
        act.sa_mask = sig;
        act.sa_handler = handler_luke;
        sigaction(SIGINT, &act, NULL);

        //sigprocmask
        sigfillset(&sig);
        sigprocmask(SIG_SETMASK, &sig, &old);

    }

    //std::this_thread::sleep_for(std::chrono::seconds(rand() % TIME));
    randsleep();

    if(!my_pid) {
        sigset_t sig;
        sigfillset(&sig);
        sigdelset(&sig, SIGINT);
        sigsuspend(&sig);

        //old mask
        sigprocmask(SIG_SETMASK, &old, NULL);
    }
}

void combat(pid_t adversaire, pid_t my_pid) {
    while(1) {
        //std::cout << getpid() << ": loop" << std::endl;
        defense(my_pid);
        attaque(adversaire);
    }
}



//------

int main(int argc, char **argv) {
    srand(time(NULL)); //seed pour rand()
    pid_t child;
    child = fork();
    switch (child) {
        case -1:
            perror("fork");
            break;

        case 0: //child -> luke
            srand(time(NULL)); //nouveau seed
            combat(getppid(), child);
            break;

        default:
            combat(child, getpid());
            break;
    }




    return 0; //jamais atteint ?
}

//Q4
//nanosleep interrompt le bloquage si le temps et ecoulé / signal recu / fin processus
//la boucle bloque le processus malgré les signaux reçu en relancant un appel tant que le reste (à dormir) n'est pas nul

//Q5
//srand(time(NULL)) dans chaque processus ?

//Q6
//Non il n'est plus equitable, car sigsuspend attend de recevoir un signal avant de reprendre et execute donc le handler associé (coup bloqué). Donc quand Luke
//passe en defense, il est assuré de parer au moins un coup (il peut toujours en prendre un si les deux processus sont en mode attaque)