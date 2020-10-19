#include "NeuralNetwork.h"


NeuralNetwork::NeuralNetwork(const std::vector<NeuronLayer>& layers) {
	_inputLayer = layers[0];

	for (size_t i = 1; i < layers.size(); i++) {
		_layers.push_back(layers[i]);
	}
}


void NeuralNetwork::forward(std::vector<double> outputs) {
	_inputLayer.forward(outputs);

	for (auto& layer : _layers) { layer.forward(); }
}

std::vector<double> NeuralNetwork::output() {
	return _layers.back().getOutputs();
}