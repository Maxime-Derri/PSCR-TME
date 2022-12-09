#include "Semaphore.h"
#include <iostream>
#include <thread>

void pinger(int n, pr::Semaphore &sem1, pr::Semaphore &sem2) {
	for (int i=0; i < n ; i++) {
		sem2.acquire(1);
		std::cout << "ping " << i << std::endl;
		sem1.release(1);
	}
}

void ponger(int n, pr::Semaphore &sem1, pr::Semaphore &sem2) {
	for (int i=0; i < n ; i++) {
		sem1.acquire(1);
		std::cout << "pong " << i << std::endl;
		sem2.release(1);
	}
}

int main2 () {
	// a faire varier si on le souhaite
	pr::Semaphore sem1(0);
	pr::Semaphore sem2(1);
	const int NBITER = 20;

	// TODO : instancier un thread pinger et un thread ponger avec n=NBITER
	std::thread t1(pinger, NBITER, std::ref(sem1), std::ref(sem2));

	// TODO : terminaison et sortie propre
	std::thread t2(ponger, NBITER, std::ref(sem1), std::ref(sem2));
	t1.join();
	t2.join();

	return 0;
}

