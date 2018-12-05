//
//  main.cpp
//  vEBZack
//
//  Created by Mert TOSLALI on 12/4/18.
//  Copyright © 2018 Mert TOSLALI. All rights reserved.
//

#include <iostream>
#include "vEB.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    VEBTree *v = new VEBTree(256);

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
