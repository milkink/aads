#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


class BTreeNode {
public:
    int *keys; // Array of keys
    int t;  // Minimum degree (defines the range for number of keys)
    BTreeNode **C; // Array of child pointers
    int n;   // Current number of keys
    bool leaf; // True if leaf node
    BTreeNode(int _t, bool _leaf);
    void traverse();
    BTreeNode *search(int k);
    void insertNonFull(int k);
    void splitChild(int i, BTreeNode *y);
};


class BTree {
public:
    BTreeNode *root;
    int t; // Minimum degree
    BTree(int _t) {
        root = nullptr;
        t = _t;
    }
    void traverse() {
        if (root != nullptr) root->traverse();
    }
    BTreeNode *search(int k) {
        return (root == nullptr) ? nullptr : root->search(k);
    }
    void insert(int k);
};


BTreeNode::BTreeNode(int _t, bool _leaf) {
    t = _t;
    leaf = _leaf;
    keys = new int[2 * t - 1];
    C = new BTreeNode *[2 * t];
    n = 0;
}


void BTreeNode::traverse() {
    for (int i = 0; i < n; i++) {
        if (!leaf) C[i]->traverse();
        cout << " " << keys[i];
    }
    if (!leaf) C[n]->traverse();
}


BTreeNode *BTreeNode::search(int k) {
    int i = 0;
    while (i < n && k > keys[i]) i++;
    if (i < n && keys[i] == k) return this;
    if (leaf) return nullptr;
    return C[i]->search(k);
}


void BTreeNode::insertNonFull(int k) {
    int i = n - 1;
    if (leaf) {
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
        n++;
    } else {
        while (i >= 0 && keys[i] > k) i--;
        if (C[i + 1]->n == 2 * t - 1) {
            splitChild(i + 1, C[i + 1]);
            if (keys[i + 1] < k) i++;
        }
        C[i + 1]->insertNonFull(k);
    }
}


void BTreeNode::splitChild(int i, BTreeNode *y) {
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;
    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];
    if (!y->leaf) {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }
    y->n = t - 1;
    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];
    C[i + 1] = z;
    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];
    keys[i] = y->keys[t - 1];
    n++;
}


void BTree::insert(int k) {
    if (root == nullptr) {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    } else {
        if (root->n == 2 * t - 1) {
            BTreeNode *s = new BTreeNode(t, false);
            s->C[0] = root;
            s->splitChild(0, root);
            int i = 0;
            if (s->keys[0] < k) i++;
            s->C[i]->insertNonFull(k);
            root = s;
        } else {
            root->insertNonFull(k);
        }
    }
}


int main() {
    BTree t(3); // A B-tree with a minimum degree of 3
    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(6);
    t.insert(12);
    t.insert(30);
    t.insert(7);
    t.insert(17);


    cout << "Traversal of the B-tree is:\n";
    t.traverse();


    int key = 6;
    (t.search(key) != nullptr) ? cout << "\nFound key " << key << endl : cout << "\nKey " << key << " not found." << endl;


    return 0;
}
