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
	if (size() == 0) {
		delete _root;
	} else {
		destructCode(_root->left);
		delete _root;
	}
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

	Elem* root = _root->left;

	while (root) {
		if (key == root->key) {
			if (!root->left && !root->right) {
				delete root;
				_size--;
				return true;
			}
			if (root->left && root->right) {
				Elem* inorderSuccessor = root->right;
				if (!inorderSuccessor->left) {
					if (inorderSuccessor->right) {
						Elem* successorChild = inorderSuccessor->right;
						root->right = successorChild;
					}
					root->key = inorderSuccessor->key;
					root->data = inorderSuccessor->data;
					delete inorderSuccessor;
					inorderSuccessor = nullptr;
					_size--;
					return true;
				} else {
					while (inorderSuccessor->left) {
						inorderSuccessor = inorderSuccessor->left;
					}
					if (inorderSuccessor->right) {
						Elem* childSuccessor = inorderSuccessor->right;
						root->key =  inorderSuccessor->key;
						root->data = inorderSuccessor->data;
						Elem* nodeBeforeLastSuccessor = root->right;
						while (nodeBeforeLastSuccessor->left != inorderSuccessor) {
							nodeBeforeLastSuccessor = nodeBeforeLastSuccessor->left;
						}
						delete inorderSuccessor;
						_size--;
						nodeBeforeLastSuccessor->left = childSuccessor;
						return true;
					}
					// If the inorder successor does not have a right child.
					root->key = inorderSuccessor->key;
					root->data = inorderSuccessor->data;
					delete inorderSuccessor;
					_size--;
					return true;
				}
			}
			if (root->left) {
				Elem* childNode = root->left;
				root->key = childNode->key;
				root->data = childNode->data;
				delete childNode;
				_size--;
				return true;
			}
			// If only a right child.
			Elem* childNode = root->right;
			root->key = childNode->key;
			root->data = childNode->data;
			delete childNode;
			_size--;
			return true;
		}
		if (key < root->key) {
			root = root->left;
		} else if (key > root->key) {
			root = root->right;
		} else {
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
		} else {
			break;
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
	
	while (root->right) {
		root = root->right;
	}
	return Iterator(root);
}


VALUE_TYPE& Map::operator[](KEY_TYPE key) {
	Iterator it = find(key);
	if (((it == end()) && it->key != key) || !&*it) {
		string str = "";
		insert(_root->left, key, str);
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
	if (root->left && root->right) {
		Elem* leftChild = root->left;
		Elem* rightChild = root->right;
		delete root;
		_size--;
		destructCode(leftChild);
		destructCode(rightChild);
	} else if (root->left) {
		Elem* leftChild = root->left;
		delete root;
		_size--;
		destructCode(leftChild);
	} else if (root->right) {
		Elem* rightChild = root->right;
		delete root;
		_size--;
		destructCode(rightChild);
	} else {
		delete root;
		_size--;
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
