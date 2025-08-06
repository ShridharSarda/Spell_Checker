Trie-based Spell Checker
This project is a simple spell checker that uses a Trie (prefix tree) for fast dictionary lookups and an unordered_set for generating spelling suggestions using Levenshtein distance.
How it Works

1. Dictionary Loading
- Reads words from words.txt
- Inserts each word into:
  - Trie → for quick word existence checks
  - unordered_set → for suggestion generation

2. Spell Checking
- Input sentence is split into words
- Each word is checked against the Trie
- Correct words are printed normally
- Incorrect words are underlined

3. Suggestions
- Finds similar words (within a max Levenshtein distance) from the dictionary
- Displays up to 7 closest matches
Data Structures Used
- Trie → O(L) time complexity for word lookup (L = word length)
- unordered_set → for iterating dictionary words when calculating edit distances
Files
- main.cpp → Spell checker logic
- tries.h → Trie implementation
- words.txt → Dictionary word list

Trie Data Structure
A Trie is a tree-like data structure used to store a collection of strings for efficient retrieval.
How to Run
Compile Trie Example:
g++ tries_example.cpp tries.cpp -o trie
./trie
Compile Spell Checker:
g++ main.cpp tries.cpp -o spell_checker
./spell_checker
Sample Output
Trie Example:
Word car is present.
Word cart is present.
Word car is deleted.
Word car is not present.
Word cart is present.
Word carrom is not present.
Word carrom is present.
Word car is not present.
Spell Checker:
Enter a sentence: Soma
Soma
Suggestions for "Soma": coma soda sofa some soya aroma boa