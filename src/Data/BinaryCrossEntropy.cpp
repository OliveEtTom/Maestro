#include "BinaryCrossEntropy.h"
#include <cmath>
#include <algorithm>

BinaryCrossEntropy::BinaryCrossEntropy() {
    
}

double BinaryCrossEntropy::value(double y, double yHat) const {
    constexpr double EPSILON = 1e-12;

    yHat = std::clamp(
        yHat, EPSILON, 1.0 - EPSILON);

    return -(y * std::log(yHat)
           + (1.0 - y) * std::log(1.0 - yHat));
}

bool BinaryCrossEntropy::isDatasetValid(const std::vector<Sample>& dataset) const {
    for (const auto& sample : dataset) {
        if (sample.y != 0.0 && sample.y != 1.0) {
            return false;
        }
    }
    return true;
}