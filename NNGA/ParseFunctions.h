#pragma once
#include "NN/NNFunctions.h"


NeuralNetwork toNN(
	const std::vector<double>& genome,
	const size_t& inputSize,
	const std::vector<size_t>& nnSize
);

std::vector<double> toGenome(const NeuralNetwork& nn);