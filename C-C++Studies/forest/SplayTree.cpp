#include <iostream>
using namespace std;

// basic node structure
struct node {
    int key;
    node *left, *right;
    node* parent;

    node(int init) : key(init), left(nullptr), right(nullptr), parent(nullptr) {}
    ~node() {}
};

class SplayTree {
public:
    node* root;

    SplayTree() : root(nullptr) {}

    // left rotation helper function used to splay
    // This will make more sense if you follow along
    // from the splay function.
    // Here x can refer to either the parent or grandparent node.
    void left_rotate(node *x);
    // right rotation helper function used to splay
    void right_rotate(node *x);
    // the splay function moves the accessed node up the tree
    void splay(node *x);
    // find a key
    node* find(int key);
    void insert(int key);
};


void SplayTree:: left_rotate(node *x) {
    node *r = x->right;
    if (r) {
        x->right = r->left;
        if (r->left)
            r->left->parent = x;
        r->parent = x->parent;
    }
    if (!x->parent)
        root = r;
    else if (x == x->parent->left)
        x->parent->left = r;
    else
        x->parent->right = r;

    if (r)
        r->left = x;

    x->parent = r;
}


void SplayTree:: right_rotate(node *x) {
    node *l = x->left;
    if (l) {
        x->left = l->right;
        if (l->right)
            l->right->parent = x;
        l->parent = x->parent;
    }
    if (!x->parent)
        root = l;
    else if (x == x->parent->left)
        x->parent->left = l;
    else
        x->parent->right = l;
    if (l)
        l->right = x;

    x->parent = l;
}


void SplayTree:: splay(node *x) {
    while (x->parent){
        // if no grandparent: zig operation
        if (!x->parent->parent) {
            if (x->parent->left == x)
                right_rotate(x->parent);
            else
                left_rotate(x->parent);
        }
            // when grandparent exists:
            // Node exist at left of the left node: zig-zig
        else if (x->parent->left == x && x->parent->parent->left == x->parent) {
            right_rotate(x->parent->parent);
            right_rotate(x->parent);
            // Node exist at right of the right node: zag-zag
        } else if (x->parent->right == x && x->parent->parent->right == x->parent) {
            left_rotate(x->parent->parent);
            left_rotate(x->parent);
        }
            // Node exist at right of grandparent and left of parent:
            // zig-zag
        else if (x->parent->left == x && x->parent->parent->right == x->parent) {
            right_rotate(x->parent);
            left_rotate(x->parent);
        }
            // Node exist at left of grandparent and right of parent:
            // zag-zig
        else {
            left_rotate(x->parent);
            right_rotate(x->parent);
        }
    }
}


node* SplayTree:: find(int key) {
    node *z = root;
    while (z) {
        if (z->key < key)
            z = z->right;
        else if (key < z->key)
            z = z->left;
        else {
            splay(z);
            return z;
        }
    }
    return nullptr;
}


void SplayTree:: insert(int key) {
    node *z = root;
    node *p = nullptr;

    while (z) {
        p = z;
        if (z->key < key)
            z = z->right;
        else
            z = z->left;
    }

    z = new node(key);
    z->parent = p;

    if (!p)
        root = z;
    else if (p->key < z->key)
        p->right = z;
    else
        p->left = z;

    splay(z);
}


int main() {
    // please feel free to use the insert or
    // find operations and observe the results
    SplayTree *tree = new SplayTree();
    tree->insert(5);
    tree->insert(4);
    tree->insert(1);
    tree->insert(6);

    cout << "Root before find operation: " << tree->root->key <<endl;

    tree->find(4);

    cout << "Root after find operation: "  <<tree->root->key <<endl;

    return 0;
}