#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main () {
	const int N = 3;
	std::cout << "main pid=" << getpid() << std::endl;
	int cpt = 1; //main attend que 1
	for (int i=1, j=N; i<=N && j==N && fork()==0 ; i++ ) { //processus deja existant s'arretent et font un fils chacun
		cpt = 0;
		std::cout << " i:j " << i << ":" << j << std::endl;
		for (int k=1; k<=i && j==N ; k++) {
			pid_t p = fork();
			if ( p == 0) {
				cpt = 0;
				j=0;
				std::cout << " k:j " << k << ":" << j << std::endl;
			}
			else if(p > 0) {
				cpt++;
			}
			else {
				perror("fork");
				exit(1);
			}
		}//continue ici
	}

	//2)
	//std::cout << getpid() << " -> " << getppid() << std::endl;
	while(cpt > 0) {
		if(wait(NULL) < 0) { //chaque processus possède au plus un fils (à cause de la condition du fork dans le for)
			perror("wait");
			return EXIT_FAILURE;
		}
		cpt--;
	}

	return EXIT_SUCCESS;
}

//1)
//creer 11 processus