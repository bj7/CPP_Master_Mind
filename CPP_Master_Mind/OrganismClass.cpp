//
//  OrganismClass.cpp
//  CPP_Master_Mind
//
//  Created by Joshua Bernitt on 5/4/15.
//  Copyright (c) 2015 Joshua Bernitt. All rights reserved.
//

#include "OrganismClass.h"
/**
 * Default constructor for class
 */
Organism::Organism(int size) {
    this->fitness = 0;
    this->genome[size] = {};
}

int Organism::get_fitness() {
    return this->fitness;
}

bool Organism::set_fitness(int n) {
    if ((this->fitness = n)) {
        return true;
    } else {
        return false;
    }
}
