// A non-generic Map ADT implemented with a BST data structure
// The BST is not-balanced and non-threaded
#include "map.h"

Map::Map(){
	// create a dummy root node and set up an empty tree
	_root = new Elem;
	_root->left = _root;  
	_root->right = 0;
	_size = 0;

}

// copy constructor
Map::Map(const Map &v){
	// if empty tree
	if (v._root == v._root->left){
		_root = new Elem;
		_root->left = _root;  // empty tree
		_root->right = 0;
		_size = 0;
	} else {
		_root = new Elem;
		_root->left = _root;
		_root->right = 0;
		copyCode(_root->left, v._root->left);
		_size = v._size;
	}
}

bool Map::insert(KEY_TYPE key, VALUE_TYPE val) {
	if (_root->left == _root) {
		Elem* nodeToInsert = new Elem;
		nodeToInsert->key = key;
		nodeToInsert->data = val;
		_root->left = nodeToInsert;
		_size++;
		return true;
	}
	
	Elem* parent = _root->left;

	if (find(key) != end()) {
		return false;
	} else {
		Elem* nodeToInsert = new Elem;
		nodeToInsert->key = key;
		nodeToInsert->data = val;
		while (true) {
			if (key < parent->key) {
				if (!parent->left) {
					parent->left = nodeToInsert;
					_size++;
					return true;
				}
				parent = parent->left;
			} else {
				if (!parent->right) {
					parent->right = nodeToInsert;
					_size++;
					return true;
				}
				parent = parent->right;
			}
		}
	}
}


bool Map::erase(KEY_TYPE key) {
	Iterator it = find(key);

	if (it == end()) {
		return false;
	}
	if (size() == 1) {
		delete *it;
		_root->left = _root;
		return true;
	}
	if (!it->left && !it->right) {	// if no children
		delete *it;
		return true;
	}
	if (!it->left) {
		Elem* tempNode = *it;
		tempNode = tempNode->right;
		delete *it;
		return true;
	}
	if (!it->right) {
		Elem* tempNode = *it;
		tempNode = tempNode->left;
		delete *it;
		return true;
	}
	Elem* tempNode = *it;
	tempNode = tempNode->right;
	while (tempNode->left != nullptr) {
		tempNode = tempNode->left;
	}
	*it->key = tempNode->key;
	*it->data = tempNode->data;
	delete tempNode;
	return true;
}


int Map::size() const{
	return _size;
}


Map::Iterator Map::find(KEY_TYPE key) const{
	if (_size == 0) {
		return Iterator();
	}

	Elem* parent = _root->left;
	while (parent->key != key) {
		if (parent->key > key) {
			parent = parent->left;
		} else if (parent->key < key) {
			parent = parent->right;
		} else {
			return end();
		}
	}
	return Iterator(parent);
}


Map::Iterator Map::begin() const{
	if (_size == 0) {
		return Iterator();
	}
	
	return Iterator(_root->left);
}


Map::Iterator Map::end() const{
	if (_size == 0) {
		return Iterator();
	}

	Elem* parent = _root->left;

	while (parent->right != nullptr) {
		parent = parent->right;
	}
	return Iterator(parent);
}


Elem& Map::Iterator::operator*() {
	return *_cur;
}


Elem* Map::Iterator::operator->() {
	return &_cur;
}


bool Map::Iterator::operator==(Iterator it) const {
	if (_cur == *it) {
		return true;
	}
	return false;
}


// common copy code for deep copy a tree
void  Map::copyCode(Elem* &newRoot, Elem* origRoot){
	if (origRoot == 0)
		newRoot = 0;
	else{
		newRoot = new Elem;
		newRoot->key = origRoot->key;
		newRoot->data = origRoot->data;
		copyCode(newRoot->left, origRoot->left);
		copyCode(newRoot->right, origRoot->right);
	}
}

// 
//  Do Not Modify Below Here
//
//
// output the structure of tree. The tree is output as "lying down"
// in which _root is the LEFT most Elem.
void Map::printTree(ostream& out, int level, Elem *p) const{
	int i;
	if (p) {
		printTree(out, level+1, p->right);
		for(i=0;i<level;i++) {
			out << "\t";
		}
		out << p->key << " " << p->data << '\n';
		printTree(out, level+1, p->left);
	}
}

// outputs information in tree
ostream& Map::dump(ostream& out) const{
	if ( _root == _root->left) { // tree empty
		return out;
	}
	printTree(out, 0, _root->left);   // print tree structure
	return out;
}

// outputs using overloaded << operator
ostream& operator<< (ostream& out, const Map& v){
	v.dump(out);
	return out;
}
