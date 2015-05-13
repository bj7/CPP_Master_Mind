//
//  utilities.cpp
//  CPP_Array_Lib
//
//  Created by Joshua Bernitt on 5/11/15.
//  Copyright (c) 2015 Joshua Bernitt. All rights reserved.
//

#include "utilities.h"
#include <iostream>

using namespace std;
template<class T>
void print_array(T array[], int size) {
    cout << "[";
    for (int i = 0; i < size; i++) {
        cout << array[i] << ", ";
    }
    cout << "]";
}

void debug_organism(Organism *organism) {
    cout << "size: " << organism->get_size() << " array dump: ";
    for (int i = 0; i < organism->get_size(); i++) {
        cout << organism->get_genome()[i];
    }
    cout << " ";
    cout << "fitness: " << organism->get_fitness() << endl;
}