#pragma once
#include "Othello/Model/Othello.h"


class IAgentStrategy {
public:
	virtual ~IAgentStrategy() {};

	virtual std::string getName() const = 0;
	virtual otl::Point answer(const otl::Othello& othello) = 0;
};