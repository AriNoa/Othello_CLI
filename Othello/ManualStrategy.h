#pragma once
#include <random>
#include "IAgentStrategy.h"



class ManualStrategy : public IAgentStrategy {
public:
	virtual Point answer(const Othello& othello) override;
};
