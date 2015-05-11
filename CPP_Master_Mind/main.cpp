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
#include "utilities.h"

int secret[4] = {1, 2, 4, 6};

/** 
 * this struct serves no purpose other than as some code I was playing with
struct {
	int array[1] = {};
	int *size = &array[-1];
} prev_fittest;
 */

void fitness_test_helper(Organism*);
int fitness_test(int[], int size);
int contains(int, int[], int);

int main(int argc, const char * argv[]) {
    // insert code here...
	
	int genome[] = {1,2,3,4};
    Organism organism = *new Organism(4, genome);
	
	//organism.set_genome();
	debug_organism(organism);
	
	fitness_test_helper(&organism);
	debug_organism(organism);
    
    return 0;
}

/**
 * API function for fitness test of organism allowing for simpler call.
 * Hides details of implementing the fitness test.
 * @param Organism* - Organism class instance
 * @return void
 */
void fitness_test_helper(Organism *organism) {
	int genome[organism->get_size()];
	for (int i = 0; i < organism->get_size(); i++) {
		genome[i] = organism->get_genome()[i];
	}
	organism->set_fitness(fitness_test(genome, organism->get_size()));
}

/**
 * Actual fitness function to determine fitness of array passed in.
 * @param int[] - array to test against
 * @param int - size of array 
 * @return int - returns the fitness of the array as compared to the secret code
 */
int fitness_test(int array[], int size) {
	int fitness = 0;
	for(int i = 0; i < size; i++) {
		if(secret[i] == array[i]) {
			fitness++;
		}
	}
	for (int i = 0; i < size; i++) {
		fitness += contains(array[i], secret, size);
	}
	
	return fitness;
}
/**
 * Determines if a value exists in the array passed in and calculates the number of times it appears.
 * @param int - the value to test against
 * @param int[] - the array to check for the value
 * @param int - size of the array
 * @return int - returns the number of times the value exists in the array
 */
int contains(int test_val, int array[], int size) {
	int count = 0;
	for (int i = 0; i < size; i++) {
		if (test_val == array[i]) {
			count++;
		}
	}
	return count;
}
