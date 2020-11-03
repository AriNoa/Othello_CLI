#include "ParseFunctions.h"
#include <cmath>


NeuralNetwork toNN(const std::vector<double>& genome, const size_t& inputSize, const std::vector<size_t>& nnSize) {
	size_t frontSize = inputSize;
	size_t index = 0;

	std::vector<std::vector<NeuronModel>> nn;

	for (size_t layerIndex = 0; layerIndex < nnSize.size(); layerIndex++) {
		std::vector<NeuronModel> layer;

		for (size_t neuronIndex = 0; neuronIndex < nnSize[layerIndex]; neuronIndex++) {
			std::vector<double> weights;

			for (size_t weightIndex = 0; weightIndex < frontSize; weightIndex++) {
				weights.push_back(genome[index]);
				index++;
			}

			const NeuronModel neuron = { weights, genome[index] };
			index++;

			layer.push_back(neuron);
		}

		nn.push_back(layer);
	}

	auto activation = [](const double& x) -> double { return 1.0 / (1.0 + std::exp(-x)); };
	return createNN(nn, activation);
}

std::vector<double> toGenome(const NeuralNetwork& nn) {
	std::vector<double> genome;

	for (const auto& layer : nn.layers()) {
		for (const auto& neuron : layer.neurons()) {
			for (const auto& weight : neuron.weights()) {
				genome.push_back(weight);
			}

			genome.push_back(neuron.bias());
		}
	}

	return genome;
}