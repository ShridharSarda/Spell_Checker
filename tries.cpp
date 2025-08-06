#include "trie.h"
#include <cctype>

Trie::Trie() {
    root = new TrieNode();
}

void Trie::insert(const string &word) {
    TrieNode* node = root;
    for (char c : word) {
        if (!isalpha(c)) continue; // ignore non-letters
        c = tolower(c);
        int index = c - 'a';
        if (!node->children[index])
            node->children[index] = new TrieNode();
        node = node->children[index];
    }
    node->isEndOfWord = true;
}

bool Trie::search(const string &word) {
    TrieNode* node = root;
    for (char c : word) {
        if (!isalpha(c)) continue;
        c = tolower(c);
        int index = c - 'a';
        if (!node->children[index])
            return false;
        node = node->children[index];
    }
    return node->isEndOfWord;
}
