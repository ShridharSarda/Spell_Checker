#ifndef TRIE_H
#define TRIE_H

#include <string>
using namespace std;

struct TrieNode {
    TrieNode* children[26];
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < 26; i++)
            children[i] = nullptr;
    }
};

class Trie {
public:
    Trie(); 
    void insert(const string &word);
    bool search(const string &word);
private:
    TrieNode* root;
};

#endif
