#pragma once
#include "NeuronLayer.h"


class NeuralNetwork {
private:
	NeuronLayer _inputLayer;
	std::vector<NeuronLayer> _layers;

public:
	NeuralNetwork() = default;
	NeuralNetwork(const std::vector<NeuronLayer>& layers);

	void forward(std::vector<double> outputs);
	std::vector<double> output();
};
