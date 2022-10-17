#include "Banque.h"
#include <thread>
#include <mutex>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <iostream>

using namespace std;

const int SOLDEINITIAL = 10000;
const int NB_THREAD = 20;
const int NB_COMPTES = 80;
const int TEST_Q8 = 500;
bool run_cpt = true;


void f1(pr::Banque &b) {
	for(int x = 0; x < TEST_Q8; x++) { // 8)
		size_t i, j;
		unsigned int m;
		i = rand() % b.size();
		j = rand() % b.size();
		while(i == j) {
			j = rand() % (b.size());
		}
		m = 1 + rand() % 101;
		b.transfert(i, j, m);

		//std::cout << "dort " << std::this_thread::get_id() << std::endl;
		//std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 21));
		//std::cout << "reveil" << std::endl;
	}
}

void f8(pr::Banque &b) {
	while(run_cpt) {
		b.comptabiliser(NB_COMPTES * SOLDEINITIAL);
		this_thread::sleep_for(std::chrono::milliseconds(5));
	}

}

int main () {
	vector<thread> threads;
	::srand(::time(nullptr));
	pr::Banque b(NB_COMPTES, SOLDEINITIAL);
	// TODO : creer des threads qui font ce qui est demandé
	for(int i = 0; i < NB_THREAD; i++) {
		threads.emplace_back(f1, std::ref(b));
	}

	//thread comptable
	thread cpt(f8, std::ref(b));

	for (auto & t : threads) {
		t.join();
	}

	run_cpt = false;
	cpt.join();

	// TODO : tester solde = NB_THREAD * JP
	return 0;
}
