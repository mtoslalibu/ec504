//
//  main.cpp
//  vEBZack
//
//  Created by Mert TOSLALI on 12/4/18.
//  Copyright © 2018 Mert TOSLALI. All rights reserved.
//

#include <iostream>
#include "vEB.hpp"
#include "XFastTrie.hpp"
#include <vector>

int main(int argc, const char * argv[]) {
    // insert code here...
    VEBTree *v = new VEBTree(256);

    XFastTrie *xft = new XFastTrie();

    Entry e = {5};
    vector<Node*> ch_n;
    ch_n.push_back(NULL);
    ch_n.push_back(NULL);
    Node n = {&e, ch_n, NULL};
    vector<Node*> ch_nr;
    ch_nr.push_back(&n);
    ch_nr.push_back(NULL);
    Node nr = {NULL, ch_nr, NULL};
    n.parent = &nr;

    cout << "Is internal " << isInternal(&nr) << endl;
    uint8_t a = 1;
    printf("shifted %d\n", ((uint8_t) 128) | (a << 6));

    vector<int> vec;
    vec.push_back(1);
    vec[0] = 2;
    cout << "Size: " << vec.size() << " val: " << vec[0] << endl;

    Entry nne = {12};
    Node* nnode = newNode(&nr, &nne);
    cout << "entry: " << nne.key << " parents child entry: ";
    printf("%lu\n", nnode->parent->children[0]->entry->key);

    for (int i=0; i<250; i = i+3) {
        v->insert(i);
    }

    printf("%d\n", v -> getMax());
    printf("%d\n", v -> getMin());
    printf("%d\n", (v -> successor(9)));
    printf("%d\n", (v -> predecessor(9)));
    printf(v->findItem(9)?"found\n":"not found\n");

    return 0;
}
