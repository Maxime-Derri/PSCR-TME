#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

bool is_child = false;


//avec wait (non waitpid)
int wait_till_pid1(pid_t pid) {
    int status;
    pid_t tmp;
    while(1) {
        tmp = wait(&status);

        if(tmp == -1) //err
            return -1;
        
        if(tmp == pid && WIFEXITED(status))
            return pid;

    }
}

int wait_till_pid2(pid_t pid, int sec) { //pas a faire ~ en rab
    int status;
    pid_t tmp;
    while(sec >= 0) {
        tmp = waitpid(pid, &status, WNOHANG); //ne pas bloquer pour sleep()
        if(tmp == -1)
            return -1;
        
        if(tmp == pid && WIFEXITED(status))
            return pid;

        if(sec > 0)
            sleep(1);
        --sec;
    }
    return 0;
}

void handler_alrm(int sig) {
    std::cout << "handler: fin tempo" << std::endl;
    is_child = false;
}

void handler_chd(int sig) {
    //rien: provoquer la reception du signal (non ignoré)
    std::cout << "handler: child" << std::endl;
    is_child = true;
}

//utiliser alarm(), signal et les masques de signaux
int wait_till_pid3(pid_t pid, int sec) { //pb
    sigset_t old;
    sigset_t sig;
    sigfillset(&sig);

    sigprocmask(SIG_SETMASK, &sig, &old);

    sigdelset(&sig, SIGALRM);
    sigdelset(&sig, SIGCHLD);
    signal(SIGALRM, handler_alrm);
    signal(SIGCHLD, handler_chd);
    alarm(sec);
    sigsuspend(&sig); //on peut avoir recu sigchild, et entre sigsuspend et sigpending sigalrm ? SIGPROCMASK regle le probleme (le mask est modifié seulement en sigsuspend et avant/apres tt est masqué)?
                      //sigsuspend: handler déclanché mais signaux pas reset ? seul solution: var global ? cafr sigsuspend retire du mask les 2 signaux -> traitement retour mode U
                      //=> provoque les erreurs lignes qui suivent ?

    sigset_t rec;
    sigpending(&rec);
    if(is_child) {
        alarm(0);
        signal(SIGALRM, SIG_DFL);
        sigprocmask(SIG_SETMASK, &old, nullptr);
        return pid;
    }
    else {
        signal(SIGCHLD, SIG_DFL);
        sigprocmask(SIG_SETMASK, &old, nullptr);
        return 0;
    }
    /*
    int test = sigismember(&rec, SIGCHLD);
    if(test == -1) {
        perror("sigpending / sigismember");
        return -1;
    }
    else if(test) { //child
        alarm(0);
        signal(SIGALRM, SIG_DFL); //tj exec... utlisier une var global depuis les handers ?
        return pid;
    }
    else {
        signal(SIGCHLD, SIG_DFL);
        return 0;
    }
    */

}

int main(int argc, char **argv) {
    pid_t child = fork();
    switch (child) {
    case -1:
        perror("fork");
        return EXIT_FAILURE;
    
    case 0: //child
        sleep(3);
        exit(0);
    
    default:
        pid_t res;
        //res = wait_till_pid1(child);
        //res = wait_till_pid2(child, 4);
        res = wait_till_pid3(child, 3);
        if(res == -1) {
            std::cout << "pas bien" << std::endl;
            return EXIT_FAILURE;
        }
        else if(res == 0) {
            std::cout << "temps ecoulé" << std::endl;
        }
        else {
            std::cout << "bien" << std::endl;
            return EXIT_SUCCESS;
        }
    }


    return 0;
}