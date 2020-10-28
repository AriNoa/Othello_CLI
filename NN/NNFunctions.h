#pragma once
#include "NeuralNetwork.h"


struct NeuronModel {
	std::vector<double> weights;
	double bias;
};


NeuronLayer createLayer(
	const std::vector<NeuronModel>& neuronModels,
	const std::function<double(const double&)>& activation
);

NeuralNetwork createNN(
	const std::vector<std::vector<NeuronModel>>& nn,
	const std::function<double(const double&)>& activation
);