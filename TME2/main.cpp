#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>

void f2(std::vector<std::string> &v, const std::string &s) {
	auto it = find(v.begin(), v.end(), s);
	if(it == v.end()) {
		v.push_back(s);
	}
}

void f3(std::vector<std::pair<std::string, int>> &v, const std::string &s) {
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
void f3_print(const std::vector<std::pair<std::string, int>> &v) {
	//war
	//peace
	//toto
	for(auto it = v.begin(), end_it=v.end(); it != end_it; ++it) {
		std::pair<std::string, int> p = *it;
		if(p.first == "war" || p.first == "peace" || p.first == "toto")
			std::cout << p.first << " --- " << p.second << std::endl;
	}
}

int main () {
	using namespace std;
	using namespace std::chrono;

	ifstream input = ifstream(/*/"tmp/ */"WarAndPeace.txt");

	// 2)
	//std::vector<std::string> w_diff;

	// 3)
	//vector<pair<string, int>> w_occur;


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
		///*
		if (nombre_lu % 100 == 0)
			// on affiche un mot "propre" sur 100
			cout << nombre_lu << ": "<< word << endl;
		nombre_lu++;
		//*/
		// ---------------------------


	    // 2) O(n²)
		/*
		f2(w_diff, word)
		++nombre_lu;
		*/

		// 3)
		/*
		f3(w_occur, word);
		++nombre_lu;
		*/
	
	}
	input.close();

	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;

	// 3)
	//f3_print(w_occur);

    return 0;
}


