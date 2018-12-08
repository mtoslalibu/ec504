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
#include "inttypes.h"

pair<int, char> foo() {
    return make_pair(1, 'c');
}

int main(int argc, const char * argv[]) {
    // insert code here...
    VEBTree *v = new VEBTree(8);

    XFastTrie xft(4);

    Entry e0 = {2};
    xft.insert(&e0);
    Entry e1 = {3};
    xft.insert(&e1);
    Entry e2 = {5};
    xft.insert(&e2);
    Entry e3 = {7};
    xft.insert(&e3);
    Entry e4 = {11};
    xft.insert(&e4);
    Entry e5 = {13};
    xft.insert(&e5);

    cout << "Predecessor 9: " << xft.getPredecessor((uint64_t) 9)->key << endl;
    // cout << xft.getSuccessor((uint64_t) 4)->key << endl;

    printf("Len of layers: %lu\n", xft.getLayers().size());
    // for (int i = 0; i < 64; i++)
    //     printf("0x%" PRIx64 "\n", masks[i]);

    // vector<int> vec;
    // vec.push_back(1);
    // vec[0] = 2;
    // printf("vec[0]: %d\n", vec[0]);

    // map<char, int> mmap;
    // mmap['a'] = 1;
    // mmap['b'] = 2;
    // mmap['b'] = 33;
    // printf("mmap a, b: %d, %d\n", mmap['a'], mmap['b']);

    // vector<int*> vec = vector<int*>();
    // int one = 1;
    // int two = 2;
    // int three = 3;
    // vec.push_back(NULL);
    // vec.push_back(NULL);
    // vec[0] = &one;
    // vec[1] = &two;
    // vec[0] = &three;
    // vec[1] = &three;
    // vec[100] = &one;
    // cout << "Size is: " << vec.size() << endl;

    // auto ret = foo();
    // cout << "first: " << ret.first << " second: " << ret.second;

    // Entry e = {5};
    // xft.insert(&e);
    // Entry e1 = {6};
    // xft.insert(&e1);
    // Entry e2 = {6};
    // xft.insert(&e2);
    // Entry e3 = {4};
    // xft.insert(&e3);
    // Entry e4 = {8};
    // xft.insert(&e4);
    // Entry e33 = {12};
    // xft.insert(&e33);
    // Entry e44 = {13};
    // xft.insert(&e44);
    // Entry e331 = {9};
    // xft.insert(&e331);
    // Entry e441 = {34};
    // xft.insert(&e441);

    // Entry entries[100];
    // for (int i = 0; i < 100; i++) {
    //     cout << "insert " << i << endl;
    //     entries[i].key = i;
    //     xft.insert(&entries[i]);
    // }

    // printf("Max: %lu\n", xft.getMax()->key);
    // printf("Min: %lu\n", xft.getMin()->key);
    // printf("Len: %d\n", xft.getLen());
    // Entry* suc_5 = xft.getSuccessor((uint64_t)5);
    // Entry* suc_7 = xft.getSuccessor((uint64_t)7);
    // Entry* pred_7 = xft.getPredecessor((uint64_t)7);
    // Entry* pred_6 = xft.getPredecessor((uint64_t)6);
    // printf("Suc5: %lu\n", suc_5->key);
    // printf("Pred6: %lu\n", pred_6->key);
    // printf("Succ7: %lu Pred7: %lu\n", suc_7->key, pred_7->key);

    // cout << "Should delete " << endl;
    // xft.del((uint64_t) 6);
    // xft.del((uint64_t) 9);
    // xft.del((uint64_t) 12);
    // xft.del((uint64_t) 13);

    // vector<Node*> ch_n;
    // ch_n.push_back(NULL);
    // ch_n.push_back(NULL);
    // Node n = {&e, ch_n, NULL};
    // vector<Node*> ch_nr;
    // ch_nr.push_back(&n);
    // ch_nr.push_back(NULL);
    // Node nr = {NULL, ch_nr, NULL};
    // n.parent = &nr;

    // cout << "Is internal " << isInternal(&nr) << endl;
    // uint8_t a = 1;
    // printf("shifted %d\n", ((uint8_t) 128) | (a << 6));

    // vector<int> vec;
    // vec.push_back(1);
    // vec[0] = 2;
    // cout << "Size: " << vec.size() << " val: " << vec[0] << endl;

    // Entry nne = {12};
    // Node* nnode = newNode(&nr, &nne);
    // cout << "entry: " << nne.key << " parents child entry: ";
    // printf("%lu\n", nnode->parent->children[0]->entry->key);

    // printf("mask size: %lu\n", masks.size());
    // for (size_t i = 0; i < masks.size(); i++) {
    //     printf("%u ", masks[i]);
    // }
    // printf("Done\n");

    // for (int i=0; i<250; i = i+3) {
    //     v->insert(i);
    // }

    // vector<map<int, int>> veco;
    // map<int, int> mapo;
    // veco.push_back(mapo);

    // if (veco[0].find(2) == veco[0].end())
    //     cout << "Cannot find the key" << endl;

    // map<char, int> mapa;
    // mapa['a'] = 928;
    // mapa['b'] = 2;
    // map<char, int>::iterator record1 = mapa.find('a');
    // map<char, int>::iterator record2 = mapa.find('c');
    // if (record1 == mapa.end())
    //     cout << "record1 is end" << endl;
    // if (record2 == mapa.end())
    //     cout << "record2 is end" << endl;

    // printf("%d\n", v -> getMax());
    // printf("%d\n", v -> getMin());
    // printf("%d\n", (v -> successor(9)));
    // printf("%d\n", (v -> predecessor(9)));
    // printf(v->findItem(9)?"found\n":"not found\n");

    return 0;
}
