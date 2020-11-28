#pragma once
#include "Othello/AgentStrategy/IAgentStrategy.h"
#include "AlphaBetaSearch.h"


class NNBot : public IAgentStrategy {
public:
	static constexpr int searchDepth = 3;
	static constexpr int fullSearchCount = 12;

private:
	NeuralNetwork _nn;

public:
	NNBot(const NeuralNetwork& nn);

	virtual std::string getName() const { return "NNBot"; }
	virtual otl::Point answer(const otl::Othello& othello) override;
};
