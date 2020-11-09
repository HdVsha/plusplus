#include <iostream>


using namespace std;


class AVLNode
{
    friend class AVLTree; // So that we could use everything

private:
    int height;
    AVLNode* parent;
    AVLNode* left;
    AVLNode* right;

public:
    int value;
    AVLNode(int key, AVLNode* left_node=nullptr, AVLNode* right_node=nullptr)
    {
        value = key;
        left = left_node;
        right = right_node;
        height = 0;
    }
    ~AVLNode(){}
};


class AVLTree
{
private:
    AVLNode* root;
    // Types of rotations
    AVLNode* right_rotation(AVLNode* p);
    AVLNode* left_rotation(AVLNode* p);
    // Counting the balance factor
    int bfCount(AVLNode* p);
    // Updating the height where needed
    void  heightUpd(AVLNode* node);
    // Balancing our tree
    AVLNode* balance(AVLNode* p);

    AVLNode* minimum_node_of_tree(AVLNode* node){
        if(node->left == nullptr) return node;
        else return minimum_node_of_tree(node->left);
    }
    // Need this in order to correctly set the heights
    int sub_tree_height(AVLNode* node){return (node != nullptr)?node->height + 1:0;}
    // Inserting the key into the tree
    AVLNode* insert(int key, AVLNode* node);
    // If true, removing the key from the tree
    AVLNode* remove(int key, AVLNode* node);


public:

    AVLTree(){ root = nullptr; }
    ~AVLTree(){}
    void insert(int key){ root = insert(key, root);}
    void remove(int key){ root = remove(key, root);}
    AVLNode* exists(int key, AVLNode* node);
    AVLNode* next(int key, AVLNode* node);
    AVLNode* prev(int key, AVLNode* node);
    AVLNode* getRoot(){ return root; }

};


AVLNode* AVLTree:: right_rotation(AVLNode *p) {
     if (p -> left) {
         AVLNode *new_p = p->left;
         p->left = new_p->right;
         new_p->right = p;
         // Need to upd the heights of the trees
         heightUpd(p);
         heightUpd(new_p);

         return new_p;
     } else { return p; }
}

AVLNode* AVLTree:: left_rotation(AVLNode* p){
    if(p -> right){
        AVLNode* new_p = p->right;
        p->right = new_p->left;
        new_p->left = p;

        heightUpd(p);
        heightUpd(new_p);

        return new_p;
    } else { return p; }
}

int AVLTree:: bfCount(AVLNode* p){
    int height_L = sub_tree_height(p->left);
    int height_R = sub_tree_height(p->right);
    int balance_factor = height_R - height_L;
    return balance_factor;
}

void AVLTree:: heightUpd(AVLNode* node){
    int height_L = sub_tree_height(node->left);
    int height_R = sub_tree_height(node->right);
    node->height = max(height_L, height_R);
}

AVLNode* AVLTree:: insert(int key, AVLNode* node){
    if(node == nullptr){return node = new AVLNode(key);}

    if(key < node->value){node->left = insert(key, node->left);}
    else if(key > node->value){node->right = insert(key, node->right);}
    else if(node->value == key) return node;

    heightUpd(node); // Need to update the height of a parent
    return balance(node);
}

AVLNode* AVLTree:: remove(int key, AVLNode* node)
{
    if(node == nullptr) return node;
    if(key < node->value)
    {
        node->left = remove(key, node->left);
    }
    else if(key > node->value)
    {
        node->right = remove(key, node->right);
    }
    else //if(node->value == key)
    {
        if(node->left == nullptr && node->right == nullptr)
        {
            delete node;
            return nullptr;
        }
        else if(node->left == nullptr && node->right != nullptr)
        {
            AVLNode* sub_right_tree = node->right;
            delete node;
            return sub_right_tree;
        }
        else if(node->left != nullptr && node->right == nullptr)
        {
            AVLNode* sub_left_tree = node->left;
            delete node;
            return sub_left_tree;
        }
        else
        {
            AVLNode* minimum_node_in_sub_left_tree = minimum_node_of_tree(node->right);
            node->value = minimum_node_in_sub_left_tree->value;
            node->right = remove(minimum_node_in_sub_left_tree->value, node->right);
        }
    }
    heightUpd(node);
    return balance(node);
}

AVLNode* AVLTree:: balance(AVLNode* p){
    if (bfCount(p) == 2){
        if (bfCount(p -> right) < 0){p->right = right_rotation(p->right);}
        return left_rotation(p);
    }
    if (bfCount(p) == -2){
        if (bfCount(p -> left) < 0){p->left = left_rotation(p->left);}
        return right_rotation(p);
    }
    return p;
}

AVLNode* AVLTree:: exists(int key, AVLNode* node){
    if (node == nullptr) return node;
    else if (key < node -> value){
        node = exists(key, node -> left);
    }
    else if (key > node -> value){
        node = exists(key, node -> right);
    }
    return node;
}

AVLNode* AVLTree:: next(int key, AVLNode* node){
    AVLNode* current = node;
    AVLNode* successor = nullptr;
    while (current != nullptr){
        if (current -> value > key){
            successor = current;
            current = current -> left;
        }
        else{
            current = current -> right;
        }
    }
    return successor;
}

AVLNode* AVLTree:: prev(int key, AVLNode* node){
    AVLNode* current = node;
    AVLNode* successor = nullptr;
    while (current != nullptr){
        if (current -> value < key){
            successor = current;
            current = current -> right;
        }
        else{
            current = current -> left;
        }
    }
    return successor;
}

void commandParse(const string& command, AVLTree& tree){
    if (command == "insert"){
        int num;
        cin >> num;
        tree.insert(num);
    }
    else if (command == "exists"){
        int num;
        cin >> num;
        if (tree.exists(num, tree.getRoot()) == nullptr) {
            cout << "false" << endl;
        } else { cout << "true" << endl; }
    }
    else if (command == "delete"){
        int num;
        cin >> num;
        tree.remove(num);
    }
    else if (command == "next"){
        int num;
        cin >> num;
        AVLNode* tmp = tree.next(num, tree.getRoot());
        if (tmp == nullptr) {
            cout << "none" << endl;
        } else { cout << tmp -> value << endl; }
    }
    else if (command == "prev"){
        int num;
        cin >> num;
        AVLNode* tmp = tree.prev(num, tree.getRoot());
        if (tmp == nullptr) {
            cout << "none" << endl;
        } else { cout << tmp -> value << endl; }
    }
}


int main()
{
    AVLTree avltree;
    string s;
    while (cin >> s) {
        commandParse(s, avltree);
    }
    return 0;
}
