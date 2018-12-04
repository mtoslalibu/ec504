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
    std::cout << "Hello, World!\n";
    vEB *v= new class vEB(256);
    
    for (int i=0; i<250; i = i+4) {
        v->insert(i);
    }
    
    
    printf("%d\n", v -> getMax());
    printf("%d\n", v -> getMin());
    printf("%d\n", (v -> successor(9)));
    printf("%d\n", (v -> prediccessor(9)));
    
    
    return 0;
}
