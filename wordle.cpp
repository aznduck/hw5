#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <unordered_map>
#include <vector>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;




void wordHelp(const std::string& in, std::string& floating, const set<string>& dict, unsigned int n, string curr, std::set<std::string>& ans, int filled);

std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    std::set<std::string> ans;
    string floatingRef = floating;
    int filled = in.size() - std::count(in.begin(), in.end(), '-');
    wordHelp(in, floatingRef, dict, 0, in, ans, filled);
    return ans;
}

void wordHelp(const std::string& in, std::string& floating, const set<string>& dict, unsigned int n, string curr, std::set<std::string>& ans, int filled) {
    if(floating.size() + filled > (in.size() - n))
        return;
    if (n == curr.size()) {
        if (!(dict.find(curr) != dict.end())) 
            return;
        else if (floating.empty())
        {
            ans.insert(curr);
            return;
        }
        return;    
    }
    
    if (curr[n] != '-') {
        wordHelp(in, floating, dict, n + 1, curr, ans, filled - 1);
    } else {
        for (char letter = 'a'; letter <= 'z'; ++letter) {
            size_t pos = floating.find(letter);
            if (pos != std::string::npos) {
                string newFloating = floating;
                newFloating.erase(pos, 1);
                curr[n] = letter;
                wordHelp(in, newFloating, dict, n + 1, curr, ans, filled);
            }
                curr[n] = letter;
                wordHelp(in, floating, dict, n + 1, curr, ans, filled);
        }
    }
}




