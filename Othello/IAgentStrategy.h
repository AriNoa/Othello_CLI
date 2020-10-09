#pragma once
#include "Model/Othello.h"

using namespace otl;

class IAgentStrategy {
	virtual ~IAgentStrategy() {};

	virtual Point answer(const Othello& othello) = 0;
};