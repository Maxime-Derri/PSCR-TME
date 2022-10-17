#include "Banque.h"

#include <iostream>

using namespace std;

namespace pr {

void Banque::transfert(size_t deb, size_t cred, unsigned int val) {
	// 4)
	Compte & debiteur = comptes[deb];
	Compte & crediteur = comptes[cred];
	//std::lock(crediteur.getMutex(), debiteur.getMutex()); 6) peut deadlock si i et j essaient de s'accéder l'un l'autre: commutation et sur architecture multi_coeur
	//debiteur.getMutex().lock();
	while(!debiteur.getMutex().try_lock()) {
		std::this_thread::yield();
	}
	crediteur.getMutex().lock();
	if (debiteur.debiter(val)) {
		crediteur.crediter(val);
	}
	debiteur.getMutex().unlock();
	crediteur.getMutex().unlock();
}
size_t Banque::size() const {
	return comptes.size();
}
bool Banque::comptabiliser (int attendu) const {
	int bilan = 0;
	int id = 0;
	for (const auto & compte : comptes) {
		if (compte.getSolde() < 0) {
			cout << "Compte " << id << " en négatif : " << compte.getSolde() << endl;
		}
		bilan += compte.getSolde();
		id++;
	}
	if (bilan != attendu) {
		cout << "Bilan comptable faux : attendu " << attendu << " obtenu : " << bilan << endl;
	}
	return bilan == attendu;
}
}
