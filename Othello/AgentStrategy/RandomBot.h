#pragma once
#include <random>
#include "IAgentStrategy.h"


class RandomBot : public IAgentStrategy {
public:
	virtual std::string getName() const { return "RandomBot"; }
	virtual otl::Point answer(const otl::Othello& othello) override;
};
