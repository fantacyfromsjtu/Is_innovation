#ifndef AHO_CORASICK_H
#define AHO_CORASICK_H

#include <vector>
#include <unordered_map>
#include <string>
#include <queue>

class AhoCorasick
{
public:
    AhoCorasick(const std::vector<std::string> &patterns);
    std::vector<std::pair<int, int>> search(const std::string &text);

private:
    struct Node
    {
        std::unordered_map<char, int> children;
        int failure = -1;
        std::vector<int> output;
    };

    std::vector<Node> trie;
    void buildTrie(const std::vector<std::string> &patterns);
    void buildFailurePointers();
};

#endif // AHO_CORASICK_H
