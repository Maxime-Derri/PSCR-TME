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
	//Stack<char> * s;// = new Stack<char>();
	Stack<char> *s =(Stack<char> *)mmap(0, sizeof(Stack<char>), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
	s = new Stack<char>;

	
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
	munmap(s, sizeof(*s));
	return 0;
}

