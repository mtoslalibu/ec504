#include <stdint.h>
#include <map>
#include <vector>
#include <tuple>

using namespace std;

// In 8-bit parlance: 10000000, 11000000, 11100000 ...
static vector<uint64_t> fillMasks() {
    vector<uint64_t> masks;
    uint64_t mask = 0;

    for (uint64_t i = 0; i < 64; i++) {
        mask = mask | (1 << (63 - i));
        masks.push_back(mask);
    }

    return masks;
}

// In 8 bit parlance:
static vector<uint64_t> fillPositions() {
    vector<uint64_t> positions;

    for (uint64_t i = 0; i < 64; i++)
        positions.push_back(1 << (63 - i));

    return positions;
}

static const vector<uint64_t> masks = fillMasks();
static const vector<uint64_t> positions = fillPositions();

// Data actually stored in the XFastTrie
typedef struct Entry {
    uint64_t key;
} Entry;

typedef struct Node {
    Entry* entry;
    vector<Node*> children;
    Node* parent;
} Node;

// Internal nodes have no entry. All data in the leaves.
bool isInternal (Node* n) {
    if (n == NULL)
        return false;

    return n->entry == NULL;
}

// Does a node have children that are internal
bool hasInternal(Node* n) {
    return isInternal(n->children[0]) || isInternal(n->children[1]);
}

bool isLeaf(Node* n) {
    if (n == NULL)
        return false;

    return !isInternal(n);
}

Node* newNode(Node* parent, Entry* entry) {
    Node* n = new Node;

    n->children = vector<Node*>();
    n->parent = parent;
    n->entry = entry;

    return n;
}

tuple<int, Node*> bianrySearchHashMaps(vector<map<uint64_t, Node*>> layers, uint64_t key) {
    int low = 0;
    int high = layers.size();
    int diff = 64 - layers.size();
    int mid;
    Node* node;

    while (low <= high) {
        mid = (low + high) / 2;
        auto n_iter = layers[mid].find(key & masks[diff + mid]);
        if (n_iter == layers[mid].end()) {
            // key not present
            high = mid - 1;
        } else {
            node = n_iter->second;
            low = mid + 1;
        }
    }

    return tuple<int, Node*>(low, node);
}

int whichSide(Node* parent, Node* n) {
    if (parent->children[0] == n)
        return 0;

    if (parent->children[1] == n)
        return 1;

    throw "Node " + to_string(n->entry->key) + " is not a child of "
        + to_string(parent->entry->key);
}

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
