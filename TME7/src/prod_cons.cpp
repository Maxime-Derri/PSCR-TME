#include "Stack.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <sys/mman.h>


using namespace std;
using namespace pr;

void producteur (Stack<char> * stack) {
	char c ;
	while (cin.get(c)) {
		stack->push(c);
		cout << c << " ===>" << std::endl;
	}
}

void consomateur (Stack<char> * stack) {
	while (true) {
		char c = stack->pop();
		cout << "<=== " << c << std::endl;//flush ;
	}
}

int main () {
	Stack<char> * s; // = new Stack<char>(); //sm contient les sem
	//emplace_new
	//var->~c()
	//sem nommé: standard et anonyme: non standard
	void *addr = mmap(nullptr, sizeof(Stack<char>), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
	s = new (addr) Stack<char>();

	//int fd = shm_ope, ("/myshm", O_RDWR | O_CREAT | O_EXCL, 0600) //EXCL => faute si existe deja
	//ftruncate(fd, sizeof(Stack<char/);)
	//addr = mmap(0, siszof(Stack<char>), PROT_READ | PROT_WRITE, fd, O);
	//mmap
	//close(fd)
	//munmap(adddr, sizeof(Stack<chzr>)
	//shm_unlink("/mushm");

	pid_t pp = fork();
	if (pp==0) {
		producteur(s);
		return 0;
	}

	pid_t pc = fork();
	if (pc==0) {
		consomateur(s);
		return 0;
	}

	wait(0);
	wait(0);

	delete s;
	return 0;
}

