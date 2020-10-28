#pragma once
#include <functional>
#include "Neuron.h"


class NeuronLayer {
private:
	std::vector<Neuron> _neurons;
	std::function<double(double)> _activation;

public:
	NeuronLayer() = default;
	NeuronLayer(
		const std::vector<Neuron>& neurons,
		const std::function<double(double)>& activation
	);

	std::vector<double> forward(const std::vector<double>& inputs) const;

	const std::vector<Neuron>& neurons() const;
	const std::function<double(double)>& activation() const;
};