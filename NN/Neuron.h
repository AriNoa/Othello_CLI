#pragma once
#include <vector>


class Neuron {
private:
	std::vector<double> _weights;
	double _bias;
	
public:
	Neuron() = default;
	Neuron(
		const std::vector<double>& weights,
		const double& bias
	);
	
	double forward(const std::vector<double>& inputs) const;
	
	const std::vector<double>& weights() const;
	const double& bias() const;
};