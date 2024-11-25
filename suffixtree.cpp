#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>


using namespace std;


struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord = false;
};


class Trie {
public:
    TrieNode* root;


    Trie() {
        root = new TrieNode();
    }


    void insert(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->isEndOfWord = true;
    }


    bool search(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                return false;
            }
            node = node->children[c];
        }
        return node->isEndOfWord;
    }
};


struct SuffixTreeNode {
    unordered_map<char, SuffixTreeNode*> children;
    vector<int> indices; 


    SuffixTreeNode() {}
};


// Suffix Tree Class
class SuffixTree {
public:
    SuffixTreeNode* root;


    SuffixTree(const string& text) {
        root = new SuffixTreeNode();
        buildSuffixTree(text);
    }


    void buildSuffixTree(const string& text) {
        for (int i = 0; i < text.size(); ++i) {
            insertSuffix(text.substr(i), i);
        }
    }


    void insertSuffix(const string& suffix, int index) {
        SuffixTreeNode* node = root;
        for (char c : suffix) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new SuffixTreeNode();
            }
            node = node->children[c];
            node->indices.push_back(index); // Store index of the suffix
        }
    }


    vector<int> search(const string& pattern) {
        SuffixTreeNode* node = root;
        for (char c : pattern) {
            if (node->children.find(c) == node->children.end()) {
                return {}; // Not found
            }
            node = node->children[c];
        }
        return node->indices; 
    }
};


int main() {
    string text = "bananas";
    SuffixTree suffixTree(text);


    string pattern;
    cout << "Enter a pattern to search: ";
    cin >> pattern;


    vector<int> result = suffixTree.search(pattern);


    if (!result.empty()) {
        cout << "Pattern found at indices: ";
        for (int index : result) {
            cout << index << " ";
        }
        cout << endl;
    } else {
        cout << "Pattern not found." << endl;
    }


    return 0;
}
