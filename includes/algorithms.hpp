#include "includes.hpp"

class algorithm {

public:

	// Fonctions de la classe.
	int word_counter(std::string& text);

	std::unordered_map<std::string, int> word_occurences(std::string& text);

	bool word_finder(std::string& text, std::string& word);
	
};


