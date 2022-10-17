#include "Banque.h"
#include <thread>
#include <mutex>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <iostream>

using namespace std;

const int SOLDEINITIAL = 10000;
const int NB_THREAD = 10;
const int NB_COMPTES = 2;


void f1(pr::Banque &b) {
	size_t i, j;
	unsigned int m;
	i = rand() % b.size();
	j = rand() % b.size();
	while(i == j) {
		j = rand() % (b.size()-1);
	}
	m = 1 + rand() % 101;
	b.transfert(i, j, m);

	std::cout << "dort " << std::this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 21));
	std::cout << "reveil" << std::endl;
	
}

int main () {
	vector<thread> threads;
	::srand(::time(nullptr));
	pr::Banque b(NB_COMPTES, SOLDEINITIAL);
	// TODO : creer des threads qui font ce qui est demandé
	for(int i = 0; i < NB_THREAD; i++) {
		threads.emplace_back(f1, std::ref(b));
	}


	for (auto & t : threads) {
		t.join();
	}

	// TODO : tester solde = NB_THREAD * JP
	return 0;
}
