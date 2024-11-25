
#include <iostream>
#include <vector>
using namespace std;

class Node {
    static const int SYMBOLS = 26;
public:
    vector<Node*> children;
    vector<string> edgeLabel;
    bool isEnd;

    Node(bool isEnd) : isEnd(isEnd) {
        children.resize(SYMBOLS, nullptr);
        edgeLabel.resize(SYMBOLS);
    }
};

class Trie {
private:
    Node* root;
    char CASE;

    string strCopy(string str, int index) {
        return str.substr(index);
    }

    void print(Node* node, string str) {
        if (node->isEnd) {
            cout << str << endl;
        }

        for (int i = 0; i < node->edgeLabel.size(); ++i) {
            if (!node->edgeLabel[i].empty()) {
                string temp = str + node->edgeLabel[i];
                print(node->children[i], temp);
            }
        }
    }

public:
    Trie(char CASE = 'a') : CASE(CASE) {
        root = new Node(false);
    }

    void insert(string word) {
        Node* trav = root;
        int i = 0;

        while (i < word.length() && !trav->edgeLabel[word[i] - CASE].empty()) {
            int index = word[i] - CASE;
            int j = 0;
            string label = trav->edgeLabel[index];

            // Traverse through the edge label
            while (j < label.length() && i < word.length() && label[j] == word[i]) {
                ++i;
                ++j;
            }

            // If we reach the end of the edge label, keep traversing
            if (j == label.length()) {
                trav = trav->children[index];
            } else {
                // Split the edge label and add new nodes as necessary
                Node* existingChild = trav->children[index];
                Node* newChild = new Node(i == word.length());

                string remainingLabel = label.substr(j);
                trav->edgeLabel[index] = label.substr(0, j);  // Update current edge label

                trav->children[index] = newChild;  // Set new child for the truncated label
                newChild->edgeLabel[remainingLabel[0] - CASE] = remainingLabel;
                newChild->children[remainingLabel[0] - CASE] = existingChild;

                if (i < word.length()) {
                    string remainingWord = word.substr(i);
                    newChild->edgeLabel[remainingWord[0] - CASE] = remainingWord;
                    newChild->children[remainingWord[0] - CASE] = new Node(true);
                }
                return;
            }
        }

        // If no matching edge, add the remaining word
        if (i < word.length()) {
            trav->edgeLabel[word[i] - CASE] = strCopy(word, i);
            trav->children[word[i] - CASE] = new Node(true);
        } else {
            trav->isEnd = true;  // Mark the current node as a terminal node
        }
    }

    void traverse() {
        print(root, "");
    }

    bool search(string prefix) {
        int i = 0;
        Node* trav = root;

        while (i < prefix.length() && !trav->edgeLabel[prefix[i] - CASE].empty()) {
            int index = prefix[i] - CASE;
            string label = trav->edgeLabel[index];
            int j = 0;

            while (i < prefix.length() && j < label.length()) {
                if (prefix[i] != label[j]) {
                    return false;
                }
                i++;
                j++;
            }

            if (j == label.length()) {
                trav = trav->children[index];
            } else {
                return true;
            }
        }

        return i == prefix.length();
    }
};

int main() {
    Trie trie;

    string words[] = {"bull", "bear", "buy", "bell", "stop", "stock"};

    for (string word : words) {
        trie.insert(word);
    }
    trie.traverse();

    string prefixes[] = {"bull", "be", "see"};
    for (string prefix : prefixes) {
        if (trie.search(prefix)) {
            cout << prefix << " is present\n";
        }
        else {
            cout << prefix << " is not present\n";
        }
    }

    return 0;
}
