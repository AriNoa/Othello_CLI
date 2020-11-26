#pragma once
#include "Othello/AgentStrategy/IAgentStrategy.h"
#include "NNEval.h"




class NNBot : public IAgentStrategy {
private:
	NeuralNetwork _nn;

public:
	NNBot(const NeuralNetwork& nn);

	virtual std::string getName() const { return "NNBot"; }
	virtual otl::Point answer(const otl::Othello& othello) override;
};
