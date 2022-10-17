#include "Compte.h"

using namespace std;

namespace pr {
void Compte::crediter (unsigned int val) {
	//unique_lock<mutex> g(m);  6)
	m.lock();
	solde+=val ;
	m.unlock();
}

bool Compte::debiter (unsigned int val) {
	//unique_lock<mutex> g(m);  6)
	m.lock();
	bool doit = solde >= val;
	if (doit) {
		solde-=val ;
	}
	m.unlock();
	return doit;
}

int Compte::getSolde() const  {
	//unique_lock<mutex> g(m);  6)
	unique_lock<std::recursive_mutex> g(m);
	//m.lock();
	return solde;
	//m.unlock();
}

// NB : vector exige Copyable, mais mutex ne l'est pas...
Compte::Compte(const Compte & other) {
	other.m.lock();
	solde = other.solde;
	other.m.unlock();
}


std::recursive_mutex &Compte::getMutex() {
	return m;
}

}
