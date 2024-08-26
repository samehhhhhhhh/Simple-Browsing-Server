

#include "algorithms.hpp"

int algorithm::word_counter(std::string& text)
{
	// Cette fonction prend comme parametre une chaine de caractére et retourne le nombre total de mot dans celle ci.

	int word_count{ 0 };

	for (auto i : text)

	{

		if (i == ' ')
		{
			word_count++;
		}

	}

	word_count++;

	return word_count;

}

bool algorithm::word_finder(std::string& text, std::string& word)
{
	size_t pos = text.find(word);
	return pos != std::string::npos;
}
std::unordered_map<std::string, int> algorithm::word_occurences(std::string& text)
{
	// Cette fonction comme parametre une chaine de caractére et retourne le nombre d'occurence de chaque mot dans une hashmap avec cette structure : 
	// vec.first -> le mot vec.second -> sont occurence totale dans la chaine.

	std::string word;
	std::unordered_map<std::string, int> vec;

	for (auto i : text)
	{

		if (i != ' ' && i != '.' && i != '!' && i != '?' && i != ';')
		{
			word += i;
		}

		else 
		{

			std::unordered_map<std::string, int>::iterator it = vec.find(word);

			if (it != vec.end()) 
			{
				it->second++;
				word = "";
			}

			else 
			{
				vec[word] = 1;
				word.clear();
			}
		}
	}
	
	return vec;

}



