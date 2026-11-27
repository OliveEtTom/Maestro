#include "NeuralNetwork.h"

double Neuron::forward(const std::vector<double>& x) const
{
    double z = bias;

    for (std::size_t i = 0; i < weights.size(); ++i)
        z += weights[i] * x[i];

    return m_activationFunction->value(z);
}

NeuralNetwork::NeuralNetwork(const Neuron& neuron, std::shared_ptr<LossFunction> lossFunction, size_t inputSize) : 
m_neuron(neuron), m_lossFunction(std::move(lossFunction)), m_inputSize(inputSize) {
    m_neuron.setInputSize(inputSize);
}

void NeuralNetwork::train(const std::vector<Sample>& dataset, std::size_t epochs, double learningRate) {
    if (dataset.empty())
        throw std::invalid_argument("Empty dataset");

    for (const auto& sample : dataset) {
        if (sample.x.size() != m_inputSize) {
            throw std::invalid_argument("Invalid dataset");
        }
    }

    if (!m_lossFunction || !m_lossFunction->isDatasetValid(dataset))
        throw std::invalid_argument("Invalid loss function");

    for (std::size_t epoch = 0; epoch < epochs; ++epoch) {
        Gradients grad(m_inputSize);
        double totalLoss = 0.0;

        // Forward + Backward
        for (const auto& sample : dataset)
            totalLoss += backward(sample, grad);

        // Update weights once per epoch
        update(grad, learningRate, dataset.size());

        if (epoch % 100 == 0) {
            std::cout
                << "Epoch: " << epoch
                << " | Loss: "
                << totalLoss / dataset.size()
                << '\n';
        }
    }
}

double NeuralNetwork::backward(const Sample& sample, Gradients& grad) {
    if (!m_lossFunction) return 0;
    const double yHat = m_neuron.forward(sample.x);

    // Derivative of BCE + sigmoid
    const double dZ = yHat - sample.y;

    // Gradients for weights
    for (std::size_t i = 0; i < m_inputSize; ++i)
        grad.weights[i] += dZ * sample.x[i];

    // Gradient for bias
    grad.bias += dZ;

    return m_lossFunction->value(sample.y, yHat);
}

void NeuralNetwork::update(const Gradients& grad, double learningRate, std::size_t batchSize) {
    const double scale =
        learningRate / static_cast<double>(batchSize);

    for (std::size_t i = 0; i < m_inputSize; ++i)
        m_neuron.weights[i] -= scale * grad.weights[i];

    m_neuron.bias -= scale * grad.bias;   
}