#pragma once
#include "Othello.h"

using namespace otl;

class IAgentStrategy {
	virtual ~IAgentStrategy() = 0;

	virtual Point answer(const Othello& othello) = 0;
};