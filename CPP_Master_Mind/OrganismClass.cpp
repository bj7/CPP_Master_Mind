//
//  OrganismClass.cpp
//  CPP_Master_Mind
//
//  Created by Joshua Bernitt on 5/4/15.
//  Copyright (c) 2015 Joshua Bernitt. All rights reserved.
//

#include "OrganismClass.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

/**
 * Default constructor for class
 */
Organism::Organism() {
    this->fitness = 0;
    this->size = 0;
    this->genome = NULL;
}

Organism::Organism(int size) {
    this->fitness = 0;
    this->size = size;
    this->genome = new int[size];
}

Organism::Organism(int size, int *genome) {
    this->fitness = 0;
    this->size = size;
    this->genome = new int[size];
    
    for (int i = 0; i < size; i++) {
        this->genome[i] = genome[i];
    }
}

Organism::~Organism() {
    cout << "Deleting this: " << this << endl;
    if (this->genome != NULL) {
         delete [] this->genome;
    }
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

void Organism::set_genome() {
    generate_genome(this->genome, this->size);
}

int* Organism::get_genome() {
    return this->genome;
}

void Organism::generate_genome(int genome[], int size) {
    //srand(time(NULL)); *this here causes the same random number due to
    //execution speed
    for (int i = 0; i < size; i++) {
        genome[i] = rand() % 6 + 1;
    }
}

int Organism::get_size() {
    return this->size;
}

