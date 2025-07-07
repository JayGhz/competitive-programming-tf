#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    struct TSTNode {
        char ch;
        bool isEnd;
        int freq;
        int firstIndex;
        TSTNode *left, *eq, *right;

        TSTNode(char c) {
            ch = c;
            isEnd = false;
            freq = 0;
            firstIndex = -1;
            left = eq = right = nullptr;
        }
    };

    class TernarySearchTree {
    public:
        TSTNode* root = nullptr;
        TSTNode* insert(TSTNode* node, const string& word, int i, int index) {
            char c = word[i];
            if (!node) node = new TSTNode(c);

            if (c < node->ch) {
                node->left = insert(node->left, word, i, index);
            } else if (c > node->ch) {
                node->right = insert(node->right, word, i, index);
            } else {
                if (i + 1 == word.length()) {
                    node->isEnd = true;
                    node->freq++;
                    if (node->firstIndex == -1)
                        node->firstIndex = index;
                } else {
                    node->eq = insert(node->eq, word, i + 1, index);
                }
            }
            return node;
        }
        void insert(const string& word, int index) {
            root = insert(root, word, 0, index);
        }

        void findMax(TSTNode* node, string& current, string& result, int& maxFreq, int& latestFirstIndex) {
            if (!node) return;
            findMax(node->left, current, result, maxFreq, latestFirstIndex);

            current.push_back(node->ch);
            if (node->isEnd) {
                if (node->freq > maxFreq || (node->freq == maxFreq && node->firstIndex > latestFirstIndex)) {
                    result = current;
                    maxFreq = node->freq;
                    latestFirstIndex = node->firstIndex;
                }
            }
            findMax(node->eq, current, result, maxFreq, latestFirstIndex);
            current.pop_back();
            findMax(node->right, current, result, maxFreq, latestFirstIndex);
        }

        string mostFrequentWord() {
            string current = "", result = "";
            int maxFreq = 0, latestFirstIndex = -1;
            findMax(root, current, result, maxFreq, latestFirstIndex);
            return result;
        }
    };

    string mostFrequentWord(string arr[], int n) {
        TernarySearchTree tree;
        for (int i = 0; i < n; ++i) {
            tree.insert(arr[i], i);}
        return tree.mostFrequentWord();}
};

int main() {
    int n;
    cin >> n;

    string* arr = new string[n];
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    Solution sol;
    string resultado = sol.mostFrequentWord(arr, n);
    cout << resultado << endl;
    delete[] arr;
    return 0;
}	
