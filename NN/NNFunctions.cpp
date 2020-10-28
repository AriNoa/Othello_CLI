#include "NNFunctions.h"


NeuronLayer createLayer(
	const std::vector<NeuronModel>& neuronModels,
	const std::function<double(const double&)>& activation
) {
	std::vector<Neuron> neurons;

	for (const auto& model : neuronModels) {
		neurons.push_back(
			Neuron(model.weights, model.bias)
		);
	}

	return NeuronLayer(neurons, activation);
}

NeuralNetwork createNN(
	const std::vector<std::vector<NeuronModel>>& nn,
	const std::function<double(const double&)>& activation
) {
	std::vector<NeuronLayer> layers;

	for (const auto& neuronModels : nn) {
		layers.push_back(
			createLayer(neuronModels, activation)
		);
	}

	return NeuralNetwork(layers);
}