#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
#include <map>
using namespace std;


// Add prototypes of helper functions here

// check if word has matches known positions
bool green_check(const std::string& word, const std::string& in) {
    for (int i = 0; i < word.size(); i++) {
        if (in[i] != '-' && word[i] != in[i]) {
            return false;
        }
    }
    return true;
}

// check if word has floating letters
bool yellow_check(const std::string& word, const std::string& floating) {
    std::map<char, int> word_count;

    // Contar las letras en la palabra
    for (char c : word) {
        word_count[c]++;
    }

    // Contar las letras en floating y verificar que están en word
    for (char c : floating) {
        if (word_count[c] > 0) {
            word_count[c]--;  // marcarla como usada
        } else {
            return false;  // no está presente o no hay suficientes ocurrencias
        }
    }

    return true;
}

// check if word in dictionary
bool dict_check(const std::string& word, const std::set<std::string>& dict) {
    if (dict.find(word) != dict.end()) return true;
    return false;
}

// use branch and bound to add words to set of found
void recursive_helper(
        const std::string& word,
        size_t depth,
        std::set<std::string>& found,
        const std::string& in,
        const std::string& floating,
        const std::set<std::string>& dict
        ) {
    // base case the word lengths are at max (grown to maturity)
    if (depth == 0) {
        // check for floating and if word is in dictionary
        if (yellow_check(word, floating) && dict_check(word, dict)) {
            found.insert(word);
        }
        return;
    }

    // add next letter to branch
    for (char letter = 'a'; letter <= 'z'; letter++) {
        // check if known positions are valid
        if (green_check(word + letter, in)) {
            recursive_helper(word + letter, depth - 1, found, in, floating, dict);
        }
    }

}


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> found;

    recursive_helper("", in.size(), found, in, floating, dict);

    return found;

}

