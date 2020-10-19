#pragma once
#include "Neuron.h"


class NeuronLayer {
private:
	std::vector<std::shared_ptr<Neuron>> _neurons;

public:
	NeuronLayer() = default;
	NeuronLayer(const std::vector<std::shared_ptr<Neuron>>& neurons);

	void forward();
	void forward(const std::vector<double>& outputs);

	const std::vector<std::shared_ptr<Neuron>>& getNeurons();
	std::vector<double> getOutputs();
};