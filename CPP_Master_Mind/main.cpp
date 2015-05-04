//
//  main.cpp
//  CPP_Master_Mind
//
//  Created by Joshua Bernitt on 5/4/15.
//  Copyright (c) 2015 Joshua Bernitt. All rights reserved.
//

#include <iostream>
using namespace std;
#include "OrganismClass.h"
#include "debug.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    Organism organism = *new Organism(4);
    debug_array(organism);
    
    organism.set_fitness(5);

    organism.set_genome();
    debug_array(organism);
    
    return 0;
}
