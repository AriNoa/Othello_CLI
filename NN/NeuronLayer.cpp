#include "NeuronLayer.h"


NeuronLayer::NeuronLayer(const std::vector<std::shared_ptr<Neuron>>& neurons) {
	_neurons = neurons;
}


void NeuronLayer::forward() {
	for (auto& neuron : _neurons) { neuron->forward(); }
}

void NeuronLayer::forward(const std::vector<double>& outputs) {
	for (int i = 0; i < _neurons.size(); i++) {
		const double output = outputs[i];

		_neurons[i]->forward(output);
	}
}


const std::vector<std::shared_ptr<Neuron>>& NeuronLayer::getNeurons() {
	return _neurons;
}

std::vector<double> NeuronLayer::getOutputs() {
	std::vector<double> outputs;

	for (const auto& neuron : _neurons) {
		outputs.push_back(neuron->output());
	}
	
	return outputs;
}