#pragma once
#include "IAgentStrategy.h"


class LeftUpBot : public IAgentStrategy {
public:
	virtual std::string getName() const { return "LeftUp"; }
	virtual otl::Point answer(const otl::Othello& othello) override;
};
