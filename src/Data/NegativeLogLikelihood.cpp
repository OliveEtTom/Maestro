#include "NegativeLogLikelihood.h"
#include <cmath>

double NegativeLogLikelihood::value(double y, double yHat) const {
    return -(y*std::log(yHat) + (1 - y) * std::log(1 - yHat));
}

bool NegativeLogLikelihood::isDatasetValid(const std::vector<Sample>& dataset) const {
    return true;
}