//
//  main.cpp
//  CPP_Master_Mind
//
//  Created by Joshua Bernitt on 5/4/15.
//  Copyright (c) 2015 Joshua Bernitt. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;
#include "OrganismClass.h"
#include "utilities.h"
//#include "utilities.cpp"

int secret[4] = {1, 2, 4, 6}; //fitness of six is the best

/** 
 * this struct serves no purpose other than as some code I was playing with
struct {
	int array[1] = {};
	int *size = &array[-1];
} prev_fittest;
 */

//function definitions for main usage
void fitness_test_helper(Organism*);
int fitness_test(int[], int size);
int contains(int, int[], int);

int main(int argc, const char * argv[]) {
    // insert code here...
	/*
	 set up...
	 */
	//init random number key for use in genome generation
	//best used if only run once at start of program (allows for best randomness)
	srand(time(NULL));
	
	//create starting population container using classic arrays (for comparison on vectors)
	//DON'T FORGET TO delete() the array at the end!
	//Will not actually be using the pointer array. Will make use of vectors.
	Organism **start_population = new Organism*[300];
	int genome[] = {1,2,3,4};	//Initializing new genome. According to *site_paper*
								//using a random set of numbers from 1-4 provides the best
								//chance at guessing the sercret code.
	
	vector<Organism*> start_pop (300); //initializing vector to an array of pointers
	
	Organism *prime = new Organism(4, genome); //create first organism using constructor
	fitness_test_helper(prime); //get fitness of our base model
	
	/*
	 generate starting population...
	 */
	for (int i = 0; i < 300; i++) {
		//simple usage of arrays of pointers
		start_population[i] = new Organism(4);
		start_population[i]->set_genome();
		
		//here is the actual vector that is used
		start_pop[i] = new Organism(4); //create new organism in our vector
		start_pop[i]->set_genome();
	}
	
	/*
	 population evolution...
	 */
	for (int i = 0; i < 300; i++) {
		//test against prime
	}
	
	/*
	 Clean up the array of pointers we created because we don't need it.
	 */
	//we need to iterate through the array deleting all the pointers
	for (int i = 0; i < 300; i++) {
		delete start_population[i];
	}
	//now delete the array
	delete [] start_population; //cleaning up heap
	
	/*
	 Exit
	 */
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
