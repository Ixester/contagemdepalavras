//
//  main.cpp
//  jwick
//
//  Created by Italo Xesteres on 07/05/23.
//
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <unordered_map>

using namespace std;
struct Node {
    string word;
    int count;
    Node* left;
    Node* right;
    int height;
    Node(string w) : word(w), count(1), left(nullptr), right(nullptr), height(1) {}
};
class BST {
private:
    Node* root;
    Node* insertNode(Node* node, string word) {
        if (node == nullptr) {
            return new Node(word);
        }
        if (word < node->word) {
            node->left = insertNode(node->left, word);
        } else if (word > node->word) {
            node->right = insertNode(node->right, word);
        } else {
            node->count++;
        }
        return node;
    }
    int getHeight(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return max(getHeight(node->left), getHeight(node->right)) + 1;
    }
    int countLeaves(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        if (node->left == nullptr && node->right == nullptr) {
            return 1;
        }
        return countLeaves(node->left) + countLeaves(node->right);
    }
public:
    BST() : root(nullptr) {}
    void insert(string word) {
        root = insertNode(root, word);
    }
    int getTotalWords() {
        return getTotalWords(root);
    }
    int getTotalDistinctWords() {
        return getTotalDistinctWords(root);
    }
    int getMinimumTreeHeight() {
        return getMinimumTreeHeight(root);
    }
    int getTreeHeight() {
        return getHeight(root);
    }
    int getNumSheets() {
        return countLeaves(root);
    }
private:
    int getTotalWords(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->count + getTotalWords(node->left) + getTotalWords(node->right);
    }
    int getTotalDistinctWords(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + getTotalDistinctWords(node->left) + getTotalDistinctWords(node->right);
    }
    int getMinimumTreeHeight(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        int leftHeight = getMinimumTreeHeight(node->left);
        int rightHeight = getMinimumTreeHeight(node->right);
        return 1 + min(leftHeight, rightHeight);
    }
};
class AVLTree {
private:
    Node* root;
    Node* insertNode(Node* node, string word) {
        if (node == nullptr) {
            return new Node(word);
        }
        if (word < node->word) {
            node->left = insertNode(node->left, word);
        } else if (word > node->word) {
            node->right = insertNode(node->right, word);
        } else {
            node->count++;
        }
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balanceFactor = getBalanceFactor(node);
        if (balanceFactor > 1 && word < node->left->word) {
            return rotateRight(node);
        }
        if (balanceFactor < -1 && word > node->right->word) {
            return rotateLeft(node);
        }
        if (balanceFactor > 1 && word > node->left->word) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balanceFactor < -1 && word < node->right->word) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }
    Node* rotateRight(Node* node) {
        Node* newRoot = node->left;
        Node* temp = newRoot->right;
        newRoot->right = node;
        node->left = temp;
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        newRoot->height = 1 + max(getHeight(newRoot->left), getHeight(newRoot->right));
        return newRoot;
    }
    Node* rotateLeft(Node* node) {
        Node* newRoot = node->right;
        Node* temp = newRoot->left;
        newRoot->left = node;
        node->right = temp;
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        newRoot->height = 1 + max(getHeight(newRoot->left), getHeight(newRoot->right));
        return newRoot;
    }
    int getBalanceFactor(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }
public:
    AVLTree() : root(nullptr) {}
    void insert(string word) {
        root = insertNode(root, word);
    }
    int getTotalWords() {
        return getTotalWords(root);
    }
    int getTotalDistinctWords() {
        return getTotalDistinctWords(root);
    }
    int getMinimumTreeHeight() {
        return getMinimumTreeHeight(root);
    }
    int getTreeHeight() {
        return getHeight(root);
    }
    int getNumSheets() {
        return countLeaves(root);
    }
private:
    int getHeight(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }
    int getTotalWords(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->count + getTotalWords(node->left) + getTotalWords(node->right);
    }
    int getTotalDistinctWords(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + getTotalDistinctWords(node->left) + getTotalDistinctWords(node->right);
    }
    int getMinimumTreeHeight(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        int leftHeight = getMinimumTreeHeight(node->left);
        int rightHeight = getMinimumTreeHeight(node->right);
        return 1 + min(leftHeight, rightHeight);
    }
    int countLeaves(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        if (node->left == nullptr && node->right == nullptr) {
            return 1;
        }
        return countLeaves(node->left) + countLeaves(node->right);
    }
};
void write(int totalWords, int totalDistinctWords, int minimumHeight, int bstHeight, int bstNumSheets, int avlHeight, int avlNumSheets) {
    cout << "Total number of words: " << totalWords << endl;
    cout << "Total number of distinct words: " << totalDistinctWords << endl;
    cout << "Minimum tree height: " << minimumHeight << endl;
    cout << "BST height: " << bstHeight << endl;
    cout << "Number of BST sheets: " << bstNumSheets << endl;
    cout << "AVL height: " << avlHeight << endl;
    cout << "Number of AVL sheets: " << avlNumSheets << endl;
}
int main() {
    string filePath = ("/Users/italoxesteres/Downloads/Arquivos/mam.txt");
    ifstream inputFile(filePath);
    if (!inputFile) {
        cerr << "Failed to open the input file." << endl;
        return 1;
    }
    BST bst;
    AVLTree avl;
    string word;
    while (inputFile >> word) {
        bst.insert(word);
        avl.insert(word);
    }
    int totalWords = bst.getTotalWords();
    int totalDistinctWords = bst.getTotalDistinctWords();
    int minimumHeight = bst.getMinimumTreeHeight();
    int bstHeight = bst.getTreeHeight();
    int bstNumSheets = bst.getNumSheets();
    int avlHeight = avl.getTreeHeight();
    int avlNumSheets = avl.getNumSheets();

    write(totalWords, totalDistinctWords, minimumHeight, bstHeight, bstNumSheets, avlHeight, avlNumSheets);
    
    return 0;
}


//CountWord


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <unordered_map>
using namespace std;

struct WordFrequency {
    string word;
    int frequency;

    WordFrequency(const string& w, int f) : word(w), frequency(f) {}
};

bool compareWordFrequency(const WordFrequency& wf1, const WordFrequency& wf2) {
    if (wf1.frequency == wf2.frequency) {
        return wf1.word < wf2.word;
    }
    return wf1.frequency > wf2.frequency;
}

class BST {
private:
    struct Node {
        string word;
        int count;
        Node* left;
        Node* right;

        Node(const string& w) : word(w), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

public:
    BST() : root(nullptr) {}

    void insert(const string& word) {
        root = insertNode(root, word);
    }

    void countFrequencies(vector<WordFrequency>& freqList) {
        countFrequenciesHelper(root, freqList);
    }

private:
    Node* insertNode(Node* node, const string& word) {
        if (node == nullptr) {
            return new Node(word);
        }

        if (word < node->word) {
            node->left = insertNode(node->left, word);
        } else if (word > node->word) {
            node->right = insertNode(node->right, word);
        } else {
            node->count++;
        }

        return node;
    }

    void countFrequenciesHelper(Node* node, vector<WordFrequency>& freqList) {
        if (node == nullptr) {
            return;
        }

        countFrequenciesHelper(node->left, freqList);

        freqList.emplace_back(node->word, node->count);

        countFrequenciesHelper(node->right, freqList);
    }
};

int main() {
    string filePath = "/Users/italoxesteres/Downloads/Arquivos/mam.txt";
    ifstream inputFile(filePath);
    if (!inputFile) {
        cerr << "Failed to open the input file." << endl;
        return 1;
    }

    BST bst;

    string word;
    unordered_map<string, int> frequencyMap;
    while (inputFile >> word) {
        bst.insert(word);
        frequencyMap[word]++;
    }

    vector<WordFrequency> freqList;
    for (const auto& pair : frequencyMap) {
        freqList.emplace_back(pair.first, pair.second);
    }

    sort(freqList.begin(), freqList.end(), compareWordFrequency);

    int numWords = min(10, static_cast<int>(freqList.size()));

    cout << "Top " << numWords << " most frequent words:" << endl;
    for (int i = 0; i < numWords; ++i) {
        cout << freqList[i].word << ": " << freqList[i].frequency << endl;
    }

    return 0;
}
