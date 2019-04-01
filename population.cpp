#include <random>

//
// Created by Haoyang Wang on 2019-03-30.
//

#include "population.hpp"

std::default_random_engine myRand((unsigned) time(0));

population::population(tour the_tour, int population_size, double the_mutation_rate) {
    mutation_rate = the_mutation_rate;
    for (int i = 0; i < population_size; i++) {
        vector<city> city_list = the_tour.get_city_list();
        shuffle(city_list.begin(), city_list.end(), std::mt19937(std::random_device()()));
        tour temp_tours(city_list);
        tours.push_back(temp_tours);
    }
    sort(tours.begin(), tours.end());
    elite_tour = tours[0];
    base_distance = elite_tour.get_total_distance();
}

void population::update_parents() {
    parents.clear();
    for (int i = 0; i < PARENT_POOL_SIZE; i++) {
        int size = static_cast<int>(tours.size() - 1);
        int index = myRand() % size + 1;
        tour temp = tours[index];
        parents.push_back(temp);
    }
}

tour population::crossover() {
    int a;
    int b;
    do {
        a = myRand() % PARENT_POOL_SIZE;
        b = myRand() % PARENT_POOL_SIZE;
    } while (a == b);
    vector<city> cities_a = parents[a].get_city_list();
    vector<city> cities_b = parents[b].get_city_list();
    vector<city> child_cities;

    int number_of_cities = static_cast<int>(cities_a.size());

    int indexStart = myRand() % number_of_cities;
    int indexEnd = myRand() % number_of_cities;

    if (indexStart > indexEnd) {
        int temp = indexEnd;
        indexEnd = indexStart;
        indexStart = temp;
    }

    for (int i = indexStart; i <= indexEnd; i++) {
        child_cities.push_back(cities_a[i]);
    }

    for (int j = 0; j < number_of_cities; j++) {
        bool tag = true;
        int size = static_cast<int>(child_cities.size());
        for (int n = 0; n < size; n++) {
            if (cities_b[j].getCityNumber() == child_cities[n].getCityNumber()) {
                tag = false;
                break;
            }
        }
        if (tag) {
            child_cities.push_back(cities_b[j]);
        }
    }
    tour child_tour(child_cities);

    return child_tour;
}

tour population::mutation(tour a_tour) {
    int city_list_size = static_cast<int>(a_tour.get_city_list().size());
    vector<city> temp_city_list = a_tour.get_city_list();

    for (int i = 0; i < city_list_size; i++) {
        int rand = myRand() % 100;

        if (rand < mutation_rate) {
            if (i == 0) {
                swap(temp_city_list[i], temp_city_list[i + 1]);
            } else if (i == city_list_size - 1) {
                swap(temp_city_list[i], temp_city_list[i - 1]);
            } else {
                if (myRand() % 2) {
                    swap(temp_city_list[i], temp_city_list[i - 1]);
                } else {
                    swap(temp_city_list[i], temp_city_list[i + 1]);
                }
            }
        }
    }
    tour tour_temp(temp_city_list);
    return tour_temp;
}


void population::GA() {
    double previous_total_distance = elite_tour.get_total_distance();
    int generations_between_elites = 0;
    for (int i = 0; i < GENERATIONS; i++) {
        update_parents();
        for (int j = 1; j < tours.size(); j++) {

            tour child_tour = crossover();

            double ran = (double) (myRand() % 100) / 100;

            if (ran < mutation_rate) {
                tours[j] = mutation(child_tour);
            } else {
                tours[j] = child_tour;
            }
            sort(tours.begin(), tours.end());

        }

        if (elite_tour.get_fitness() < tours[0].get_fitness()) {
            elite_tour = tours[0];

        }
        double current_total_distance = elite_tour.get_total_distance();
        if (previous_total_distance != current_total_distance) {
            cout << "After " << generations_between_elites << " generations: "<< endl;
            cout << "Current best distance: " << current_total_distance << endl;
            previous_total_distance = current_total_distance;
            generations_between_elites = 0;
        } else {
            generations_between_elites++;
        }

        double improve_factor = 100 - ((elite_tour.get_total_distance() / base_distance) * 100);

        if ((improve_factor > IMPROVEMENT_FACTOR) && i > 950) {
            cout << "Achieved a improvement factor" << endl;
            cout << "The best distance is " << elite_tour.get_total_distance() << endl;
            cout << "The improvement is " << improve_factor << "%" << endl;
            break;
        }
    }
}