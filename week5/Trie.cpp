#include <iostream>
#include <string>
#include <map>
using namespace std;

struct Node
{
    map<char, Node *> next;
    bool isWord = false;
};

class Trie
{
public:
    Node *root;
    Trie()
    {
        root = new Node;
    }

    void insert(string word)
    {
        Node *cur = root;
        for (auto c : word)
        {
            if (cur->next[c] == nullptr)
            {
                cur->next[c] = new Node;
            }
            cur = cur->next[c];
        }
        cur->isWord = true;
    }

    bool search(string word)
    {
        Node *cur = root;
        for (auto c : word)
        {
            if (cur->next[c] == nullptr)
                return false;
            cur = cur->next[c];
        }
        return cur->isWord;
    }

    bool startWith(string prefix)
    {
        Node *cur = root;
        for (auto c : prefix)
        {
            if (cur->next[c] == nullptr)
                return false;
            cur = cur->next[c];
        }
        return true;
    }
};

int main()
{
    Trie trie;
    trie.insert("love");
    trie.insert("panda");
    cout << trie.startWith("love");
}