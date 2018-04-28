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
	}
	return 0;
}

/*TODO
add an error for same keys

implement vector-storage for the nodes

remove key-value class

remove shovel member from node class.

Clean up commenting on operator++ function?

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
fixed bug with tree traversal (root being final node caused exception)
implemented novisit() function for nodes (combines is_nullptr and is_visited)
removed copy-and-swap from the iterator + int function, since it wasn't needed.
iterator + int function tested lightly, works fine. Will throw out_of_range exceptions sometimes, but that's by intent actually.
*/