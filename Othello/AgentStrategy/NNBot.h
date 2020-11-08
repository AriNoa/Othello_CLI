#pragma once
#include "IAgentStrategy.h"
#include "NN/NeuralNetwork.h"


class NNBot : public IAgentStrategy {
private:
	NeuralNetwork _nn;

public:
	NNBot(const NeuralNetwork& nn);

	std::pair<double, double> getInput(const otl::Team& myTeam, const otl::Team& team) const;
	std::vector<double> getInputs(const otl::Team& myTeam, const std::vector<std::vector<otl::Team>>& board) const;

	virtual std::string getName() const { return "NNBot"; }
	virtual otl::Point answer(const otl::Othello& othello) override;
};
