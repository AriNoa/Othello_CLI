#include "NeuronLayer.h"

NeuronLayer::NeuronLayer(const std::vector<Neuron>& neurons, const std::function<double(double)>& activation) {
	_neurons = neurons;
	_activation = activation;
}

std::vector<double> NeuronLayer::forward(const std::vector<double>& inputs) const {
	std::vector<double> outputs;

	for (const auto& neuron : _neurons){
		const double output = neuron.forward(inputs);
		outputs.push_back(
			_activation(output)
		);
	}

	return outputs;
}

const std::vector<Neuron>& NeuronLayer::neurons() const {
	return _neurons;
}

const std::function<double(double)>& NeuronLayer::activation() const {
	return _activation;
}
