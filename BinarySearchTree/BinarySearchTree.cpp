#include <iostream>
#include <stack>

#define MAX(a, b) ((a > b)? a: b)

using namespace std;

// Tree Node
class Node {
public:
	int key;
	int height;
	Node* left;
	Node* right;
	Node() {
		height = 0;
		left = right = nullptr;
	}
};
// To do(Insert) : getNode()
Node* getBSTNode() {
	Node* newNode = new Node();
	return newNode;
}

// Binary Search Tree
class BST {
public:
	Node* root;

	BST() { root = nullptr; }
	~BST() { delete root; }
};
void insertBST(BST* tree, int newKey) {
	Node* p = tree->root;
	Node* q = nullptr;
	stack<Node*> stack;

	// find position to insert newKey while sotring parent node on stack
	while(p != nullptr) {
		if(newKey == p->key)
			return;

		q = p;
		stack.push(q);

		if(newKey < p->key)
			p = p->left;
		else
			p = p->right;
	}
	
	// create new node
	Node* newNode = getBSTNode();		// = Node* newNode = new Node();
	newNode->key = newKey;
	
	// insert newNode as a child of q
	if(tree->root == nullptr)
		tree->root = newNode;
	else if(newKey < q->key)
		q->left = newNode;
	else
		q->right = newNode;
	
	// update height while popping parent node from stack
	while(!stack.empty()) {
		q = stack.top(); stack.pop();
		
		if(q->left == nullptr) {
			if(q->right == nullptr)
				q->height = 1;
			else
				q->height = 1 + q->right->height;
		}
		else {
			if(q->right == nullptr)
				q->height = 1 + q->left->height;
			else
				q->height = 1 + MAX(q->left->height, q->right->height);
		}
	}
}
// To do(Delete) : height(T)
int height(Node* root) { return root->height; }
// To do(Delete) : noNodes(T)
int noNodes(Node* root) {
	if(root)
		return 1 + noNodes(root->left) + noNodes(root->right);
	return 0;
}
// To do(Delete) : maxNode(T)
Node* maxNode(Node* node, stack<Node*> &stack) {
	Node* tmpNode = node;
	while(tmpNode->right != nullptr) {
		stack.push(tmpNode);
		tmpNode = tmpNode->right;
	}
	return tmpNode;
}
// To do(Delete) : minNode(T)
Node* minNode(Node* node, stack<Node*> &stack) {
	Node* tmpNode = node;
	while(tmpNode->left != nullptr) {
		stack.push(tmpNode);
		tmpNode = tmpNode->left;
	}
	return tmpNode;
}
// To do(Delete) : deleteBST(T, deleteKey)
void deleteBST(BST* tree, int deleteKey) {
	Node* p  = tree->root;
	Node* q = nullptr;
	stack<Node*> stack;

	// find position of deleteKey while storing parent node on stack
	while(p != nullptr && deleteKey != p->key) {
		q = p;
		stack.push(q);

		if(deleteKey < p->key)
			p = p->left;
		else
			p = p->right;
	}

	// deleteKey was not found
	if(p == nullptr)
		return;

	// case of degree 2 is reduced to case of degree 0 or case of degree 1
	if(p->left != nullptr && p->right != nullptr) {
		stack.push(p);
		Node* tmpNode = p;

		// passing stack for updating node height
		if(height(p->left) < height(p->right))
			p = minNode(p->right, stack);
		else if(height(p->left) > height(p->right))
			p = maxNode(p->left, stack);
		else {
			if(noNodes(p->left) < noNodes(p->right))
				p = minNode(p->right, stack);
			else
				p = maxNode(p->left, stack);
		}

		tmpNode->key = p->key;
		q = stack.top();
	}

	// now degree of p is 0 or 1
	// delete p from T
	if(p->left == nullptr && p->right == nullptr) {	// case of degree 0
		if(q == nullptr) 		// case of root
			tree->root = nullptr;
		else if(q->left == p)
			q->left = nullptr;
		else
			q->right = nullptr;
	}
	else {						// case of degree 1
		if(p->left != nullptr) {
			if(q == nullptr)	// case of root
				tree->root = tree->root->left;
			else if(q->left == p)
				q->left = p->left;
			else
				q->right = p->left;
		}
		else {
			if(q == nullptr)	// case of root
				tree->root = tree->root->right;
			else if(q->left == p)
				q->left = p->right;
			else
				q->right = p->right;
		}
	}

	// Remove Node	
	delete p;

	// update height while popping parent node from stack
	while(!stack.empty()) {
		q = stack.top(); stack.pop();
		
		if(q->left == nullptr) {
			if(q->right == nullptr)
				q->height = 1;
			else
				q->height = 1 + q->right->height;
		}
		else {
			if(q->right == nullptr)
				q->height = 1 + q->left->height;
			else
				q->height = 1 + MAX(q->left->height, q->right->height);
		}
	}
}

// Tree Traversal
void preorder(Node* node) {
	cout << node->key << " ";
	if(node->left != nullptr) preorder(node->left);
	if(node->right != nullptr) preorder(node->right);
}
void inorder(Node* node) {
	if(node->left != nullptr) inorder(node->left);
	cout << node->key << " ";
	if(node->right != nullptr) inorder(node->right);
}
void postorder(Node* node) {
	if(node->left != nullptr) postorder(node->left);
	if(node->right != nullptr) postorder(node->right);
	cout << node->key << " ";
}
// Tree Traversal Function for Binary Search Tree
void preorderBST(BST* tree) {
	if(tree->root != nullptr) {
		preorder(tree->root);
	}
	cout << endl;
}
void inorderBST(BST* tree) {
	if(tree->root != nullptr) {
		inorder(tree->root);
	}
	cout << endl;
}
void postorderBST(BST* tree) {
	if(tree->root != nullptr) {
		postorder(tree->root);
	}
	cout << endl;
}

int main() {
	BST* tree = new BST();
	
	// Insertion
	insertBST(tree, 25); inorderBST(tree);
	insertBST(tree, 500); inorderBST(tree);
	insertBST(tree, 33); inorderBST(tree);
	insertBST(tree, 49); inorderBST(tree);
	insertBST(tree, 17); inorderBST(tree);
	insertBST(tree, 403); inorderBST(tree);
	insertBST(tree, 29); inorderBST(tree);
	insertBST(tree, 105); inorderBST(tree);
	insertBST(tree, 39); inorderBST(tree);
	insertBST(tree, 66); inorderBST(tree);
	insertBST(tree, 305); inorderBST(tree);
	insertBST(tree, 44); inorderBST(tree);
	insertBST(tree, 19); inorderBST(tree);
	insertBST(tree, 441); inorderBST(tree);
	insertBST(tree, 390); inorderBST(tree);
	insertBST(tree, 12); inorderBST(tree);
	insertBST(tree, 81); inorderBST(tree);
	insertBST(tree, 50); inorderBST(tree);
	insertBST(tree, 100); inorderBST(tree);
	insertBST(tree, 999); inorderBST(tree);

	// Delete node pattern 1
	deleteBST(tree, 25); inorderBST(tree);
	deleteBST(tree, 500); inorderBST(tree);
	deleteBST(tree, 33); inorderBST(tree);
	deleteBST(tree, 49); inorderBST(tree);
	deleteBST(tree, 17); inorderBST(tree);
	deleteBST(tree, 403); inorderBST(tree);
	deleteBST(tree, 29); inorderBST(tree);
	deleteBST(tree, 105); inorderBST(tree);
	deleteBST(tree, 39); inorderBST(tree);
	deleteBST(tree, 66); inorderBST(tree);
	deleteBST(tree, 305); inorderBST(tree);
	deleteBST(tree, 44); inorderBST(tree);
	deleteBST(tree, 19); inorderBST(tree);
	deleteBST(tree, 441); inorderBST(tree);
	deleteBST(tree, 390); inorderBST(tree);
	deleteBST(tree, 12); inorderBST(tree);
	deleteBST(tree, 81); inorderBST(tree);
	deleteBST(tree, 50); inorderBST(tree);
	deleteBST(tree, 100); inorderBST(tree);
	deleteBST(tree, 999); inorderBST(tree);

	// T <- null
	tree->root = nullptr;
	
	// Re-insertion
	insertBST(tree, 25); inorderBST(tree);
	insertBST(tree, 500); inorderBST(tree);
	insertBST(tree, 33); inorderBST(tree);
	insertBST(tree, 49); inorderBST(tree);
	insertBST(tree, 17); inorderBST(tree);
	insertBST(tree, 403); inorderBST(tree);
	insertBST(tree, 29); inorderBST(tree);
	insertBST(tree, 105); inorderBST(tree);
	insertBST(tree, 39); inorderBST(tree);
	insertBST(tree, 66); inorderBST(tree);
	insertBST(tree, 305); inorderBST(tree);
	insertBST(tree, 44); inorderBST(tree);
	insertBST(tree, 19); inorderBST(tree);
	insertBST(tree, 441); inorderBST(tree);
	insertBST(tree, 390); inorderBST(tree);
	insertBST(tree, 12); inorderBST(tree);
	insertBST(tree, 81); inorderBST(tree);
	insertBST(tree, 50); inorderBST(tree);
	insertBST(tree, 100); inorderBST(tree);
	insertBST(tree, 999); inorderBST(tree);

	// Delete node pattern 2
	deleteBST(tree, 999); inorderBST(tree);
	deleteBST(tree, 100); inorderBST(tree);
	deleteBST(tree, 50); inorderBST(tree);
	deleteBST(tree, 81); inorderBST(tree);
	deleteBST(tree, 12); inorderBST(tree);
	deleteBST(tree, 390); inorderBST(tree);
	deleteBST(tree, 441); inorderBST(tree);
	deleteBST(tree, 19); inorderBST(tree);
	deleteBST(tree, 44); inorderBST(tree);
	deleteBST(tree, 305); inorderBST(tree);
	deleteBST(tree, 66); inorderBST(tree);
	deleteBST(tree, 39); inorderBST(tree);
	deleteBST(tree, 105); inorderBST(tree);
	deleteBST(tree, 29); inorderBST(tree);
	deleteBST(tree, 403); inorderBST(tree);
	deleteBST(tree, 17); inorderBST(tree);
	deleteBST(tree, 49); inorderBST(tree);
	deleteBST(tree, 33); inorderBST(tree);
	deleteBST(tree, 500); inorderBST(tree);
	deleteBST(tree, 25); inorderBST(tree);

	return 0;
}
