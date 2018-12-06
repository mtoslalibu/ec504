#pragma once

#include <stdint.h>
#include <map>

using namespace std;

typedef struct Entry {
    uint64_t key;
} Entry;

typedef struct Node {
    Entry entry;
    Node* children[2];
    Node* parent;
} Node;

class XFastTrie
{
public:
    XFastTrie();
    ~XFastTrie();

    map<uint64_t, Node*> getLayers() const;

private:
    // LSS hash layers
    map<uint64_t, Node*> layers;

    // Root node. Introduces new layer, on the top of others.
    Node* root;

    // Number of items in the trie
    uint64_t num;

    // Number of bits of the keys and its difference with 64
    uint16_t bits, diff;

    // Highest and lowest seen keys
    Node* min, max;
};

XFastTrie::XFastTrie() {}
