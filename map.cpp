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

// destructor
Map::~Map() {
	destructCode(_root);
}

// assignment
Map& Map::operator=(const Map &rhs) {
	if (this == &rhs) {
		return *this;
	}
	destructCode(_root);
	_size = rhs.size();
	if (_size == 0) {
		copyCode(_root, rhs._root);
	}
	return *this;
}


bool Map::insert(KEY_TYPE key, VALUE_TYPE data) {
	if (size() == 0) {
		Elem* nodeToInsert = new Elem;
		nodeToInsert->key = key;
		nodeToInsert->data = data;
		_root->left = nodeToInsert;
		_size++;
		return true;
	}
	return insert(_root->left, key, data);
}


bool Map::erase(KEY_TYPE key) {
	Iterator it = find(key);

	if ((it == end()) && (it->key == key)) {
		delete &*it;
		_size--;
		return true;
	}
	if (it == end()) {
		return false;
	}
	if (!it->left && !it->right) {	// if no children
		delete &*it;
		_size--;
		return true;
	}
	if (!it->left) {
		Elem* tempNode = &*it;
		tempNode = tempNode->right;
		delete &*it;
		_size--;
		return true;
	}
	if (!it->right) {
		Elem* tempNode = &*it;
		tempNode = tempNode->left;
		delete &*it;
		_size--;
		return true;
	}
	Elem* tempNode = &*it;
	tempNode = tempNode->right;
	while (tempNode->left != nullptr) {
		tempNode = tempNode->left;
	}
	it->key = tempNode->key;
	it->data = tempNode->data;
	delete tempNode;
	_size--;
	return true;
}


int Map::size() const{
	return _size;
}


Map::Iterator Map::find(KEY_TYPE key) const{
	if (_size == 0) {
		return Iterator();
	}

	Elem* root = _root->left;

	while (root->key != key) {
		if ((root->key > key) && (root->left)) {
			if (root->left->key < key) {
				return end();
			}
			root = root->left;
		} else if ((root->key < key) && (root->right)) {
			if (root->right->key > key) {
				return end();
			}
			root = root->right;
		} else {
			return end();
		}
	}
	return Iterator(root);
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

	Elem* root = _root->left;

	while (root->right != nullptr) {
		root = root->right;
	}
	return Iterator(root);
}


VALUE_TYPE& Map::operator[](KEY_TYPE key) {
	if (find(key) == end()) {
		string str = "";
		insert(key, str);
		Iterator it = find(key);
		return it->data;
	}
	Iterator it = find(key);
	return it->data;
}


Map::Elem& Map::Iterator::operator*() {
	return *_cur;
}


Map::Elem* Map::Iterator::operator->() {
	return _cur;
}


bool Map::Iterator::operator==(Iterator it) const {
	if ((_cur->key == it->key) && (_cur->data == it->data)) {
		return true;
	}
	return false;
}


bool Map::Iterator::operator!=(Iterator it) const {
	if ((_cur->key != it->key) && (_cur->data != it->data)) {
		return true;
	}
	return false;
}


bool Map::insert(Elem *& root, const KEY_TYPE& key, const VALUE_TYPE& data) {
	if (key == root->key) {
		return false;
	}

	if ((key < root->key) && (!root->left)) {
		Elem* nodeToInsert = new Elem;
		nodeToInsert->key = key;
		nodeToInsert->data = data;
		root->left = nodeToInsert;
		_size++;
		return true;
	}
	if ((key < root->key) && (root->left)) {
		insert(root->left, key, data);
	}

	if ((key > root->key) && (!root->right)) {
		Elem* nodeToInsert = new Elem;
		nodeToInsert->key = key;
		nodeToInsert->data = data;
		root->right = nodeToInsert;
		_size++;
		return true;
	}
	if ((key > root->key) && (root->right)) {
		insert(root->right, key, data);
	}
	return false;
}


void Map::destructCode(Elem *& root) {
	if (size() == 0) {
		delete root;
	} else {
		Elem* tempRoot = root;
		delete root;
		_size--;
		if (tempRoot->left) {
			destructCode(tempRoot->left);
		}
		if (tempRoot->right) {
			destructCode(tempRoot->right);
		}
	}
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
