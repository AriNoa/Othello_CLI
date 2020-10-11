#pragma once
#include <random>
#include <vector>
#include "Model/Point.h"
#include "IAgentStrategy.h"

class RandomBot : public IAgentStrategy {
public:
	virtual ~RandomBot() {}
	virtual Point answer(const Othello& othello) override;
};
