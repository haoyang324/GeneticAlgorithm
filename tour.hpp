//
// Created by Haoyang Wang on 2019-03-30.
//

#ifndef GENETICALGORITHM_TOUR_HPP
#define GENETICALGORITHM_TOUR_HPP

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "city.hpp"

#define SCALAR 10000

using namespace std;

class tour {

private:
    vector<city> city_list;
    double fitness{};
public:
    double get_fitness() const;

private:
    double total_distance{};
public:

public:

    tour() = default;;

    explicit tour(int number_of_cities);

    explicit tour(string citys_in_tour);

    explicit tour(vector<city> the_city_list);

    vector<city> get_city_list();

    void cal_total_distance();

    double get_total_distance() const;
    bool operator < (const tour & tou) const;


};


#endif //GENETICALGORITHM_TOUR_HPP
