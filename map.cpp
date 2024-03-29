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
	copyCode(_root, rhs._root);
	_size = rhs.size();
	return *this;
}


bool Map::insert(KEY_TYPE key, VALUE_TYPE data) {
	if (size() == 0) {
		Elem* nodeToInsert = new Elem;
		nodeToInsert->key = key;
		nodeToInsert->data = data;
		_root->left = nodeToInsert;
		nodeToInsert->left = nullptr;
		nodeToInsert->right = nullptr;
		_size++;
		return true;
	}
	return insert(_root->left, key, data);
}


bool Map::erase(KEY_TYPE key) {
	if (size() == 0) {
		return false;
	}

	Elem* parent = _root;
	Elem* root = _root->left;

	while (root) {
		if (key == root->key) {
			if (!root->left && !root->right) {
				if (parent->left == root) {
					delete root;
					parent->left = nullptr;
				} else {
					delete root;
					parent->right = nullptr;
				}
			}
			else if (root->left && root->right) {
				Elem* inorderSuccessor = root->right;
				if (!inorderSuccessor->left) {
					if (inorderSuccessor->right) {
						Elem* successorChild = inorderSuccessor->right;
						root->right = successorChild;
					}
					root->key = inorderSuccessor->key;
					root->data = inorderSuccessor->data;
					delete inorderSuccessor;
					root->right = nullptr;
				} else {
					Elem* parent = root->right;
					inorderSuccessor = inorderSuccessor->left;
					while (inorderSuccessor->left) {
						inorderSuccessor = inorderSuccessor->left;
						parent = parent->left;
					}
					if (inorderSuccessor->right) {
						Elem* childSuccessor = inorderSuccessor->right;
						root->key =  inorderSuccessor->key;
						root->data = inorderSuccessor->data;
						delete inorderSuccessor;
						parent->left = childSuccessor;
					} else if (!inorderSuccessor->right) {
						root->key = inorderSuccessor->key;
						root->data = inorderSuccessor->data;
						delete inorderSuccessor;
						parent->left = nullptr;
					} else {
						break;
					}
				}
			} else if (root->left) {
				Elem* leftChild = root->left;
				root->key = leftChild->key;
				root->data = leftChild->data;
				if (leftChild->left && leftChild->right) {
					Elem* leftTree = leftChild->left;
					Elem* rightTree = leftChild->right;
					delete leftChild;
					root->left = leftTree;
					root->right = rightTree;
				}
				else if (leftChild->left) {
					Elem* leftTree = leftChild->left;
					delete leftChild;
					root->left = leftTree;
				} else if (leftChild->right) {
					Elem* rightTree = leftChild->right;
					delete leftChild;
					root->left = rightTree;
				} else {
					delete leftChild;
					root->left = nullptr;
				}
			} else if (root->right) {
				Elem* rightChild = root->right;
				root->key = rightChild->key;
				root->data = rightChild->data;
				if (rightChild->left && rightChild->right) {
					Elem* leftTree = rightChild->left;
					Elem* rightTree = rightChild->right;
					delete rightChild;
					root->right = rightTree;
					root->left = leftTree;
				} else if (rightChild->left) {
					Elem* leftTree = rightChild->left;
					delete rightChild;
					root->right = leftTree;
				} else if (rightChild->right) {
					Elem* rightTree = rightChild->right;
					delete rightChild;
					root->right = rightTree;
				} else {
					delete rightChild;
					root->right = nullptr;
				}
			}
			_size--;
			return true;
		} else if (key < root->key) {
			parent = root;
			root = root->left;
		} else if (key > root->key) {
			parent = root;
			root = root->right;
		}
		else {
			break;
		}
	}
	return false;
}


int Map::size() const{
	return _size;
}


Map::Iterator Map::find(KEY_TYPE key) const{
	if (size() == 0) {
		return end();
	}

	Elem* root = _root->left;

	while (root) {
		if (key < root->key) {
			root = root->left;
		} else if (key > root->key) {
			root = root->right;
		} else if (key == root->key) {
			return Iterator(root);
		} else {
			break;
		}
	}
	return end();
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
	
	while (root->right) {
		root = root->right;
	}
	return Iterator(root->right);
}


VALUE_TYPE& Map::operator[](KEY_TYPE key) {
	Iterator it = find(key);
	if (it == end()) {
		string str = "";
		insert(key, str);
		Iterator newIt = find(key);
		return newIt->data;
	}
	return it->data;
}


Map::Elem& Map::Iterator::operator*() {
	return *_cur;
}


Map::Elem* Map::Iterator::operator->() {
	return _cur;
}


bool Map::Iterator::operator==(Iterator it) const {
	if (_cur == &*it) {
		return true;
	}
	return false;
}


bool Map::Iterator::operator!=(Iterator it) const {
	if (_cur != &*it) {
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
		nodeToInsert->left = nullptr;
		nodeToInsert->right = nullptr;
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
		nodeToInsert->left = nullptr;
		nodeToInsert->right = nullptr;
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
		while ((root->left) && (size() != 0)) {
			erase(root->left->key);
		}
		delete _root;
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
