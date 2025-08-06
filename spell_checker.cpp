    #include <iostream>
    #include <fstream>
    #include <unordered_set>
    #include <vector>
    #include <sstream>
    #include <algorithm>
    #include "tries.h"

    #define underlineOn "\033[4m"
    #define underlineOff "\033[0m"

    using namespace std;

    // Load words from words.txt
    unordered_set<string> loadWordsFromFile(const string& filename) {
        unordered_set<string> wordsSet;
        ifstream file(filename);
        string word;

        if (!file.is_open()) {
            cerr << "Error: Could not open words.txt" << endl;
            return wordsSet;
        }

        while (file >> word) {
            wordsSet.insert(word);
        }

        file.close();
        return wordsSet;
    }

    // Check if the word is all uppercase
    bool isAllUppercase(const string& word) {
        for (char c : word) {
            if (!isupper(c)) {
                return false;
            }
        }
        return true;
    }

    // Check if the word is capitalized (first letter uppercase, rest lowercase)
    bool isCapitalized(const string& word) {
        if (!isupper(word[0])) {
            return false;  // First letter must be uppercase
        }
        for (size_t i = 1; i < word.length(); ++i) {
            if (!islower(word[i])) {
                return false;  // Remaining letters must be lowercase
            }
        }
        return true;
    }

    // Check if the word is lowercase
    bool isAllLowercase(const string& word) {
        for (char c : word) {
            if (!islower(c)) {
                return false;
            }
        }
        return true;
    }

    // Levenshtein Distance Function
    int levenshteinDistance(const string& s1, const string& s2) {
        const size_t len1 = s1.size(), len2 = s2.size();
        vector<vector<int>> d(len1 + 1, vector<int>(len2 + 1));

        for (size_t i = 0; i <= len1; ++i) d[i][0] = i;
        for (size_t i = 0; i <= len2; ++i) d[0][i] = i;

        for (size_t i = 1; i <= len1; ++i)
            for (size_t j = 1; j <= len2; ++j)
                d[i][j] = min({
                    d[i - 1][j] + 1,   // deletion
                    d[i][j - 1] + 1,   // insertion
                    d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1)  // substitution
                });

        return d[len1][len2];
    }

    // Find suggestions for a misspelled word based on Levenshtein Distance
    vector<string> findSuggestions(const unordered_set<string>& dictionary, const string& misspelledWord, int maxSuggestions = 7, int maxDistance = 2) {
        vector<pair<int, string>> suggestionsWithDistance;
        string lowercaseWord = misspelledWord;

        // Convert the misspelled word to lowercase
        for (char& c : lowercaseWord) {
            c = tolower(c);
        }

        // Find words that are close to the misspelled word by Levenshtein Distance
        for (const string& dictWord : dictionary) {
            int distance = levenshteinDistance(lowercaseWord, dictWord);
            if (distance <= maxDistance) {  // Only consider words within a certain distance
                suggestionsWithDistance.push_back({distance, dictWord});
            }
        }

        // Sort the suggestions by Levenshtein Distance
        sort(suggestionsWithDistance.begin(), suggestionsWithDistance.end());

        // Extract the top maxSuggestions sorted suggestions
        vector<string> suggestions;
        for (size_t i = 0; i < suggestionsWithDistance.size() && i < (size_t)maxSuggestions; ++i) {
            suggestions.push_back(suggestionsWithDistance[i].second);
        }

        return suggestions;
    }

    // Display suggestions for the misspelled word
    void displaySuggestions(const vector<pair<string, vector<string>>>& suggestions) {
        for (const auto& suggestion : suggestions) {
            cout << "Suggestions for \"" << underlineOn << suggestion.first << underlineOff << "\": ";
            if (!suggestion.second.empty()) {
                for (const string& suggestionWord : suggestion.second) {
                    cout << suggestionWord << " ";
                }
            } else {
                cout << "No suggestions available.";
            }
            cout << endl;
        }
    }
int main() {
    Trie dictionaryTrie;
    unordered_set<string> dictionarySet;

    // Load dictionary from file
    ifstream file("words.txt");
    string w;
    while (file >> w) {
        dictionaryTrie.insert(w);
        dictionarySet.insert(w);
    }
    file.close();

    if (dictionarySet.empty()) {
        cerr << "Error: No words loaded from words.txt" << endl;
        return 1;
    }

    cout << "Enter a sentence: ";
    string inputLine;
    getline(cin, inputLine);

    if (inputLine.empty()) {
        cerr << "Error: No input provided." << endl;
        return 1;
    }

    istringstream iss(inputLine);
    string word;
    bool isFirstWord = true;

    vector<pair<string, vector<string>>> suggestionsList;

    auto processWord = [&](const string& originalWord, bool firstWord) {
        string lowercaseWord = originalWord;
        for (char& c : lowercaseWord) c = tolower(c);

        bool validCase = firstWord
            ? (isCapitalized(originalWord) || isAllUppercase(originalWord))
            : (isAllLowercase(originalWord) || isCapitalized(originalWord) || isAllUppercase(originalWord));

        if (validCase && dictionaryTrie.search(lowercaseWord)) {
            cout << originalWord << " ";
        } else {
            cout << underlineOn << originalWord << underlineOff << " ";
            suggestionsList.push_back({originalWord, findSuggestions(dictionarySet, originalWord)});
        }
    };

    while (iss >> word) {
        processWord(word, isFirstWord);
        isFirstWord = false;
    }

    cout << endl;
    displaySuggestions(suggestionsList);

    return 0;
}
