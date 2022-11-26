#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>

int main(int argc, char *argv[]) {
    int pfd[2];
    int found = 0;
    char *path2 = NULL;

    if(argc < 4) {
        std::cout << "not enought param" << std::endl;
        return EXIT_FAILURE;
    }
    
    if(pipe(pfd) < 0) {
        perror("pipe");
        return EXIT_FAILURE;
    }

    if(argv[1][0] == '\|' || argv[argc-1][0] == '\|') {
        std::cerr << "err, pipe at the begin or at the end" << std::endl;
        return EXIT_FAILURE;
    }

    //solution dangereuse: pourrait sensible aux shellcode
    //on peut utiliser -D_FORTIFY_SOURCE=2 -O1
    for(int i = 1; i < argc; i++) {
        if(argv[i][0] == '\|') {
            found = i+1; //idx
            path2 = argv[found];
            argv[i] = NULL;
            break;
        }
    }
    
    switch(fork()) {
        case -1:
            perror("fork");
            return EXIT_FAILURE;

        case 0: //child - second com
            dup2(pfd[0], STDIN_FILENO);
            close(pfd[1]);
            if(execv(path2, argv+found) < 0) {
                perror("execv 2");
                return EXIT_FAILURE;
            }

        default:
            switch(fork()) {
                case -1:
                    perror("fork");
                    return EXIT_FAILURE;
                
                case 0: //child - first com
                    dup2(pfd[1], STDOUT_FILENO);
                    close(pfd[0]);
                    if(execv(argv[1], argv+1) < 0) {
                       perror("execv 1");
                       return EXIT_FAILURE;
                    }

                default:
                    return EXIT_SUCCESS;
            }
    }
    wait(NULL);
    wait(NULL);

    return EXIT_SUCCESS;
}