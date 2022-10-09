#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <algorithm>
#include "hash_map.h"

//TME2
void f2_tme2(std::vector<std::string> &v, const std::string &s) {
	auto it = find(v.begin(), v.end(), s);
	if(it == v.end()) {
		v.push_back(s);
	}
}

void f3_tme2(std::vector<std::pair<std::string, int>> &v, const std::string &s) {
	auto it = find_if(v.begin(), v.end(),
		[&](const auto &pair) {
			return pair.first == s;
		});
	
	if(v.end() == it) {
		v.push_back(std::pair(s,1));
	}
	else {
		it->second++;
	}
}

//print les mots
void f3_print_tme2(const std::vector<std::pair<std::string, int>> &v) {
	//war
	//peace
	//toto
	for(auto it = v.begin(), end_it=v.end(); it != end_it; ++it) {
		std::pair<std::string, int> p = *it;
		if(p.first == "war" || p.first == "peace" || p.first == "toto")
			std::cout << p.first << " --- " << p.second << std::endl;
	}
}

void f6_tme2(HashMap<std::string,int> &map) {
	//war
	//peace
	//toto
	
	int *n1 = map.get("war");
	int *n2 = map.get("peace");
	int *n3 = map.get("toto");
	
	//je passe les détails de si n1 et n2 sont nullptr pour aller plus vite
	//il n'y a que toto qui l'est
	std::cout << "war: " << *n1 << std::endl;
	std::cout << "peace: " << *n2 << std::endl;

	int nb = (n3 == nullptr)? 0 : *n3;
	std::cout << "toto: " << nb << std::endl;
}

void f8_tme2(std::vector<std::pair<std::string,int>> &vec) {
	std::sort(vec.begin(), vec.end(), [](const auto &p1, const auto &p2) {
	return p1.second > p2.second;
    });

    for(auto it=vec.begin(), end=vec.begin()+10; it!= end; ++it) {
        std::cout << it->first << ": " << it->second << std::endl;
    }
}


//TME3

// 1)
template<typename iterator>
size_t count(iterator begin, iterator end) {
	//return end - begin;
	size_t ct = 0;
	while(begin != end) {
		++ct;
		++begin;
	}
	return ct;
}

// 2)
template<typename iterator, typename T>
size_t count_if_equal(iterator begin, iterator end, const T &val) {
	size_t ct = 0;
	while(begin++ < end) {
		if(*begin == val)
			++ct;
	}
	return ct;
}

// 3)
void f3_tme3(const size_t nb_w, HashMap<std::string, int> &map) {
	auto ct = count(map.get_buckets().begin(), map.get_buckets().end());
	std::cout << "nbr buckets: " << map.size() << " | " << ct << std::endl;

	ct = 0;
	for(auto it=map.get_buckets().begin(), end=map.get_buckets().end(); it != end; ++it) {
		ct += count(it->begin(), it->end());
	}
	std::cout << "nbr mots: " << nb_w << " | mots uniques: " << ct << std::endl;

}

// 5)

std::vector<std::pair<std::string,int>> f5_tme3(HashMap<std::string, int> &map) {
	std::vector<std::pair<std::string, int>> vec;
	vec.reserve(map.get_buckets().size());
	for(auto it=map.begin(), end=map.end(); it != end; ++it) {
		auto e = *it;
		vec.push_back(std::pair(e.key, e.value));
	}
	return vec;
}

int main () {
	using namespace std;
	using namespace std::chrono;

	ifstream input = ifstream(/*/"tmp/ */"WarAndPeace.txt");

	//TME2
	// 2)
	//std::vector<std::string> w_diff;

	// 3)
	//vector<pair<string, int>> w_occur;

	// 6)
	HashMap<std::string, int> map;



	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	size_t nombre_lu = 0;
	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");
	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);

		// word est maintenant "tout propre"
		// ---------------------------
		/*
		if (nombre_lu % 100 == 0)
			// on affiche un mot "propre" sur 100
			cout << nombre_lu << ": "<< word << endl;
		*/
		// ---------------------------

		//TME2
	    // 2) O(n²)
		//f2_tme2(w_diff, word)
		

		// 3)
		
		//f3_tme2(w_occur, word);
		
		// 6)
		int *nb_get = map.get(word);
		//int nb = (nb_get==nullptr)? 0 : *nb_get;
		int nb;
		if(nb_get==nullptr)
			nb = 0;
		else
			nb = *nb_get;
		++nb;
		map.put(word, nb);


		++nombre_lu;
	}
	input.close();

	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;

	//TME2
	// 3)
	//f3_print(w_occur);

	// 6)
	/*
	f6_tme2(map);
	map.print_entry("war");
	map.print_entry("peace");
	map.print_entry("toto");
	*/

	// 7)
	
	//auto vec = map.f7_tme2();
	//std::cout << vec.size() << " " << map.size() << std::endl;

	// 8)
	//f8_tme2(vec);



	//TME3

	// 3)
	//f3_tme3(nombre_lu, map);

	// 5) et 6)
	//auto vec = map.f7_tme2();
	//f8_tme2(vec);
	//std::cout << "------------" << std::endl;
	//auto vecc = f5_tme3(map);
	//f8_tme2(vecc);


    return 0;
}


