//
//  OrganismClass.h
//  CPP_Master_Mind
//
//  Created by Joshua Bernitt on 5/4/15.
//  Copyright (c) 2015 Joshua Bernitt. All rights reserved.
//

#ifndef __CPP_Master_Mind__OrganismClass__
#define __CPP_Master_Mind__OrganismClass__

#include <stdio.h>

#endif /* defined(__CPP_Master_Mind__OrganismClass__) */

#ifndef ORGANISMCLASS_H
#define ORGANISMCLASS_H

class Organism {
private:
    int fitness;
    int *genome;
    int size;
    void generate_genome(int[], int size);
    
public:
    bool set_fitness(int n);
    int get_fitness();
    void set_genome();
    int* get_genome();
    int get_size();
    
    Organism(int size); //default constructor
    
};

#endif
