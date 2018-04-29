#include "stdafx.h"
#include "text_freq.h"
#include "my_map.h"
#include "key_value.h"
#include <fstream>
#include <sstream>
#include <functional>
#include <algorithm>
#include <locale>
#include <sstream>
using namespace std;

string read_file(string file_name)
{
	ifstream file(file_name);
	string theString;
	string babyString;
	if (file.is_open()) {
		while (!file.eof()) {
			file >> babyString;
			theString.append(babyString);
			theString.append(" "); //yay
		}
	}
	return theString;
    //this should read the file, and return the string of the whole file
}

string remove_punctuation(string& text)
{
	std::string result = "";
	char charred;
	for (auto it = text.begin(); it != text.end(); ++it) {
		charred = *it;
		if (charred < 0 || charred > 255) {
			//some more complicated unicode characters break this.
			charred = 0;
		}
		if (!ispunct(charred))
			result.push_back(charred);
	}
	text = result;
	return result;
    /*std::string result;
    std::remove_copy_if(text.begin(), text.end(),            
                        std::back_inserter(result), //Store output           
                        std::ptr_fun<int, int>(std::ispunct));
    return result;*/ //"this is already done for you" maybe if it worked, yeah...
}

my_map<string, double> create_freq_map(const string& text)
{
    my_map<string,double> freq_map;
	stringstream streaming(text);
	string theory;
	while (!streaming.eof()) {
		streaming >> theory;
		freq_map[theory]++; //this will probably get a little messed up by the fact that the default value for int's is probably 32. 
			//cuz that's what static_cast<int>(' ') gets converted to, I think.
	}
    //FINISH THIS FUNCTION
    //this should find the frequecies of every word in the text

    return freq_map;
}

vector<key_value<string,double>> vectorize_map(my_map<string, double>& freq_map)
{
    vector<key_value<string,double>> freq_vec;

    //FINISH THIS FUNCTION
    //this should return a sorted vector of the results

    return freq_vec;
}

void remove_stop_words(vector<key_value<string,double>>& freq_vec, vector<string> stop_words)
{
   //FINISH THIS FUNCTION
   //this function should remove the elements contained in stop_words from freq_vec 
}

void print_top_20_freqs(const vector<key_value<string,double>>& freq_vec, ostream& out)
{
    //prints the top 20 frequencies to out
}
