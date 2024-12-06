#include <iostream>
using namespace std;

struct Node {
    char value;
    Node* left;
    Node* right;
    Node(char val) : value(val), left(nullptr), right(nullptr) {}
};

void preOrder(Node* node) {
    if (node == nullptr) return;
    cout << node->value << " ";
    preOrder(node->left);
    preOrder(node->right);
}

void inOrder(Node* node) {
    if (node == nullptr) return;
    inOrder(node->left);
    cout << node->value << " ";
    inOrder(node->right);
}

void postOrder(Node* node) {
    if (node == nullptr) return;
    postOrder(node->left);
    postOrder(node->right);
    cout << node->value << " ";
}

int main() {
    Node* root = new Node('+');
    root->left = new Node('-');
    root->right = new Node('+');

    root->left->left = new Node('a');
    root->left->right = new Node('/');
    root->left->right->left = new Node('*');
    root->left->right->right = new Node('c');
    root->left->right->left->left = new Node('5');
    root->left->right->left->right = new Node('b');

    root->right->left = new Node('^');
    root->right->right = new Node('^');
    root->right->left->left = new Node('c');
    root->right->left->right = new Node('8');
    root->right->right->left = new Node('d');
    root->right->right->right = new Node('1/2');

    cout << "Preorder: ";
    preOrder(root);
    cout << endl;

    cout << "Inorder: ";
    inOrder(root);
    cout << endl;

    cout << "Postorder: ";
    postOrder(root);
    cout << endl;

    return 0;
}