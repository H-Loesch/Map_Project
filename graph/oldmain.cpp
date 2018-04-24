#include "stdafx.h"
#include "BTree.h"
#include <string>

template<typename T, typename E>
BTree<T, E> read_file(string file_name);

using namespace std;
/*
int main()
{
	BTree<int, string> dingus;
	dingus.insert(21, "fuck");
	ofstream outDonk;
	BTree<int, int> donk;
	donk = read_file<int, int>("1r");
	outDonk.open("1rout.txt");
	std::cout << "FUCK";
	donk.print_level_by_level(outDonk);
	outDonk.close();

		donk = read_file<int, int>("2r");
	outDonk.open("2rout.txt");
	donk.print_level_by_level(outDonk);
	outDonk.close();

		donk = read_file<int, int>("3r");
	outDonk.open("3rout.txt");
	donk.print_level_by_level(outDonk);
	outDonk.close();

		donk = read_file<int, int>("4r");
	outDonk.open("4rout.txt");
	donk.print_level_by_level(outDonk);
	outDonk.close();

		donk = read_file<int, int>("1l");
	outDonk.open("1lout.txt");
	donk.print_level_by_level(outDonk);
	outDonk.close();

		donk = read_file<int, int>("2l");
	outDonk.open("2lout.txt");
	donk.print_level_by_level(outDonk);
	outDonk.close();

		donk = read_file<int, int>("3l");
	outDonk.open("3lout.txt");
	donk.print_level_by_level(outDonk);
	outDonk.close();

		donk = read_file<int, int>("4l");
	outDonk.open("4lout.txt");
	donk.print_level_by_level(outDonk);
	outDonk.close();

		donk = read_file<int, int>("1p");
	outDonk.open("1pout.txt");
	donk.print_level_by_level(outDonk);
	outDonk.close();

		donk = read_file<int, int>("2p");
	outDonk.open("2pout.txt");
	donk.print_level_by_level(outDonk);
	outDonk.close();

	donk = read_file<int, int>("3p");
	outDonk.open("3pout.txt");
	donk.print_level_by_level(outDonk);
	outDonk.close();

	donk = read_file<int, int>("4p");
	outDonk.open("4pout.txt");
	donk.print_level_by_level(outDonk);
	outDonk.close();

	std::cout << ("honk" > "donk");
	return 0;
}*/

template<typename T, typename E>
BTree<T, E> read_file(string file_name) // oh okay
{
	ifstream port(file_name);
	T donk;
	BTree<T, E> newTree;
	if (port.is_open()) { //we're all just looking for a port that's open, aren't we?
		while (port >> donk) {//this will almost certainly fail.
			newTree.insert(donk, 0);
			//anything else need to be done here?
		}
	}

    /*
        open the file and use the input operator (operator>>)
        to construct a new tree
    */
    return newTree;
}

//TODO: total and average search time
//figure out why we have two assignment operators??? commenting one of them out for now.
//total search time works, but got it's starting to bother me how insert doesn't just update the things itself, and uses a thing instead. pointless.
//fix the insert function (make a second, good one)