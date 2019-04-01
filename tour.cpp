#include <utility>

//
// Created by Haoyang Wang on 2019-03-30.
//


#include "tour.hpp"

tour::tour(int number_of_cities) {
    fitness = 0;
    for (int i = 0; i < number_of_cities; i++) {
        city c(i);
        city_list.push_back(c);
    }

}

tour::tour(string filePath) {
    ifstream ifs{filePath};

    int n;
    double x;
    double y;
    while (ifs >> n && ifs >> x && ifs >> y) {
        city c(n, x, y);
        city_list.push_back(c);
    }
}

vector<city> tour::get_city_list() {
    return city_list;
}

void tour::cal_total_distance() {
    total_distance = 0;
    if (city_list.size() > 1) {
        for (int i = 0; i < city_list.size() - 1; i++) {
            total_distance += city_list[i].distanceTo(city_list[i + 1]);
        }
    }
    int lastCityIndex = static_cast<int>(city_list.size() - 1);
    total_distance += city_list[0].distanceTo(city_list[lastCityIndex]);

//    cout << total_distance << " ";
    fitness = 1 / total_distance * SCALAR;
}

tour::tour(vector<city> city_list) :city_list(std::move(city_list)){
    cal_total_distance();
}

double tour::get_total_distance() const {
    return total_distance;
}

bool tour::operator<(const tour &tou) const {
    return fitness > tou.get_fitness();
}

double tour::get_fitness() const {
    return fitness;
}
