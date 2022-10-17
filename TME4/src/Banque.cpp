#include "Banque.h"

#include <iostream>

static size_t etape_cpt = 0;

using namespace std;

namespace pr {

void Banque::transfert(size_t deb, size_t cred, unsigned int val) {
	//test.lock(); // 6) idée de correction 1*
	// 4)
	Compte & debiteur = comptes[deb];
	Compte & crediteur = comptes[cred];
	//std::lock(crediteur.getMutex(), debiteur.getMutex()); //6) peut deadlock si i et j essaient de s'accéder l'un l'autre: commutation et sur architecture multi_coeur
	
	
	bool c_l; //solution correction 2
	do {
		debiteur.getMutex().lock();
		c_l = crediteur.getMutex().try_lock();
		if(!c_l) {
			debiteur.getMutex().unlock();
			this_thread::yield(); //on laisse un autre thread passer - pas obligé
		}
	} while(!c_l);
	
	if (debiteur.debiter(val)) {
		crediteur.crediter(val);
	}
	
	//std::cout << "transaction" << std::endl;

	debiteur.getMutex().unlock(); // 2*
	crediteur.getMutex().unlock(); //2*
	//test.unlock();   // 1*
}
size_t Banque::size() const {
	return comptes.size();
}

bool Banque::comptabiliser (int attendu) /* const */ {
	// 9) il faut utiliser le mutex test de Banque, et ajouter la verification dans transaction
	int bilan = 0;
	int id = 0;
	for (auto & compte : comptes) {
		/* const */compte.getMutex().lock(); //10)
		if (compte.getSolde() < 0) {
			cout << "Compte " << id << " en négatif : " << compte.getSolde() << endl;
		}
		bilan += compte.getSolde();
		id++;
		//std::cout << " ---------- comptabiliser   " << etape_cpt << "   ----------" << std::endl;
	}

	// 10)
	for(auto & compte : comptes) compte.getMutex().unlock();

	if (bilan != attendu) {
		cout << "Bilan comptable faux : attendu " << attendu << " obtenu : " << bilan << endl;
	}
	
	++etape_cpt;
	return bilan == attendu;
	
}
}
