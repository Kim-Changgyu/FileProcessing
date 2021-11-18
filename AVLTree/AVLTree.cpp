#include <iostream>
#include <stack>

#define MAX(a, b) ((a<b)? b: a)

using namespace std;

// AVL Tree Node
class AVLNode {
public:
	int key, address, height, bf;
	AVLNode *left, *right;
};

// Return a new AVL Node
AVLNode *getAVLNode() {
	AVLNode* node = new AVLNode();
	node->height = 1;
	node->bf = 0;
	node->left = node->right = nullptr;
	
	return node;
}

// Using global variable
AVLNode* p = nullptr;
AVLNode* q = nullptr;
AVLNode* x = nullptr;
AVLNode* f = nullptr;
stack<AVLNode*> s;

// AVLTree has a pointer of root
class AVLTree {
public:
	AVLNode *root;
};

// Return the height of T
int height(AVLNode* T) {
	return T->height;
}

// update AVLNode's height & balance factor
void updateNode(AVLNode* node) {
	if(node == nullptr)
		return;

	// check child node
	if(node->left != nullptr || node->right != nullptr) {
		if(node->right == nullptr) {
			node->height = 1 + node->left->height;
			node->bf = node->left->height;
		}
		else if(node->left == nullptr) {
			node->height = 1 + node->right->height;
			node->bf = -(node->right->height);
		}
		else {
			node->height = 1 + MAX(node->left->height, node->right->height);
			node->bf = node->left->height - node->right->height;
		}
	}
	else if(node->left == nullptr && node->right == nullptr) {
		node->height = 1;
		node->bf = 0;
	}
}

/*
 * T: An AVL tree
 * x: root node of subtree
 * f: parent node of x
 */
void rotateLL(AVLTree* T) {
	bool leftChild = f->left == x;
	bool rootCheck = x == f;

	if(rootCheck) {				// root case
		AVLNode* tmp = x->left;
		x->left = tmp->right;
		tmp->right = x;
		T->root = tmp;
	}
	else {
		if(leftChild) {
			f->left = x->left;
			x->left = x->left->right;
			f->left->right = x;
		}
		else {
			f->right = x->left;
			x->left = x->left->right;
			f->right->right = x;
		}
	}

	// updateNode : Height & Balance Factor
	updateNode(x);
	updateNode(f->left);
	updateNode(f->right);
	updateNode(f);
	updateNode(T->root);
}
void rotateRR(AVLTree* T) {
	bool leftChild = f->left == x;
	bool rootCheck = x == f;

	if(rootCheck) {				// root case
		AVLNode* tmp = x->right;
		x->right = tmp->left;
		tmp->left = x;
		T->root = tmp;
	}
	else {
		if(leftChild) {
			f->left = x->right;
			x->right = x->right->left;
			f->left->left = x;
		}
		else {
			f->right = x->right;
			x->right = x->right->left;
			f->right->left = x;
		}
	}

	// updateNode : Height & Balance Factor
	updateNode(x);
	updateNode(f->right);
	updateNode(f->left);
	updateNode(f);
	updateNode(T->root);
}
void rotateLR(AVLTree* T) {
	bool leftChild = f->left == x;
	bool rootCheck = x == f;

	AVLNode* tmp = x->left->right;
	if(tmp->left == nullptr && tmp->right == nullptr) {
		x->left->right = nullptr;
		tmp->left = x->left;
		tmp->right = x;
		x->left = nullptr;
	}
	else {
		x->left->right = tmp->left;
		tmp->left = x->left;
		x->left = tmp->right;
		tmp->right = x;
	}

	if(rootCheck) {				// root case
		T->root = tmp;
	}
	else {
		if(leftChild)
			f->left = tmp;
		else
			f->right = tmp;
	}

	// updateNode : Height & Balance Factor
	updateNode(tmp->left);
	updateNode(tmp->right);
	updateNode(tmp);
	updateNode(f);
	updateNode(T->root);
}
void rotateRL(AVLTree* T) {
	bool leftChild = f->left == x;
	bool rootCheck = x == f;

	AVLNode* tmp = x->right->left;
	if(tmp->left == nullptr && tmp->right == nullptr) {
		x->right->left = nullptr;
		tmp->left = x;
		tmp->right = x->right;
		x->right = nullptr;
	}
	else {
		x->right->left = tmp->right;
		tmp->right = x->right;
		x->right = tmp->left;
		tmp->left = x;
	}


	if(rootCheck) {				// root case
		T->root = tmp;
	}
	else {
		if(leftChild)
			f->left = tmp;
		else
			f->right = tmp;
	}

	// updateNode : Height & Balance Factor
	updateNode(tmp->left);
	updateNode(tmp->right);
	updateNode(tmp);
	updateNode(f);
	updateNode(T->root);
}
// TO DO : rotateTree(T, rotationType) (p, q -> global var)
void rotateTree(AVLTree* T, string rotationType) {
	if(rotationType == "LL")
		rotateLL(T);
	else if(rotationType == "LR")
		rotateLR(T);
	else if(rotationType == "RL")
		rotateRL(T);
	else if(rotationType == "RR")
		rotateRR(T);
	else
		return;
}
// TO DO : inserBST(T, newKey) (Using Same code BST)
void insertBST(AVLTree* T, int newKey) {
	p = T->root;
	q = nullptr;
	// stack = [];
	while(!s.empty())
		s.pop();

	// find position to insert newKey while storing parent node on stack
	while(p != nullptr) {
		if(newKey == p->key)
			return;

		q = p;
		s.push(q);

		if(newKey < p->key)
			p = p->left;
		else
			p = p->right;
	}

	// create new Node
	AVLNode* y = getAVLNode();
	y->key = newKey;

	// insert y as a child of q
	if(T->root == nullptr)
		T->root = y;
	else if(newKey < q->key)
		q->left = y;
	else
		q->right = y;
}
// Insert newKey into insertAVL
string checkBalance(AVLTree* T) {
	x = nullptr;
	f = nullptr;

	// update height and balancing factor while popping parent node from stack
	while(!s.empty()) {
		q = s.top(); s.pop();
		
		updateNode(q);
		
		if(1 < q->bf or q->bf < -1) {
			if(x == nullptr) {
				x = q;
				
				if(s.empty())
					f = T->root;
				else
					f = s.top();
			}
		}
	}
	
	// if there's no problem, return
	if(x == nullptr) {
		return "NO";
	}
	
	// rebalance tree
	if(1 < x->bf) {
		if(x->left->bf < 0) {
			rotateTree(T, "LR");	
			return "LR";
		}
		else {
			rotateTree(T, "LL");
			return "LL";
		}
	}
	else {
		if(x->right->bf > 0) {
			rotateTree(T, "RL");
			return "RL";
		}
		else {
			rotateTree(T, "RR");
			return "RR";
		}
	}
}
void insertAVL(AVLTree* T, int newKey) {
	insertBST(T, newKey);
	cout << checkBalance(T) << " ";
}

// Using deleteBST Code
int noNodes(AVLNode* node) {
	if(node)
		return 1 + noNodes(node->left) + noNodes(node->right);
	return 0;
}
AVLNode *maxNode(AVLNode* node) {
	AVLNode* tmpNode = node;
	while(tmpNode->right != nullptr) {
		s.push(tmpNode);
		tmpNode = tmpNode->right;
	}
	return tmpNode;
}
AVLNode *minNode(AVLNode* node) {
	AVLNode* tmpNode = node;
	while(tmpNode->left != nullptr) {
		s.push(tmpNode);
		tmpNode = tmpNode->left;
	}
	return tmpNode;
}
void deleteBST(AVLTree* T, int deleteKey) {
	p = T->root;
	q = nullptr;
	if(!s.empty())
		s.pop();

	while(p != nullptr && deleteKey != p->key) {
		q = p;
		s.push(q);

		if(deleteKey < p->key)
			p = p->left;
		else
			p = p->right;
	}

	if(p == nullptr)
		return;

	if(p->left != nullptr && p->right != nullptr) {
		s.push(p);
		AVLNode* tmpNode = p;

		if(height(p->left) < height(p->right))
			p = minNode(p->right);
		else if(height(p->left) > height(p->right))
			p = maxNode(p->left);
		else {
			if(noNodes(p->left) <= noNodes(p->right))
				p = minNode(p->right);
			else
				p = maxNode(p->left);
		}

		tmpNode->key = p->key;
		q = s.top();
	}

	if(p->left == nullptr && p->right == nullptr) {
		if(q == nullptr)
			T->root = nullptr;
		else if(q->left == p)
			q->left = nullptr;
		else
			q->right = nullptr;
	}
	else {
		if(p->left != nullptr) {
			if(q == nullptr)
				T->root = T->root->left;
			else if(q->left == p)
				q->left = p->left;
			else
				q->right = p->left;
		}
		else {
			if(q == nullptr)
				T->root = T->root->right;
			else if(q->left == p)
				q->left = p->right;
			else
				q->right = p->right;
		}
	}

	delete p;
}
// Delete deleteKey from T
void deleteAVL(AVLTree* T, int deleteKey) {
	deleteBST(T, deleteKey);
	cout << checkBalance(T) << " ";
}

void inorder(AVLNode* node) {
	if(node != nullptr) {
		inorder(node->left);
		cout << node->key << " ";
		inorder(node->right);
	}
}
void inorderBST(AVLTree* T) {
	inorder(T->root);
}

int main() {
	int testCases[] = {40, 11, 77, 33, 20, 90, 99, 70, 88, 80, 66, 10, 22, 30, 44, 55, 50, 60, 25, 49};

	AVLTree* T = new AVLTree();
	T->root = nullptr;

	for(int i = 0; i < 20; i++) {
		insertAVL(T, testCases[i]);
		inorderBST(T);
		cout << endl;
	}

	for(int i = 0; i < 20; i++) {
		deleteAVL(T, testCases[i]);
		inorderBST(T);
		cout << endl;
	}
	
	for(int i = 0; i < 20; i++) {
		insertAVL(T, testCases[i]);
		inorderBST(T);
		cout << endl;
	}

	for(int i = 19; i >= 0; i--) {
		deleteAVL(T, testCases[i]);
		inorderBST(T);
		cout << endl;
	}

	delete T;

	return 0;
}
