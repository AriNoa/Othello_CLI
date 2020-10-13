#pragma once
#include <random>
#include "Model/Othello.h"
#include "IAgentStrategy.h"

using namespace std;


class RandomBot : public IAgentStrategy {
public:
	virtual Point answer(const Othello& othello) override;
};
