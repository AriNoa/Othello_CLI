#include "NeuralNetwork.h"


NeuralNetwork::NeuralNetwork(const std::vector<NeuronLayer>& layers) {
	_layers = layers;
}


std::vector<double> NeuralNetwork::forward(const std::vector<double>& inputs) const {
	std::vector<double> outputs = inputs;

	for (const auto& layer : _layers) {
		outputs = layer.forward(outputs);
	}

	return outputs;
}