#pragma once

#include <stdexcept>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <atomic>

namespace pr {

class Semaphore {
	int compteur;
	std::mutex m; //chaque thread passe un par un dans le test
	std::mutex m_cv; //pour differencier le blocage while et cv
	std::condition_variable_any cv;
public :
	Semaphore(int initial): compteur(initial) {}

	void acquire(int qte) {
		if(qte <= 0)
			throw std::invalid_argument("qte may be at least 1. Or more.");

		while(1) {
			m.lock();
			if(qte > compteur) {
				m.unlock();
				cv.wait(m_cv);
				continue;
			}
			compteur -= qte;
			m.unlock();
			break;
		}
	}

	void release(int qte) {
		std::unique_lock<std::mutex> l(m);
		compteur += qte;
		cv.notify_all();
	}
};

}
