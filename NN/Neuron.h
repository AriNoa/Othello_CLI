#pragma once
#include <vector>
#include <memory>
#include <cmath>


class Neuron {
public:
	struct Link {
		std::weak_ptr<Neuron> Neuron;
		double weight;
	};
	
private:
	std::vector<Link> _inputLinks;
	double _bias = 0;
	double _outputValue = 0;
	
public:
	Neuron() = default;
    Neuron(
		const std::vector<Link>& inputLinks,
		const double& bias
	);

	inline double sigmoid(const double& x) {
		return x > 0 ? 1 : 0;
	}
	
	void forward();
	void forward(const double& outputValue);
	
	const std::vector<Link>& getLinks() const;
	const double& output() const;
};