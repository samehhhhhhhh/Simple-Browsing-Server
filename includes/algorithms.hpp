

#include "includes.hpp"

class algorithm {
public:
	struct T {
		std::string title;
		std::string linked;
		std::string link;
		std::string subtitles;
		std::string text;
	};
	std::string assembler(const T& p);
	int word_counter(std::string& text);
	std::unordered_map<std::string, int> word_occurences(std::string& text);
	bool word_finder(std::string& text, std::string& word);
	

};


