//FAUTE, il manque l'include
#include "List.h"
namespace pr {

// ******************* Chainon
Chainon::Chainon (const std::string & data, Chainon * next):data(data),next(next) {};

//FAUTE, len n'est jamais retourné, mais à la place la fonction length() est encore appelé: boucle
size_t Chainon::length() {
	size_t len = 1;
	if (next != nullptr) {
		len += next->length();
	}
	return len;
}

//FAUTE, il manque la déclaration const, comme dans le prototype du .h
//FAUTE, next->print(os) était appelé tout le temps, le if n'arrete pas les appels récursifs
//compte comme 1 seul faute ?
void Chainon::print (std::ostream & os) const {
	os << data ;
	if (next != nullptr) {
		os << ", ";
		next->print(os);
	}
	return;
}

// ******************  List
const std::string & List::operator[] (size_t index) const  {
	Chainon * it = tete;
	for (size_t i=0; i < index ; i++) {
		it = it->next;
	}
	return it->data;
}

void List::push_back (const std::string& val) {
	if (tete == nullptr) {
		tete = new Chainon(val);
	} else {
		Chainon * fin = tete;
		while (fin->next) {
			fin = fin->next;
		}
		fin->next = new Chainon(val);
	}
}

void List::push_front (const std::string& val) {
	tete = new Chainon(val,tete);
}

//FAUTE, il manque List:: comme empty en est une fonction de cette classe
bool List::empty() {
	return tete == nullptr;
}

size_t List::size() const {
	if (tete == nullptr) {
		return 0;
	} else {
		return tete->length();
	}
}

//FAUTE, la redéfinition de l'opérateur pour les List est censé être dans l'espace de nom 'pr'
std::ostream & operator<< (std::ostream & os, const pr::List & vec)
{
	os << "[";
	if (vec.tete != nullptr) {
		vec.tete->print (os) ;
	}
	os << "]";
	return os;
}

} // namespace pr


