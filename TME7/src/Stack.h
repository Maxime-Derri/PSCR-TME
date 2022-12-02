#pragma once

#include <cstring> // size_t,memset
#include <condition_variable>
#include <mutex>
#include <semaphore.h>
#include <iostream>


/*
Ecrivez progressivement une version avec N pro ducteurs et M consommateurs, qui
utilise un segment de mémoire partagée nommé, et se termine proprement sur Ctrl-C
*/

//mem partagé => on stock pas de ptr
namespace pr {

#define STACKSIZE 100

/*
struct sem {
	sem_t vide;
	sem_t full;
	sem_t sync;
};
*/

template<typename T>
class Stack {
	T tab [STACKSIZE]; //size: sizeof(T) * STACKSIZE (on a STACKSIZE case T)
	size_t sz;
	sem_t vide;
	sem_t full;
	sem_t sync;
	//sem lock;
public :
	Stack () : sz(0) {
		memset(tab,0,sizeof tab) ;
		if(sem_init(&vide, 1, STACKSIZE) < 0) {
			perror("sem_init");
			exit(1);
		}

		if(sem_init(&full, 1, 0) < 0) {
			perror("sem_init");
			exit(1);
		}

		if(sem_init(&sync, 1, 1)) {
			perror("sem_init");
			exit(1);
		}
	}

	T pop () {
		// bloquer si vide
		sem_wait(&full);

		sem_wait(&sync);
		T toret = tab[--sz];
		sem_post(&sync);

		sem_post(&vide);
		return toret;
	}

	void push(T elt) {
		//bloquer si plein
		sem_wait(&vide);

		sem_wait(&sync);
		tab[sz++] = elt;
		sem_post(&sync);

		sem_post(&full);
	}

	~Stack() {
		sem_destroy(&full);
		sem_destroy(&sync);
		sem_destroy(&vide);
	}
};

}
