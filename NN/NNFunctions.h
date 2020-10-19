#pragma once
#include "NeuralNetwork.h"


struct NeuronModel {
	std::vector<double> weights;
	double bias;
};


std::vector<Neuron::Link> createLinks(
	std::vector<std::shared_ptr<Neuron>> linkedNeurons,
	std::vector<double> weights
);

std::vector<std::shared_ptr<Neuron>> createNeurons(
	std::vector<NeuronModel> layer,
	std::vector<std::shared_ptr<Neuron>> linkedNeurons
);

NeuralNetwork createNN(const std::vector<std::vector<NeuronModel>>& nn);