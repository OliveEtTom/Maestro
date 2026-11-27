#pragma once
#include "Sample.h"

class LossFunction {
public:
    virtual ~LossFunction() = default;
    virtual bool isDatasetValid(const std::vector<Sample>& dataset) const = 0;
    virtual double value(double y, double yHat) const = 0;
};