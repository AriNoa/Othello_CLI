#include "NNFunctions.h"


std::vector<Neuron::Link> createLinks(
	std::vector<std::shared_ptr<Neuron>> linkedNeurons,
	std::vector<double> weights
) {
	using namespace std;

	vector<Neuron::Link> links;

	for (size_t i = 0; i < linkedNeurons.size(); i++) {
		Neuron::Link link = {
			weak_ptr<Neuron>(linkedNeurons[i]),
			weights[i],
		};

		links.push_back(link);
	}

	return links;
}

std::vector<std::shared_ptr<Neuron>> createNeurons(
	std::vector<NeuronModel> layer,
	std::vector<std::shared_ptr<Neuron>> linkedNeurons
) {
	using namespace std;
	vector<shared_ptr<Neuron>> neurons;

	for (const auto& neuron : layer) {
		vector<Neuron::Link> links = createLinks(linkedNeurons, neuron.weights);

		shared_ptr<Neuron> neuron_ptr(new Neuron(
			links, neuron.bias
		));

		neurons.push_back(neuron_ptr);
	}

	return neurons;
}

NeuralNetwork createNN(const std::vector<std::vector<NeuronModel>>& nn) {
	using namespace std;

	vector<NeuronLayer> layers;
	vector<shared_ptr<Neuron>> linkedNeurons;

	for (const auto& layer : nn) {
		vector<std::shared_ptr<Neuron>> neurons = createNeurons(layer, linkedNeurons);

		layers.push_back(NeuronLayer(neurons));
		linkedNeurons = neurons;
	}

	return NeuralNetwork(layers);
}