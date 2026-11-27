#include <boost/test/unit_test.hpp>

#include "NeuralNetwork.h"
#include "BinaryCrossEntropy.h"

void buildTrainDataset(double min, double max, size_t numSteps, 
    std::vector<double> w, double b,
    std::vector<Sample> &dataset) {
    size_t inputSize = w.size();

    std::shared_ptr<ActivationFunction> activationFunction = std::make_shared<Sigmoid>();
    Neuron neuron(activationFunction);
    neuron.weights = w;
    neuron.bias = b;

    double delta = (max - min) / numSteps;
    for (size_t iStep = 0; iStep < numSteps; iStep++) {
        std::vector<double> sampleX(inputSize, min + iStep * delta);
        double sampleB = neuron.forward(sampleX) >= 0.5 ? 1 : 0;
        dataset.push_back({sampleX, sampleB});
    }
}

BOOST_AUTO_TEST_SUITE(NeuralNetworkTest)

BOOST_AUTO_TEST_CASE(test_train)
{
    std::vector<Sample> trainDataSet;
    buildTrainDataset(-2.5, 2.5, 100, { 0.985, 2.186 }, -0.522, trainDataSet);

    std::shared_ptr<ActivationFunction> activationFunction = std::make_shared<Sigmoid>();
    size_t inputSize = 2;
    Neuron neuron(activationFunction);
    std::shared_ptr<LossFunction> lossFunction = std::make_shared<BinaryCrossEntropy>();
    NeuralNetwork neuralNetwork(neuron, lossFunction, inputSize);

    neuralNetwork.train(trainDataSet, 5000, 0.1);

    neuron = neuralNetwork.neuron();

    std::vector<Sample> dataset = {
        {{0.896, 1.410}, 1.0},
        {{-1.509, -1.438}, 0.0},
        {{1.443, 1.333}, 1.0},
        {{-1.895, -0.613}, 0.0},
        {{-2.048, -2.420}, 0.0}
    };

    for (const auto& sample : dataset) {
        const double prediction = neuron.forward(sample.x);
        double value = prediction >= 0.5 ? 1 : 0;
        BOOST_CHECK_EQUAL(value, sample.y);
    }
}

BOOST_AUTO_TEST_SUITE_END()