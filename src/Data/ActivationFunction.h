#pragma once
#include <cmath>
class ActivationFunction {
public:
    virtual ~ActivationFunction() = default;
    virtual double value(double z) const = 0;
};

class Sigmoid : public ActivationFunction {
    double value(double z) const override {
        return 1.0 / (1.0 + std::exp(-z));
    }
};