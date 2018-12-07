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
#include <map>

int main(int argc, const char * argv[]) {
    // insert code here...
    VEBTree *v = new VEBTree(256);

    XFastTrie xft(8);
    printf("Len of layers: %lu\n", xft.getLayers().size());

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

    // printf("mask size: %lu\n", masks.size());
    // for (size_t i = 0; i < masks.size(); i++) {
    //     printf("%u ", masks[i]);
    // }
    // printf("Done\n");

    // for (int i=0; i<250; i = i+3) {
    //     v->insert(i);
    // }

    vector<map<int, int>> veco;
    map<int, int> mapo;
    veco.push_back(mapo);

    if (veco[0].find(2) == veco[0].end())
        cout << "Cannot find the key" << endl;

    map<char, int> mapa;
    mapa['a'] = 928;
    mapa['b'] = 2;
    map<char, int>::iterator record1 = mapa.find('a');
    map<char, int>::iterator record2 = mapa.find('c');
    if (record1 == mapa.end())
        cout << "record1 is end" << endl;
    if (record2 == mapa.end())
        cout << "record2 is end" << endl;

    printf("%d\n", v -> getMax());
    printf("%d\n", v -> getMin());
    printf("%d\n", (v -> successor(9)));
    printf("%d\n", (v -> predecessor(9)));
    printf(v->findItem(9)?"found\n":"not found\n");

    return 0;
}
