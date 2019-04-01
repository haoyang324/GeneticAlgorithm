//
// Created by Haoyang Wang on 2019-03-30.
//


#include "city.hpp"

int cityNumberCounter = 0;
const int lowerBound{0};
const int MAP_BOUNDARY = 1000;
std::default_random_engine generator((unsigned) time(0));
std::uniform_real_distribution<double> distribution(lowerBound, MAP_BOUNDARY);

city::city(int cityNumber) : cityNumber(cityNumber) {
    x = distribution(generator);
    y = distribution(generator);
}


city::city(int n, double x, double y) : cityNumber(n), x(x), y(y) {}


int city::getCityNumber() const {
    return cityNumber;
}

double city::getX() const {
    return x;
}

double city::getY() const {
    return y;
}

double city::distanceTo(city city2) {
    double xDistance = abs(x - city2.getX());
    double yDistance = abs(y - city2.getY());
    double distance = sqrt((xDistance * xDistance) + (yDistance * yDistance));
    return distance;
}
