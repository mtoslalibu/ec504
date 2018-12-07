/*

  Rewrite of Golang's github.com/Workiva/go-datastructures/blob/master/trie/xfast/xfast.go

 */

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
        mask = mask | ((uint64_t)1 << (63 - i));
        masks.push_back(mask);
    }

    return masks;
}

// In 8-bit parlance: 10000000, 01000000, 00100000
static vector<uint64_t> fillPositions() {
    vector<uint64_t> positions;

    for (uint64_t i = 0; i < 64; i++)
        positions.push_back((uint64_t)1 << (63 - i));

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
    n->children.push_back(NULL);
    n->children.push_back(NULL);
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

int whichSide(Node* n, Node* parent) {
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
    void del(uint64_t);
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
        return min;

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

    // if key is already present
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

    uint64_t leftOrRight;

    // from the existing node, create new nodes
    for (uint8_t i = layer; i < bits; i++) {
        leftOrRight = (key & positions[diff + i]) >> (bits - 1 - i);
        if (n->children[leftOrRight] == NULL || isLeaf(n->children[leftOrRight])) {
            Node* nn;
            if (i < bits - 1) {
                nn = newNode(n, NULL);
            } else {
                nn = newNode(n, entry);
                num++;
            }

            n->children[leftOrRight] = nn;
            layers[i][key & masks[diff + i]] = nn;
        }

        n = n->children[leftOrRight];
    }

    // add new node in doubly-linked list on the leaves level
    if (successor != NULL) {
        predecessor = successor->children[0];
        if (predecessor != NULL) {
            predecessor->children[1] = n;
            n->children[0] = predecessor;
            // TODO: cross pointers
        }
        n->children[1] = successor;
        successor->children[0] = n;
        // TODO: cross pointers
    } else if (predecessor != NULL) {
        n->children[0] = predecessor;
        predecessor->children[1] = n;
        // TODO: cross pointers
    }

    // walk up the successor if it exists to set that branch's new
    // predecessor
    if (successor != NULL)
        walkUpSuccessor(root, n, successor);

    // walk up predecessor if it exists to set that branch's new
    // successor
    if (predecessor != NULL)
        walkUpPredecessor(root, n, predecessor);

    // finally walk up our own branch to set both successors and
    // predecessors
    walkUpNode(root, n, predecessor, successor);

    // do the final check against the min/max indices
    if (max == NULL || key > max->entry->key)
        max = n;

    if (min == NULL || key < min->entry->key)
        min = n;
}

void XFastTrie::del(uint64_t key) {
    auto n_iter = layers[bits - 1].find(key);
    if (n_iter == layers[bits - 1].end())
        return;

    Node* n = n_iter->second;
    Node* successor = n->children[1];
    Node* predecessor = n->children[0];

    uint8_t i = 1;
    layers[bits - 1].erase(key);
    int leftOrRight = whichSide(n, n->parent);
    n->parent->children[leftOrRight] = NULL;
    n->children[0] = NULL;
    n->children[1] = NULL;
    n = n->parent;
    // TODO: cross pointers n->parent = NULL
    bool hasImmediateSibling = false;
    if (successor != NULL && successor->parent == n)
        hasImmediateSibling = true;
    if (predecessor != NULL && predecessor->parent == n)
        hasImmediateSibling = true;

    // this loop kills any nodes that no longer link to internal nodes
    while (n != NULL && n->parent != NULL) {
        if (hasInternal(n) || (i == 1 && hasImmediateSibling)) {
            n = n->parent;
            break;
        }

        leftOrRight = whichSide(n, n->parent);
        n->parent->children[leftOrRight] = NULL;
        // TODO: cross pointers
        n->children[0] = NULL;
        n->children[1] = NULL;
        layers[bits - i - 1].erase(key & masks[masks.size() - 1 - i]);
        n = n->parent;
        i++;
    }

    // check and update threads in leaves and in their branhes
    if (predecessor != NULL) {
        predecessor->children[1] = successor;
        // TODO: cross pointers
        walkUpPredecessor(n, successor, predecessor);
    }

    if (successor != NULL) {
        successor->children[0] = predecessor;
        // TODO: cross pointers
        walkUpSuccessor(n, predecessor, successor);
    }

    // check max/min indeces
    if (max->entry->key == key)
        max = predecessor;

    if (min->entry->key == key)
        min = successor;

    num--;
}
