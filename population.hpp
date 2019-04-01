//
// Created by Haoyang Wang on 2019-03-30.
//

#ifndef GENETICALGORITHM_POPULATION_HPP
#define GENETICALGORITHM_POPULATION_HPP

#define PARENT_POOL_SIZE 20
#define GENERATIONS 1000
#define IMPROVEMENT_FACTOR 20 //20% improvement

#include <algorithm>
#include <iostream>
#include <vector>

#include "tour.hpp"

class population {
private:
    vector<tour> tours;
    vector<tour> parents;
    double mutation_rate;
    tour elite_tour;
    double base_distance;
public:
    population(tour the_tour, int population_size, double the_mutation_rate);

    void update_parents();

    tour crossover();

    tour mutation(tour a_tour);

    void GA();


};


#endif //GENETICALGORITHM_POPULATION_HPP
