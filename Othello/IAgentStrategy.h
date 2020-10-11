#pragma once
#include "Model/Othello.h"

using namespace otl;

class IAgentStrategy {
public:
	virtual ~IAgentStrategy() {};

	virtual otl::Point answer(const otl::Othello& othello) = 0;
};