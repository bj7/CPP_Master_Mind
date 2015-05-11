//
//  debug.cpp
//  CPP_Master_Mind
//
//  Created by Joshua Bernitt on 5/4/15.
//  Copyright (c) 2015 Joshua Bernitt. All rights reserved.
//

#include "debug.h"
#include "OrganismClass.h"
#include <iostream>
using namespace std;

void debug_organism(Organism organism) {
    cout << "size: " << organism.get_size() << " array dump: ";
    for (int i = 0; i < organism.get_size(); i++) {
        cout << organism.get_genome()[i];
    }
    cout << " ";
    cout << "fitness: " << organism.get_fitness() << endl;
}

void print_array(int array[], int size) {
    cout << "[";
    for (int i = 0; i < size; i++) {
        cout << array[i] << ", ";
    }
    cout << "]";
}