#pragma once
#include <random>
#include "IAgentStrategy.h"


class RandomBot : public IAgentStrategy {
public:
	virtual Point answer(const Othello& othello) override;
};
