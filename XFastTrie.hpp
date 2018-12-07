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

// In 8-bit parlance: 10000000, 01000000, 00100000
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

tuple<int, Node*> binarySearchHashMaps(vector<map<uint64_t, Node*>> layers, uint64_t key) {
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
    XFastTrie(int);
    ~XFastTrie() {};

    bool exists(uint64_t) const;
    vector<map<uint64_t, Node*>> getLayers() const;
    int getLen() const;
    Entry* getMax() const;
    Entry* getMin() const;
    void insert(Entry*);
    Node* predecessor (uint64_t);
    Node* successor (uint64_t);
    Entry* getPredecessor(uint64_t);
    Entry* getSuccessor(uint64_t);
    void walkUpSuccessor(Node* root, Node* node, Node* successor);
    void walkUpPredecessor(Node* root, Node* node, Node* predecessor);
    void walkUpNode(Node* root, Node* node, Node* predecessor, Node* successor);

private:
    // LSS hash layers. Will have as many those as is the length of
    // keys + zeroth layer.
    vector<map<uint64_t, Node*>> layers;

    // Root node. Introduces new layer, on the top of others.
    Node* root;

    // Number of items in the trie
    uint64_t num;

    // Number of bits of the keys and its difference with 64
    uint16_t bits, diff;

    // Highest and lowest seen keys
    Node* min, *max;
};

XFastTrie::XFastTrie(int bts) {
    switch (bts) {
    case 8: bits = 8; break;
    case 16: bits = 16; break;
    case 32: bits = 16; break;
    case 64: bits = 16; break;
    default:
        throw "Only 8, 16, 32, 64 key lengths are supported.";
    }

    layers = vector<map<uint64_t, Node*>>();
    layers.reserve(bits);
    diff = 64 - bits;

    for (int i = 0; i < bits; i++)
        layers.push_back(map<uint64_t, Node*>());

    num = 0;
    root = newNode(NULL, NULL);

    min = NULL;
    max = NULL;
}

bool XFastTrie::exists(uint64_t key) const {
    // If key exists, it must be at the bottom layer
    if (layers[bits - 1].find(key) == layers[bits - 1].end())
        return false;

    return true;
}

vector<map<uint64_t, Node*>> XFastTrie::getLayers() const {
    return layers;
}

int XFastTrie::getLen() const {
    return num;
}

Entry* XFastTrie::getMax() const {
    if (max)
        return max->entry;

    return NULL;
}

Entry* XFastTrie::getMin() const {
    if (min)
        return min->entry;

    return NULL;
}

// Equal to or immediately less then the provided key
Node* XFastTrie::predecessor(uint64_t key) {
    // No nodes, no predecessor
    if (root == NULL || max == NULL)
        return NULL;

    if (key >= max->entry->key)
        return max;

    if (key < min->entry->key)
        return NULL;

    auto n_iter = layers[bits - 1].find(key);
    if (n_iter != layers[bits - 1].end())
        return n_iter->second;

    auto bs = binarySearchHashMaps(layers, key);
    int layer = get<0>(bs);
    Node* n = get<1>(bs);
    if (n == NULL && layer > 1)
        return NULL;
    else if (n == NULL)
        n = root;

    if (isInternal(n->children[0]) && isLeaf(n->children[1]))
        return n->children[1]->children[0];

    return n->children[0];
}

Node* XFastTrie::successor(uint64_t key) {
    if (root == NULL || min == NULL)
        return NULL;

    if (key <= min->entry->key)
        return 0;

    if (key > max->entry->key)
        return NULL;

    auto n_iter = layers[bits - 1].find(key);
    if (n_iter != layers[bits - 1].end())
        return n_iter->second;

    auto bs = binarySearchHashMaps(layers, key);
    int layer = get<0>(bs);
    Node* n = get<1>(bs);
    if (n == NULL && layer > 1)
        return NULL;
    else if (n == NULL)
        n = root;

    if (isInternal(n->children[1]) && isLeaf(n->children[0]))
        return n->children[0]->children[1];

    return n->children[1];
}

Entry* XFastTrie::getPredecessor(uint64_t key) {
    Node* n = predecessor(key);

    if (n)
        return n->entry;

    return NULL;
}

Entry* XFastTrie::getSuccessor(uint64_t key) {
    Node* n = successor(key);

    if (n)
        return n->entry;

    return NULL;
}

void XFastTrie::walkUpSuccessor(Node* root, Node* node, Node* successor) {
    Node* n = successor->parent;

    while (n != NULL && n != root) {
        if (!isInternal(n->children[0]) && (n->children[0] != successor)) {
            n->children[0] = node;
            // TODO: maybe this?
            // node->parent = n;
        }

        n = n->parent;
    }
}

void XFastTrie::walkUpPredecessor(Node* root, Node* node, Node* predecessor) {
    Node* n = predecessor->parent;

    while (n != NULL && n != root) {
        if (!isInternal(n->children[1]) && (n->children[1] != predecessor)) {
            n->children[1] = node;
            // TODO: maybe this?
            // node->parent = n;
        }

        n = n->parent;
    }
}

void XFastTrie::walkUpNode(Node* root, Node* node, Node* predecessor, Node* successor) {
    Node* n = node->parent;

    while (n != NULL && n != root) {
        if (!isInternal(n->children[1]) && n->children[1] != successor && n->children[1] != node) {
            n->children[1] = successor;
            // TODO: maybe this?
            // successor->parent = n->children[1];
        }

        if (!isInternal(n->children[0]) && n->children[0] != predecessor && n->children[0] != node) {
            n->children[0] = successor;
            // TODO: maybe this?
            // successor->parent = n->children[1];
        }

        n = n->parent;
    }
}

// Inserts new or overwrite if it already exists
void XFastTrie::insert(Entry *entry) {
    uint64_t key = entry->key;

    // it key is already present
    auto n_iter = layers[bits - 1].find(key);
    Node* n = NULL;
    if (n_iter != layers[bits - 1].end()) {
        n_iter->second->entry = entry;
        return;
    }

    Node *predecessor = NULL, *successor = NULL;
    if (min != NULL && key < min->entry->key)
        successor = min;
    else
        successor = XFastTrie::successor(key);

    if (successor == NULL) {
        if (max != NULL && key > max->entry->key)
            predecessor = max;
        else
            predecessor = XFastTrie::predecessor(key);
    }

    // find the deepest root with a matching prefix
    auto bs = binarySearchHashMaps(layers, key);
    int layer = get<0>(bs);
    Node* root = get<1>(bs);
    if (root == NULL) {
        n = root;
        layer = 0;
    } else {
        n = root;
    }

    // from the existing node, create new nodes
    for (uint8_t i = layer; i < bits; i++) {

    }

}
