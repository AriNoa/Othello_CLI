#include "Neuron.h"


Neuron::Neuron(
	const std::vector<Link>& inputLinks,
	const double& bias
) {
	_inputLinks = inputLinks;
	_bias = bias;
}


void Neuron::forward() {
    double sum = 0;
    for(const auto& link : _inputLinks) {
		const double x = link.Neuron.lock()->output();
		const double w = link.weight;
        sum += x*w;
    }
	
	forward(
		sigmoid(sum + _bias)
	);
}

void Neuron::forward(const double& outputValue) {
	_outputValue = outputValue;
}


const std::vector<Neuron::Link>& Neuron::getLinks() const {
	return _inputLinks;
}

const double& Neuron::output() const {
	return _outputValue;
}