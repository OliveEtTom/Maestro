#pragma once
#include "LossFunction.h"

class NegativeLogLikelihood : public LossFunction {
public:
    bool isDatasetValid(const std::vector<Sample>& dataset) const override;
    double value(double y, double yHat) const override;
};