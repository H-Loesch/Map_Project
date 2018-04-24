#include "stdafx.h"
#include "my_map.h"
#include "text_freq.h"
#include <iostream>

int main()
{
	string stringus = read_file("test_text_small1.txt");
	my_map<string, int> m;
	remove_punctuation(stringus);
	my_map<string, double> warble = create_freq_map(stringus);
	int warbus = static_cast<int>(NULL) + 5;
	m["b"] = 10;
	m["f"] = 3;
	m["r"] = 4;
	m["g"] = 5;
	m["a"] = 15;
	m["c"] = 15;
	//m["f"] = 15; //add a throw error for same keys.

	cout << endl << m.container << endl;
	m.container.print_level_by_level(std::cout);

	Node<int, int> honk(0, 0);
	Node<int, int> donk(0, 0);
	honk != donk;

	auto curr = m.begin();
	curr++;

	while (curr != m.end())
	{
		cout << *curr << endl;
		curr++;
	}
	return 0;
}

//TODO: add an error for same keys.