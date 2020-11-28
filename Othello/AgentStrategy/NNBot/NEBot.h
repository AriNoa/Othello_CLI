#pragma once
#include "Othello/AgentStrategy/IAgentStrategy.h"
#include "AlphaBetaSearch.h"


class NEBot : public IAgentStrategy {
private:
	NeuralNetwork _nn;

public:
	NEBot(const NeuralNetwork& nn);

	virtual std::string getName() const { return "NEBot"; }
	virtual otl::Point answer(const otl::Othello& othello) override;
};
