#pragma once
#include <random>
#include "IAgentStrategy.h"


class RandomBot : public IAgentStrategy {
public:
	virtual std::string getName() const { return "RandomBot"; }
	virtual Point answer(const Othello& othello) override;
};
