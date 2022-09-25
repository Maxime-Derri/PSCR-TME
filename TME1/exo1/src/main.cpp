#include "List.h"
#include <string>
#include <iostream>
#include <cstring>

int main () {

	std::string abc = "abc";
	char * str = new char [3];
	str[0] = 'a';
	str[1] = 'b';
	str[2] = 'c';
	size_t i = 0;

	if (! strcmp (str, abc.c_str())) {
		std::cout << "Equal !";
	}

	pr::List list;
	list.push_front(abc);
	list.push_front(abc);

	//FAUTE, afficher list n'est pas possible, il faut faire list.tete.print()
	std::cout << "Liste : " << list << std::endl;
	std::cout << "Taille : " << list.size() << std::endl;

	// Affiche à l'envers
	//FAUTE, size_t (i) est non signé, donc il va y avoir des problèmes
	//si on va en dessous de 0...
	//solution:
	// 1) remplacer size_t i par un entier signé mais on perd le non signé
	// 2) pour garder size_t, il faut changer la condition >= en > (i ne va pas sous 0),
	// retirer le -1 de i=... -1,
	// et enfin, ajouter ajouter dans list[i] un -1
	// du au changement de i et de la condition, i va aller de
	// list.size() à 0
	for (i= list.size() ; i > 0 ; i--) {
		std::cout << "elt " << i << ": " << list[i-1] << std::endl;
	}

	//FAUTE, les 3 champs sont de simples entiers (8 bits), il n'y a donc pas à les delete
	// liberer les char de la chaine
	/*
	for (char *cp = str ; *cp ; cp++) {
		delete cp;
	}*/

	//FAUTE, str est un pointeur sur 3 cases mémoires contigues, il faut donc ajouter []
	// et la chaine elle meme
	delete [] str;

	//FAUTE, il manque le retour de la fonction main()
	//pas prévue ? Au cas où...
	return 0;
}
