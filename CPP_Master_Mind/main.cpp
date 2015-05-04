//
//  main.cpp
//  CPP_Master_Mind
//
//  Created by Joshua Bernitt on 5/4/15.
//  Copyright (c) 2015 Joshua Bernitt. All rights reserved.
//

#include <iostream>
#include "OrganismClass.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    Organism organism = *new Organism(4);
    
    std::cout << organism.get_fitness();
    return 0;
}
