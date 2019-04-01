//
// Created by Haoyang Wang on 2019-03-30.
//

#ifndef GENETICALGORITHM_CITY_HPP
#define GENETICALGORITHM_CITY_HPP

#include <random>
#include <ctime>

class city {

private:
    int cityNumber;
    double x;
    double y;

public:

    explicit city(int);

    explicit city(int, double, double);

    int getCityNumber() const;

    double getX() const;

    double getY() const;


    double distanceTo(city city2);


};


#endif //GENETICALGORITHM_CITY_HPP
