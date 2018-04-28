#include "stdafx.h"
#include "my_map.h"
#include "text_freq.h"
#include <iostream>

int main()
{
	/* old test code (tree iteration)
	int warbus = static_cast<int>(NULL) + 5;
	m["a"] = 10;
	m["hh"] = 3;
	m["q"] = 4;
	m["g"] = 5;
	m["e"] = 15;
	m["h"] = 15;
	m["o"] = 11;
	m["u"] = 1;
	//m["f"] = 15; //add a throw error for same keys.

	cout << endl << m.container << endl;
	m.container.print_level_by_level(std::cout);

	Node<int, int> honk(0, 0);
	Node<int, int> donk(0, 0);
	honk != donk;

	auto curr = m.begin();

	while (curr != m.end())
	{
		cout << *curr << endl;
		curr + 2;
	}*/

	string stringus = read_file("test_text1.txt");
	my_map<string, int> m;
	remove_punctuation(stringus);
	my_map<string, double> warble = create_freq_map(stringus); //SEEMS to work...?
	auto curr = warble.begin();
	my_map<double, string> inorder;
	while (curr != warble.end())
	{
		key_value<string, double> temp = *curr;
		inorder[temp.value] = temp.key;
		cout << *curr << endl;
		curr++;
	}
	return 0;
}

/*TODO
add an error for same keys

store visited nodes in the iterator's members instead of the nodes: storing in nodes is more complicated than needed.

remove key-value class

remove shovel member from node class.

Clean up commenting on operator++ function?

create operator<< for maps.

stuff taken from the handout for this assignment:
put tree traversal code into a helper function for operator++, or at least divide it into sub-functions.

reading text file into string

remove punctuation

count number of word occurences, store in map

vectorize_map function

filtering of words

make sure destructors are working okay (no memory leaks).
*/



/* current changes
Reading text file from string
removing puncutation
storing number of word occurrences in map
*/