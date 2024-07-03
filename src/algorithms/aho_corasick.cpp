#include "aho_corasick.h"

// 构造函数：构建字典树和失败指针
AhoCorasick::AhoCorasick(const std::vector<std::string> &patterns)
{
    buildTrie(patterns);
    buildFailurePointers();
}

// 构建字典树
void AhoCorasick::buildTrie(const std::vector<std::string> &patterns)
{
    trie.push_back(Node()); // 根节点
    for (int i = 0; i < patterns.size(); ++i)
    {
        const std::string &pattern = patterns[i];
        int currentNode = 0;
        for (char ch : pattern)
        {
            if (trie[currentNode].children.find(ch) == trie[currentNode].children.end())
            {
                trie[currentNode].children[ch] = trie.size();
                trie.push_back(Node());
            }
            currentNode = trie[currentNode].children[ch];
        }
        trie[currentNode].output.push_back(i);
    }
}

// 构建失败指针
void AhoCorasick::buildFailurePointers()
{
    std::queue<int> q;
    for (auto &pair : trie[0].children)
    {
        int child = pair.second;
        trie[child].failure = 0;
        q.push(child);
    }

    while (!q.empty())
    {
        int currentNode = q.front();
        q.pop();

        for (auto &pair : trie[currentNode].children)
        {
            char ch = pair.first;
            int child = pair.second;
            int failure = trie[currentNode].failure;

            while (failure != -1 && trie[failure].children.find(ch) == trie[failure].children.end())
            {
                failure = trie[failure].failure;
            }

            if (failure == -1)
            {
                trie[child].failure = 0;
            }
            else
            {
                trie[child].failure = trie[failure].children[ch];
                trie[child].output.insert(trie[child].output.end(),
                                          trie[trie[child].failure].output.begin(),
                                          trie[trie[child].failure].output.end());
            }

            q.push(child);
        }
    }
}

// 搜索文本
std::vector<std::pair<int, int>> AhoCorasick::search(const std::string &text)
{
    std::vector<std::pair<int, int>> matches;
    int currentNode = 0;

    for (int i = 0; i < text.size(); ++i)
    {
        char ch = text[i];

        while (currentNode != -1 && trie[currentNode].children.find(ch) == trie[currentNode].children.end())
        {
            currentNode = trie[currentNode].failure;
        }

        if (currentNode == -1)
        {
            currentNode = 0;
            continue;
        }

        currentNode = trie[currentNode].children[ch];
        for (int patternIndex : trie[currentNode].output)
        {
            matches.push_back({i, patternIndex});
        }
    }

    return matches;
}
