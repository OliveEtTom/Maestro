#pragma once
#include "Sample.h"
#include "LossFunction.h"
#include "ActivationFunction.h"

#include <cmath>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <memory>

struct Neuron
{
    std::shared_ptr<ActivationFunction> m_activationFunction = nullptr;
    std::vector<double> weights;
    double bias = 0.0;

    Neuron(std::shared_ptr<ActivationFunction> activationFunction)
        : m_activationFunction(activationFunction)
    {
    }

    void setInputSize(std::size_t inputSize) {
        weights = std::vector<double>(inputSize, 0.0);
    }

    // Forward propagation
    double forward(const std::vector<double>& x) const;
};

struct Gradients
{
    Gradients(size_t inputSize) : weights(inputSize, 0.0) {}
    std::vector<double> weights;
    double bias = 0.0;
};

class NeuralNetwork {
public:
    NeuralNetwork(const Neuron& neuron, std::shared_ptr<LossFunction> lossFunction, size_t inputSize);
    void train(const std::vector<Sample>& dataset, std::size_t epochs, double learningRate);
    Neuron neuron() const { return m_neuron; };
private:
    double backward(const Sample& sample, Gradients& grad);
    void update(const Gradients& grad, double learningRate, std::size_t batchSize);
private:
    Neuron m_neuron;
    std::shared_ptr<LossFunction> m_lossFunction = nullptr;
    size_t m_inputSize = 0;
};

