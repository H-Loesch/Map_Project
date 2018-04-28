#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <vector>
#include <queue>
#include <stdexcept>
#include <math.h>
#include <iostream>
#include <fstream>

using namespace std;

enum color {red, black};

template <typename T, typename E>
struct Node
{
	//all members of object are public.
	T key;
	E value; //this SHOULD work.
	bool visited; //keeps track of if node has been visited by an in-order for the graph.
	bool prev;
	Node<T, E>* left;
	Node<T, E>* right;
    Node<T, E>* parent;

    int search_time;
    color node_color; //not used in this implementation

	Node() : key(T()), value(E()), visited(false), prev(false), left(NULL), right(NULL), parent(NULL), search_time(0), node_color(color::red) {}

	//value can't be easily assigned a default value, so this constructor doesn't assign a value to it at all. Just has a key.
	Node(T k, bool vis = false, bool prv = false, Node<T, E>* l = NULL, Node<T, E>* r = NULL, Node<T, E>* p = NULL, color col = color::red)
		: key(k), visited(vis), prev(prv), left(l), right(r), parent(p), search_time(0), node_color(col) {}

	//constructor which also assigns value.
    Node(T k, E v, bool vis = false, bool prv = false, Node<T,E>* l = NULL, Node<T,E>* r = NULL, Node<T,E>* p = NULL, color col = color::red)
		: key(k), value(v), visited(vis), prev(prv), left(l), right(r), parent(p), search_time(0), node_color(col) {}
	//I just think it's more readable to make them be in a seperate thing, but maybe that's just me.

	Node(const Node<T,E>* other) //System shock 2 hybrid voice: AnOtheR......
	{
		key = other->key;
		value = other->value;
		node_color = other->node_color;
		search_time = other->search_time;
	}

	Node<T,E>* insertRight(T obj, color colour);
	Node<T,E>* insertLeft(T obj, color colour);

	bool is_leaf(){return (left == 0 && right == 0);} //shouldn't these be == nullptr or smth?
	bool operator!=(const Node<T, E> &r) { return key != r.key; }
	bool operator==(const Node<T, E> &r) { return key == r.key; } 
	bool operator< (const Node<T, E> &r) { return key < r.key; }
	bool operator<=(const Node<T, E> &r) { return key <= r.key; }
	bool operator> (const Node<T, E> &r) { return key > r.key; }
	bool operator>=(const Node<T, E> &r) { return key >= r.key; }
	
	bool no_visit() {
		if (this == nullptr) //one-line implementation with && still tried to read prev from a nullptr, thus this.
			return true;
		if (this->prev)
			return true;
		return false;
	} //change to use function that checks the vector.
};

//creates and inserts a node to the right of the current. does NOT delete the old node, if any. Node will have no value.
template <typename T, typename E>
Node<T,E>* Node<T,E>::insertRight(T obj, color colour) { 
	this->right = new Node<T, E>(obj, false, false, NULL, NULL, NULL, colour);
	this->right->parent = this;
	return this->right;
}

// creates and inserts a node to the left of the current. does NOT delete the old node, if any. Node will have no value.
template <typename T, typename E> 
Node<T,E>* Node<T,E>::insertLeft(T obj, color colour) {
	this->left = new Node<T,E>(obj, false, false, NULL, NULL, NULL, colour);
	this->left->parent = this;
	return this->left;
}

template <typename T, typename E>
std::ostream& operator<<(std::ostream& out, const Node<T, E>& kvp)
{

	return out << kvp.key << " " << kvp.value;
}









template <typename T, typename E>
struct BTree
{
protected:
	int size;

	
public:
	int depth;
	Node<T,E>* root;

    BTree();
	BTree(const BTree<T, E>& other);
	BTree<T, E>& operator=(const BTree<T, E>& other);
	//BTree<T, E>& operator=(const BTree<T, E> other);

	Node<T,E>* get_root(){return root;}
	const Node<T,E>* get_root() const {return root;} 
	virtual Node<T, E>* insert(T obj);
	virtual Node<T,E>* insert(T obj, E val);
	Node<T,E>* search(T obj);
	void update_search_times();
	float get_average_search_time();
    ostream& inorder(ostream& out);
    virtual ostream& print_level_by_level(ostream& out);
	int search_time_single_update(T obj);
	int get_total_search_time(Node<T,E>* node);
	~BTree();
	void print_rec(ostream& out, Node<T,E>* node);
	int get_total_search_time();

private:
	void copy_helper(Node<T,E>* copy_to, const Node<T,E>* copy_from) const;
	virtual Node<T,E>* insert_helper(T obj, Node<T,E>* node); //carries the value with it. Probably inefficient, but whatever.
	Node<T,E>* search_helper(T obj, Node<T,E>* node);
	ostream& inorder_helper(ostream& out, Node<T,E>* node);
	void update_search_times_helper(Node<T,E>* node, int depth);
	virtual void pretty_print_node(ostream& out,Node<T,E>* node);
	int search_time_single_helper(Node<T,E>* node, T obj, int depth);
	void print_level_helper(Node<T,E>* node, std::vector<std::queue<Node<T,E>*>> &vec, int depth);
};

template <typename T, typename E> 
BTree<T, E>::BTree() {
	size = 0;
	root = NULL;
	depth = 1;
	//does there need to be anything else? idk.
	//I mean, I've already set up for root initially being empty elsewhere...
}
template <typename T, typename E>
ostream& operator<<(ostream& out, BTree<T, E>& tree)
{
	tree.print_rec(out, tree.get_root()); //doesn't even need to be part of the BTree class, but print_node is so it's gotta be. 
	return out; //and I ain't risking losing points for changing functions, I barely know what I'm doing as-is lmao.
}

template <typename T, typename E> 
void BTree<T, E>::print_rec(ostream& out, Node<T,E>* node) {
	if (node != nullptr) {
		print_rec(out, node->left);
		pretty_print_node(out, node);
		print_rec(out, node->right);
	}
}

template <typename T, typename E>
ostream& operator<<(ostream& out, Node<T,E> node)
{
	return out << "( " << node.key << ", " << node.search_time << ", " << node.node_color << " )";
}

template <typename T, typename E>
void BTree<T, E>::pretty_print_node(ostream& out,Node<T,E>* node)
{
	out << node->key << "["<<node->search_time<<"] ";
}

template <typename T, typename E>
istream& operator>>(istream& in, BTree<T, E>& tree)
{
	T intake;
	while (in >> intake) { //this certainly might work, lol
		tree.insert(intake); //probably should set up insert such that it operates via keys, but... I'll get to that later.
	}
	/*
		take input from the in stream, and build your tree
		input will look like
		4 
		2 
		6 
		1 
		3 
		5 
		7
	*/
}

//copy constructor
template <typename T, typename E>
BTree<T, E>::BTree(const BTree<T, E>& other)
{
	if (other.root == nullptr) {
		throw std::runtime_error("Root of copy source's tree is null");
	}
	else {
		size = other.size;
		depth = other.depth;
		root = new Node<T,E>;
		copy_helper(root, other.get_root()); //copy_helper should make things okay when there's null's elsewhere.
	}
}

template <typename T, typename E>
BTree<T, E>& BTree<T, E>::operator=(const BTree<T, E>& other)
{
	if (other.root == nullptr) {
		throw std::runtime_error("Root of copy source's tree is null");
	}
	size = other.size;
	depth = other.depth;
	copy_helper(root, other.get_root()); //copy_helper SHOULD be able to handle this... right?
	/*
		complete this assignment operator
		make sure when copying nodes to copy
			the key
			the relative parent, and left and right children
			the node_color
				not important for this part but will be used later
	*/
	return *this;
}

template <typename T, typename E>
void BTree<T, E>::copy_helper(Node<T,E>* copy_to, const Node<T,E>* copy_from) const
{
	//these being first SHOULDN'T be a problem, since this'll hopefully only get called on things known to not be null
	copy_to->key = copy_from->key;
	copy_to->node_color = copy_from->node_color;
	copy_to->search_time = copy_from->search_time;
	copy_to->value = copy_from->value;

	//if copy_from is not nullptr
	if (copy_from->left != nullptr) { //copy_from isn't nullptr
		if (copy_to->left == nullptr) {
			copy_to->left = new Node<T,E>; //if child doesn't exist, make one.
			copy_to->left->parent = copy_to; //and also make current its parent
		}
		copy_helper(copy_to->left, copy_from->left);
	} else if (copy_from->left == nullptr && copy_to->left != nullptr) { //copy_to isn't nullptr
		//calling the delete_rec MIGHT actually work here! Who knows, though :3c
		delete_rec(copy_to->left); 
		copy_to->left = nullptr;
	} else if (copy_from->left == nullptr && copy_to->left == nullptr) { //both are nullptr
		//do nothing lmao
	}

	if (copy_from->right != nullptr) { //copy_from isn't nullptr
		if (copy_to->right == nullptr) {
			copy_to->right = new Node<T,E>;
			copy_to->right->parent = copy_to; //this'd be more space-efficient if I consolidated this instead of splitting into right/left
		}									// but splitting it makes assigning the parent much simpler.
		copy_helper(copy_to->right, copy_from->right);
	} else if (copy_from->right == nullptr && copy_to->right != nullptr) { //just copy_from is nullptr
		delete_rec(copy_to->right);
		copy_to->right = nullptr;
	} else if (copy_from->left == nullptr && copy_to->left == nullptr) { //both nullptr
		//do nothing lmao
	}
}

template <typename T, typename E>
void delete_rec(Node<T,E>* node) {
	if (node == nullptr) {
		//don't do anything lmao
	}
	if (node->left != nullptr) {
		delete_rec(node->left);
		node->left = nullptr;
	}
	if (node->right != nullptr) {
		delete_rec(node->right);
		node->right = nullptr;
	}
	delete node;
}

//basic function for insertion of nodes into binary tree.
template <typename T, typename E>
Node<T, E>* BTree<T, E>::insert(T obj)
{
	size += 1;
	if (this->get_root() == NULL) { //if empty, create node at root.
		root = new Node<T, E>(obj);
		root->search_time = 1;
		return root;
	}
	Node<T, E>* out = insert_helper(obj, get_root()); //search_time is not updated at time of creation so that that feature can be easily removed if needed.
	out->search_time = search_time_single_update(obj);
	if (out->search_time > depth) {
		depth = out->search_time;
	}
	return out;
}

//insertion function which also assigns value.
template <typename T, typename E>
Node<T,E>* BTree<T, E>::insert(T obj, E val) 
{
	Node<T, E>* out = insert(obj);
	out->value = val;
	return out;
}

//helper function for the insert node function.
template <typename T, typename E>
Node<T,E>* BTree<T, E>::insert_helper(T obj, Node<T,E>* working) {
	if (obj > working->key) {//if obj is bigger than current's key, go to right.
		if (working->right == nullptr) {  //if right doesn't exist, make it exist using obj
			return working->insertRight(obj, red);
		}
		else { //else go to left
			return insert_helper(obj, working->right); //this COULD not have brackets on it. But I'm here for order and predictability, not minimizing space
		}
	}
	else {
		if (working->left == nullptr) {
			return working->insertLeft(obj, red);
		}
		else {
			return insert_helper(obj, working->left);
		}
	}
} //seems to work okay. Should probably get searchValue included in here sometime.


/*template <typename T, typename E> //this one keeps track of the depth, and also updates the max-depth of the dtree.  
Node<T,E>* BTree<T, E>::insertg(T obj) {
	size += 1;
	if (this->get_root() == NULL) { //if empty, create node at root.
		root = new Node<T,E>(obj);
		root->search_time = 1;
		return root;
	}
	Node<T,E>* out = insert_helper(obj, get_root());//TA said to leave parameters of insert() where they are, so... hence searchtimeupdate
	out->search_time = search_time_single_update(obj); //not a fan!
	return out;
} //it's not done yet */


template <typename T, typename E>
Node<T,E>* BTree<T, E>::search(T obj)
{
	Node<T,E>* temp = search_helper(obj, this->get_root());
	if (temp == nullptr) {
		throw std::runtime_error("Key does not exist"); //necessary? maybe :3c
	}
	return temp;
}	

template <typename T, typename E>
Node<T,E>* BTree<T, E>::search_helper(T obj, Node<T,E>* node)
{
	if (node == NULL) {
		return nullptr;
	}
	else if (node->key == obj) {
		return node; //base case
	}
	else if (obj < node->key) {
		return search_helper(obj, node->left);
	}
	else if (obj > node->key) {
		return search_helper(obj, node->right);
	}
	else {
		//?????
	}
}

//could this be replced by just calling the helper funciton instead? probably. look at later.
template <typename T, typename E> 
int BTree<T, E>::search_time_single_update(T obj) { //this exists mostly bc TA said that the insert() parameters shouldn't be changed
	return search_time_single_helper(this->get_root(), obj, 1); //and this seemed better than figuring out recursive assigning without another parameter
}

template <typename T, typename E>
int BTree<T, E>::search_time_single_helper(Node<T,E>* node, T obj, int depth) {
	if (node == NULL) {
		return -99; //doesn't exist! Oh no!
	}
	else if (node->key == obj) {
		//node->search_time = depth;
		return depth; //base case
	}
	else if (obj < node->key) {
		return search_time_single_helper(node->left, obj, depth + 1);
	}
	else if (obj > node->key) {
		return search_time_single_helper(node->right, obj, depth + 1);
	}
	else {
		//?????
	}
}

template <typename T, typename E>
void BTree<T, E>::update_search_times_helper(Node<T,E>* node, int depth)
{
	if (node != nullptr) {
		node->search_time = depth;
		update_search_times_helper(node->left, depth + 1);
		update_search_times_helper(node->right, depth + 1);
	}
}

template <typename T, typename E>
void BTree<T, E>::update_search_times()
{
	update_search_times_helper(get_root(), 1);
}

template <typename T, typename E>
ostream& BTree<T, E>::inorder_helper(ostream& out, Node<T,E>* node)
{
	if (node != nullptr) {
		inorder_helper(out, node->left);
		std::cout << node->key << ", " << node->search_time << std::endl;
		inorder_helper(out, node->right);
		return out;// why does this need to return out
	}
	
}

template <typename T, typename E>
ostream& BTree<T, E>::inorder(ostream& out)
{
	if (size < 15) {
		inorder_helper(out);
	}
	else {
		std::cout << "Sorry, there's a few too many nodes. I wrote it to a file called star.txt though! c:" << std::endl;
		ofstream star("star.txt");
		if (star.is_open()) {
			inorder_helper(star);
		} else {
			std::cout << "Oh... nevermind, that didn't work either! I'm gonna give up now! c:" << std::endl;
		}
	}
	/*
		print your nodes in infix order
		if our tree looks like 

		4
		2 6
		1 3 5 7

		we should get

		1 2 3 4 5 6 7 
	*/
	out << "Value \t Search Cost" << endl;
	return out;
}

template <typename T, typename E>
ostream& BTree<T, E>::print_level_by_level(ostream& out)
{
	if (this->depth > 9) {
		std::cout << this->depth;
		out << "Too many layers in tree for acceptable level-by-level print. Operation aborted." << std::endl;
		return out;
	}
	if (depth <= 0) {
		out << "Attempt to print empty tree by level ignored" << std::endl;
		return out;
	}
	std::vector<std::queue<Node<T,E>*>> treeVector;
	for (int i = 0; i < depth; i++) { //create as many vectors as we'll need. 
		std::queue<Node<T,E>*> putThere;
		treeVector.push_back(putThere);
	}
	print_level_helper(this->get_root(), treeVector, 0);
	for (int i = 0; i < treeVector.size(); i++) {
		while (!treeVector.at(i).empty()) {
			out << " ";
			Node<T,E>* temp = treeVector.at(i).front();
			treeVector.at(i).pop();
			if (temp == nullptr) {
				out << "X";
			}
			else {
				out << temp->key;
			}
		}
		out << " [" << i + 1 << "]" << std::endl;
	}
	/*
		print the tree using a BFS 
		output should look like this if we dont have a full tree

		4
		2 6
		1 X 5 7
		X X X X X X X 9

		it will be helpfull to do this part iterativly, 
		so do the BFS with the std stack data structure.

		it may also be helpfull to put the entire tree into a vector 
		(probably google this if you dont know how to do it)
	*/
    return out;
}

template <typename T, typename E> //I'm actually kind of proud of this one.
void BTree<T, E>::print_level_helper(Node<T,E>* node, std::vector<std::queue<Node<T,E>*>> &vec, int depth) {
	if (node != nullptr && depth >= 0) { //this may not be needed, since if's a little furhter down should prevent this being called on nulls
		
		vec.at(depth).push(node); //needed queues are already in the vector.

		if (node->left == nullptr) { 
			for (int i = node->search_time; i < this->depth; i++) { //loop through as many missing layers as there are in this branch
				for (int j = 0; j < pow(2, i - node->search_time); j++) {
					vec.at(i).push(NULL); //push empty nodes to fill out the bottom layers.
				}
			}
		}
		else {
			print_level_helper(node->left, vec, depth + 1); //if the left child exists, run this function on it.
		}

		if (node->right == nullptr) { //same as the left side lol
			for (int i = node->search_time; i < this->depth; i++) { 
				for (int j = 0; j < pow(2, i - node->search_time); j++) {
					vec.at(i).push(NULL); 
				}
			}
		}
		else {
			print_level_helper(node->right, vec, depth + 1);
		}
		//case for (if this isn't nullptr) is at the top.
	}
}

template <typename T, typename E>
int BTree<T, E>::get_total_search_time(Node<T,E>* node)
{
	return search_time_counter(0, node);
}

template <typename T, typename E> 
int BTree<T, E>::get_total_search_time() {
	return search_time_counter(0, root);
}

template <typename T, typename E>
float BTree<T, E>::get_average_search_time() //
{
	float total = get_total_search_time(this->get_root());
	return total / static_cast<float>(size);
}

template <typename T, typename E>
int search_time_counter(int count, Node<T,E>* node) {
	if (node->left != nullptr) {
		count = search_time_counter(count, node->left);
	}
	if (node->right != nullptr) {
		count = search_time_counter(count, node->right);
	}
	return count += node->search_time;
}

template <typename T, typename E>
BTree<T, E>::~BTree() {
	if (this->root != nullptr) //I guess we gotta check everything for null now :/
		delete_rec(this->get_root());
}

#endif