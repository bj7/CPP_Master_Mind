//
//  main.cpp
//  CPP_Master_Mind
//
//  Created by Joshua Bernitt on 5/4/15.
//  Copyright (c) 2015 Joshua Bernitt. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
#include "OrganismClass.h"
//#include "utilities.h"
#include "utilities.cpp"

//Defining secret code to guess. Potentially create driver for true testing.
int secret[4] = {1, 2, 3, 4}; //fitness of six is the best

//define array to hold previous fittest guesses
vector<Organism*> previous_fittest(0);

/** 
 * this struct serves no purpose other than as some code I was playing with
struct {
	int array[1] = {};
	int *size = &array[-1];
} prev_fittest;
 */

//========= Function definitions for genetic algorithm and helpers ==========//
void fitness_test_helper(Organism*, bool psudo = false);
int fitness_test(int[], int size);
int contains(int, int[], int);
void debug_organism(Organism*);
int psudo_fitness_test(int genome[], int size);
Organism* reproduce(Organism, Organism);

int main(int argc, const char * argv[]) {
    // insert code here...
	
	/*
	 set up...
	 */
	//init random number key for use in genome generation
	//best used if only run once at start of program (allows for best randomness)
	srand(time(NULL));
	
	/*
	 brief error check for proper arguments
	 if none, use default code
	 */
	if (argc < 5) {
		//do nothing, secret has been initialized
	} else {
		//get initial code from command line
		int j = 0; //set as counter for secret
		for (int i = 1; i < argc; i++) {
			secret[j] =  atoi(argv[i]); //convert to int from command line arguments
			j++;
		}
	}
	my_print_array(secret, 4); cout << endl;
	
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
	previous_fittest.push_back(prime);
	
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
	int threshold = 3; //fitness threshold for who can reproduce
	bool flag = true;
	while (flag) {
		//test population against previous fittest
		for (int i = 0; i < start_pop.size(); i++) {
			fitness_test_helper(start_pop[i], true);
			//debug_organism(start_pop[i]);
		}
		
		/*
		 Determine who can reproduce
		 */
		vector<Organism*> reproduceable (0);
		for (int i = 0; i < start_pop.size(); i++) {
			if (start_pop[i]->get_fitness() > threshold) {
				reproduceable.push_back(start_pop[i]);
			}
		}
		/*
		 Now reproduce...
		 */
		vector<Organism*> offspring (0);
		for (int i = 0; i < reproduceable.size(); i++) {
			if (i + 1 < reproduceable.size()) {
				offspring.push_back(reproduce(*reproduceable[i], *reproduceable[i+1]));
			} else {
				offspring.push_back(reproduce(*reproduceable[0], *reproduceable[i]));
			}
		}
		
		Organism *current_fittest = start_pop[0];
		for (int i = 1; i < start_pop.size(); i++) {
			if (current_fittest->get_fitness() <= start_pop[i]->get_fitness()) {
				current_fittest = start_pop[i];
			}
		}
		cout << endl;
		debug_organism(current_fittest);
		
		flag = false;
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

//============ Genetic algorithm functions and helpers implementations ==========//

/**
 * API function for fitness test of organism allowing for simpler call.
 * Hides details of implementing the fitness test.
 * Optional boolean argument 'mode' for defining if it callse psudo test or real test
 * @param Organism* - Organism class instance
 * @return void
 */
void fitness_test_helper(Organism *organism, bool psudo) {
	if (psudo == false) { // if is false, then just do normal fitness test
		int genome[organism->get_size()];
		for (int i = 0; i < organism->get_size(); i++) {
			genome[i] = organism->get_genome()[i];
		}
		organism->set_fitness(fitness_test(genome, organism->get_size()));
	} else { //else true, use psudo_fitness_test()
		int genome[organism->get_size()];
		for (int i = 0; i < organism->get_size(); i++) {
			genome[i] = organism->get_genome()[i];
		}
		organism->set_fitness(psudo_fitness_test(genome, organism->get_size()));
	}
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

/**
 * Psudo fitness test function. Does not test against actual secret code but rather against 
 * all the 'top' organisms of the past to get an averaged top fitness.
 */
int psudo_fitness_test(int genome[], int size) {
	int fitness = 0;
	//outter loop to iterate over all previous guesses
	for(int i = 0; i < previous_fittest.size(); i++) {
		//inner loops to test the individual genomes
		
		//testing if genomes have identical parts
		for (int j = 0; j < size; j++) {
			if (previous_fittest[i]->get_genome()[j] == genome[j]) {
				fitness++;
			}
		}
		//testing if the genomes at least contain the same parts
		for (int k = 0; k < size; k++) {
			fitness += contains(genome[k], previous_fittest[i]->get_genome(), size);
		}
	}
	
	//take the average of the fitness
	fitness = fitness / previous_fittest.size();
	
	return fitness;
}

/**
 * Function accepts pointer to Organism object and prints the guts of the class.
 */
void debug_organism(Organism *organism) {
	cout << "size: " << organism->get_size() << " array dump: ";
	for (int i = 0; i < organism->get_size(); i++) {
		cout << organism->get_genome()[i];
	}
	cout << " ";
	cout << "fitness: " << organism->get_fitness() << endl;
}

/**
 * Function that takes two organisms, determines a random split in their genome on which to
 * build the offspring, then mutates a random point in the genome in 2% of the population.
 * Returns new child organism.
 */
Organism* reproduce(Organism a, Organism b) {
	int genome[4];
	
	//randomly decide on where to split parent genomes
	int split = rand() % 5;
	for (int i = 0; i < a.get_size(); i++) {
		if (i < split) {
			genome[i] = a.get_genome()[i];
		} else {
			genome[i] = b.get_genome()[i];
		}
	}
	//now cause random mutation in 2% of the population
	if ((rand() % 100 + 1) <= 2) {
		int rand_index = rand() % 5;
		int mutation = rand() % 6 + 1;
		
		genome[rand_index] = mutation;
	}
	
	Organism *child = new Organism(4, genome); //need to add genome
	return child;
}
