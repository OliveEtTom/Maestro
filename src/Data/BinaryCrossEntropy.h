#pragma once
#include "LossFunction.h"

class BinaryCrossEntropy : public LossFunction {
public:
    BinaryCrossEntropy();
    bool isDatasetValid(const std::vector<Sample>& dataset) const override;
    double value(double y, double yHat) const override;
};