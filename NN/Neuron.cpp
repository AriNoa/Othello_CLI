#include "Neuron.h"

Neuron::Neuron(const std::vector<double>& weights, const double& bias)
	: _weights(weights)
	, _bias(bias) {
}


double Neuron::forward(const std::vector<double>& inputs) const {
	double dot = 0;
	for (size_t i = 0; i < inputs.size(); i++) {
		dot += _weights[i] * inputs[i];
	}

	return dot + _bias;
}


const std::vector<double>& Neuron::weights() const {
	return _weights;
}

const double& Neuron::bias() const {
	return _bias;
}
