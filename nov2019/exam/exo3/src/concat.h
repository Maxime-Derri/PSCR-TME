#pragma once

#include <vector>
#include <string>

namespace pr {

class concat {
	// TODO : attributs stockant ref ou pointeurs vers les constituants v1,v2
	std::vector<std::string> &l1, &l2;
public:
	concat(std::vector<std::string> & v1, std::vector<std::string> & v2): l1(v1), l2(v2) {}

	class iterator {
		// TODO : attributs
		std::vector<std::string>::iterator it;
		concat & curs;

	public:
		// TODO : signature du constructeur
		iterator(const std::vector<std::string>::iterator &i, concat &c): it(i), curs(c) {}

		// TODO : contrat itérateur
		std::string & operator*() {
			return *it;
		}

		iterator & operator++() {
			++it;
			if(it == curs.l1.end())
				it = curs.l2.begin();

			return *this;
		}

		bool operator!=(const iterator & other) const {
			return it != other.it;
		}
	};

	iterator begin() {
		return iterator(l1.begin(), *this);
	}

	iterator end() {
		return iterator(l2.end(), *this);
	}
};

}
