

#include "algorithms.hpp"


std::string algorithm::assembler( const T& p)
{
	// This simple function takes as parameter the struct containing all the website information and returns
	// a string containing all the text needed.
	std::string final_string{ p.text + " " + p.subtitles + " " + p.title };
	return final_string;

}
int algorithm::word_counter(std::string& text)
{
	// This function takes as parameter a string and returns the amount of words in the string

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
	// This functions takes as parameter a string, in return it will give
	// the amount of time each time occured in the string in the form of a vector of pairs of strings as first
	// And an integer as second

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



