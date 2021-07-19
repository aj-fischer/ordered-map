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
		Elem* nodeToInsert = new Elem(key, val);
		_root->left = nodeToInsert;
		_size++;
		return true;
	}
	
	_cur = _root->left;

	if (find(key) != end()) {
		return false;
	} else {
		Elem* nodeToInsert = new Elem(key, val);
		while (true) {
			if (key < _cur->key) {
				if (!_cur->left) {
					_cur->left = nodeToInsert;
					_size++;
					return true;
				}
				_cur = _cur->left;
			} else {
				if (!_cur->right) {
					_cur->right = nodeToInsert;
					_size++;
					return true;
				}
				_cur = _cur->right;
			}
		}
	}
}


int Map::size() {
	return _size;
}


Iterator Map::find(KEY_TYPE key) {
	if (_size == 0) {
		return;
	}

	_cur = _root->left;
	while (_cur->key != key) {
		if (_cur->key > key) {
			_cur = _cur->left;
		} else if (_cur->key < key) {
			_cur = _cur->right;
		} else {
			return end();
		}
	}
	return Iterator(_cur);
}


Iterator Map::begin() {
	if (_size == 0) {
		return;
	}
	
	return Iterator(_root->left);
}


Iterator Map::end() {
	if (_size == 0) {
		return;
	}

	while (_cur->right != nullptr) {
		_cur = _cur->right;
	}
	return Iterator(_cur);
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
