#include <iostream>
#include <fstream>

#include "city.hpp"
#include "tour.hpp"
#include "population.hpp"

using namespace std;

int main() {

    char mode;
    int city_in_tour;
    int population_size = 40;
    double mutation_rate = 15;
    tour t1 = tour("../qatar");

    cout << "Qatar, population 40, mutation rate 15%  " << endl;
    cout << "Use above preset? (y/n) " << endl;

    cin >> mode;

    if (mode != 'y') {

        cout << "Please input the number of city in tour: " << endl;
        cin >> city_in_tour;

        cout << "Please input population size: " << endl;
        cin >> population_size;

        cout << "Please input mutation rate: " << endl;
        cin >> mutation_rate;

        t1 = tour(city_in_tour);
    }

    t1.cal_total_distance();

    population the_population(t1, population_size, mutation_rate);

    the_population.GA();
    return 0;
}