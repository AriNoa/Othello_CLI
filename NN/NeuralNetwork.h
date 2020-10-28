#pragma once
#include "NeuronLayer.h"


class NeuralNetwork {
private:
	std::vector<NeuronLayer> _layers;

public:
	NeuralNetwork() = default;
	NeuralNetwork(const std::vector<NeuronLayer>& layers);

	std::vector<double> forward(const std::vector<double>& inputs) const;
};
