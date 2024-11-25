#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
using namespace std;

class Node {
public:
    int value;
    Node **forward;

    Node(int level, int value) {
        this->value = value;
        forward = new Node*[level + 1];
        for (int i = 0; i <= level; i++)
            forward[i] = nullptr;
    }

    ~Node() {
        delete[] forward;
    }
};

class SkipList {
private:
    int maxLevel;
    float probability;
    Node *header;

    int randomLevel() {
        int level = 0;
        while ((std::rand() / (RAND_MAX + 1.0)) < probability && level < maxLevel) {
            level++;
        }
        return level;
    }

public:
    SkipList(int maxLevel, float probability) : maxLevel(maxLevel), probability(probability) {
        header = new Node(maxLevel, -1); // Header node with value -1
    }

    ~SkipList() {
        delete header; // Destructor will handle deletion of nodes
    }

    void insert(int value) {
        Node *current = header;
        Node *update[maxLevel + 1];

        // Start from the highest level and find the position to insert
        for (int i = maxLevel; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->value < value) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        current = current->forward[0];

        // If the value is not found, insert it
        if (current == nullptr || current->value != value) {
            int newLevel = randomLevel();
            if (newLevel > maxLevel) {
                newLevel = maxLevel;
            }

            Node *newNode = new Node(newLevel, value);
            for (int i = 0; i <= newLevel; i++) {
                newNode->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = newNode;
            }
        }
    }

    bool search(int value) {
        Node *current = header;

        for (int i = maxLevel; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->value < value) {
                current = current->forward[i];
            }
        }
        current = current->forward[0];

        return (current != nullptr && current->value == value);
    }

    void remove(int value) {
        Node *current = header;
        Node *update[maxLevel + 1];

        for (int i = maxLevel; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->value < value) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        current = current->forward[0];

        if (current != nullptr && current->value == value) {
            for (int i = 0; i <= maxLevel; i++) {
                if (update[i]->forward[i] != current) break;
                update[i]->forward[i] = current->forward[i];
            }
            delete current;
        }
    }

    void display() {
        for (int i = 0; i <= maxLevel; i++) {
            Node *node = header->forward[i];
            cout << "Level " << i << ": ";
            while (node != nullptr) {
                cout << node->value << " ";
                node = node->forward[i];
            }
            cout << std::endl;
        }
    }
};

int main() {
    srand(static_cast<unsigned>(std::time(0))); // Seed for random number generation
    SkipList skiplist(3, 0.5);

    skiplist.insert(3);
    skiplist.insert(6);
    skiplist.insert(7);
    skiplist.insert(9);
    skiplist.insert(12);
    skiplist.insert(19);
    skiplist.insert(17);
    skiplist.insert(26);
    skiplist.insert(21);
    skiplist.insert(25);

    skiplist.display();

    cout << "Search 19: " << (skiplist.search(19) ? "Found" : "Not Found") << endl;
    cout << "Search 15: " << (skiplist.search(15) ? "Found" : "Not Found") << endl;

    skiplist.remove(19);
    cout << "After removing 19:" <<endl;
    skiplist.display();
}
