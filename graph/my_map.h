#ifndef MY_MAP_H
#define MY_MAP_H

#include "BTree.h"
#include "key_value.h"
#include <iterator> 
#include <vector>
#include <string>
using namespace std;

template <typename T, typename E>
struct my_map
{

    class map_iter : public iterator<input_iterator_tag, T, E> 
    {															

    /*Instead of using a prev_node vector, it would probably be much faster to store Has_Been_Visited within each node.
	that way, checking on each node is only 1 operation, then at the end of whatever is needing to know if stuff has been 
	visited can just run a function that flips the Has_Been_Visited to 0 on all nodes.*/
	private:
        vector<Node<T, E>*> prev_nodes; // right so like. My nodes are NOT based on key_value, cuz why would they be 

    public:
		Node<T, E>* node;
		key_value<T, E>* shovel;

        map_iter(Node<T, E>* x) :node(x){}  //these two may or may not work.
        map_iter(const map_iter& iter) : node(iter.node){}

		map_iter& operator++() { //walking through this worked with the tree I tested with, will leave further testing for in-program.
			if (node == nullptr) {
				throw std::runtime_error("Iterator out of range."); // error message text?
			}
			if (node->left->no_visit() && node->right->no_visit() && node->parent == nullptr)
				//if node is only one in the tree, then skip right to end()
				node = node->right;
			else if (node->right->no_visit() && node->left->no_visit()) {
				//if neither child exists and is unvisited
				if (node->parent->right == node){
					//if current is right child of its parent
					node->prev = true;
					//this while() should also catch if the current node is unvisited, since it should be impossible for the current to be unvisited and the right be visited)
					while (node->prev && (node->parent != nullptr) && (node->right->no_visit() && node->left->no_visit())) {
						//if both children unavailable, parent exists, and current.prev==true
						//then set children's .prev to false, and node = node->parent
						if (node->left != nullptr)
							node->left->prev = false;
						if (node->right != nullptr)
							node->right->prev = false;
						node = node->parent;
					}
					if (node->parent == nullptr && node->prev) {
						//FUNCTION THAT SANITIZES THE TREE OF THIS ITERATOR HERE
						//if looped to root from a (1-above-leaf) node, then go back to rightmost node, its child is the new current.
						//IE: you have reached end()
						while (node->right != nullptr) {
							node->prev = false;
							//This COULD be set to be a new node that has the same key/value as the root (or something, doesn't matter)
							//this would allow iterating from the back of the data structure. 
							//Though the operator-- function would be similarly labyrinthine...
							//(would be necessary since nullptr nodes can't have parents)
							node = node->right;
							//as-is, this could really be replaced by just setting it to nullptr. But leaving this in just in case.
						}
						node->prev = false;
						node = node->right; //now it's the end! Yay c:
					}
				}
				else {
					//if left child with no children, mark self as previous, go to parent.
					if (node->left != nullptr)
						node->left->prev = false;
					if (node->right != nullptr)
						node->right->prev = false;
					node->prev = true;
					node = node->parent;
				}
			}
			else if (node->left->no_visit()) {
				//if left is visited or does not exist...
				if (node->right != nullptr) {
					//if right exists, go there.
					node->prev = true;
					node = node->right;
					while (node->left != nullptr) {
						//if right node has a left sub-branch go there until there stop being left sub-branches
						node = node->left;
					}
				}
				else {
					// //if right doesn't exist or is visited, go up.
					node->left->prev = false;
					node->prev = true;
					node = node->parent;
				}
			}
			return *this;
		}


		map_iter operator+(int times) { //just run iterate (input) amount of times.
			map_iter tmp = *this;
			for (int i = 0; i < times; i++)
				(*this)++;
			return *this;
		}
        bool operator==(const map_iter& rhs) const {return node == rhs.node;}
        bool operator!=(const map_iter& rhs) const {return node != rhs.node;} 

		key_value<T, E>& operator*() { 
			//so. basically. this just. assigns the values from the current node to the memory pointed to by the shovel attribute
			//then returns said shovel attribute
			//terrible terrible :3c
			if (shovel == nullptr)
				this->shovel = new key_value<T, E>;
			shovel->key = node->key;
			shovel->value = node->value;
		return *shovel; }

		map_iter operator++(int) { map_iter tmp(*this); operator++(); return tmp; }
    private:
        void go_to_begining();
        Node<T, E>* find_next(Node<T, E>* curr);
        Node<T, E>* find_smallest_child(Node<T, E>* curr);
        bool is_node_in_prev_nodes(Node<T, E>* curr);
    };
	//the form of iteration used will lead to undocumented behavior if a map has >1 iterators active at one time. 

    BTree<T, E> container; //our container friend C:

    my_map() : container() { } 
    my_map(const my_map<T, E>& other);
    my_map<T, E>& operator=( const my_map<T, E>& other );

    E& operator[](T search_key); //returns a reference to the key's value.

	//return first node in inorder traversal (one with smallest key, in a binary search tree)
    map_iter begin()
    {
		if (container.root == nullptr) { //if structure is empty, throw it all out.
			throw std::runtime_error("Cannot create iterator in empty data structure");
		}
		Node<T, E>* current = container.root;
		while (current->left != nullptr) { //iterate through left children until there is no left child. Then, current node is least.
			current = current->left; //change current to point to current's left child.
		}
		return map_iter(current);
    }

	//return last inorder traversal node (right child of bottom-right-most node)
    map_iter end()
    {
		Node<T, E>* current = container.root;
		while (current->right != nullptr) { //iterate through left children until there is no left child. Then, current node is least.
			current = current->right; //change current to point to current's left child.
		}
        return map_iter(current->right); //this'll just be nullptr. Is. Is that what we want...? I don't know...
    }

	int null_function();
};

template <typename T, typename E>
ostream& operator<<(ostream& out, const my_map<T, E>& map)
{
    return out;
}

//copy constructor
//deep copy
template <typename T, typename E>
my_map<T, E>::my_map(const my_map<T, E>& other) {
	container = other.container; //binary tree's operator= should be able to handle this.
}

template <typename T, typename E>
my_map<T, E>& my_map<T, E>::operator=(const my_map<T, E>& other) {
	return other;
}

//return a reference to the key's value
//if key doesn't exist yet, create a node with that key, insert it, then return it's value.
template <typename T, typename E>
E& my_map<T,E>::operator[](T search_key)
{
	Node<T, E>* target;
	try {
		//find key.
		target = container.search(search_key);
	}
	catch (std::runtime_error e) {
		//if key does not exist, insert it.
		target = container.insert(search_key); //null SHOULD exist in all classes, right..? All the normal ones, at least... 
	}									
	return target->value;
}


template <typename T, typename E>
Node<T, E>* my_map<T,E>::map_iter::find_next(Node<T, E>* curr)
{
    //this should find the next node in the inorder traversal
}

//check if node has already been visited
//probably more efficient to not use the visited matrix
template <typename T, typename E>
bool my_map<T,E>::map_iter::is_node_in_prev_nodes(Node<T, E>* curr)
{
    //this should check if a node has already been visited
    //you can do this with the prev nodes vector, or find a faster way
}

template <typename T, typename E>
void my_map<T,E>::map_iter::go_to_begining()
{
    //this will go to the beginning of the inorder traversal
}

//finds smallest child of current node
template <typename T, typename E>
Node<T, E>* my_map<T,E>::map_iter::find_smallest_child(Node<T, E>* curr)
{
    return NULL;
}

#endif