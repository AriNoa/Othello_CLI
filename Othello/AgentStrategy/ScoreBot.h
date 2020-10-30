#pragma once
#include <random>
#include "Othello/Model/Othello.h"
#include "IAgentStrategy.h"

class ScoreBot : public IAgentStrategy {
	static const inline std::vector<std::vector<int>> scoreBoard = {
		{5, 1, 4, 4, 4, 4, 1, 5},
		{1, 0, 4, 3, 3, 4, 0, 1},
		{4, 4, 4, 3, 3, 4, 4, 4},
		{4, 3, 3, 3, 3, 3, 3, 4},
		{4, 3, 3, 3, 3, 3, 3, 4},
		{4, 4, 4, 3, 3, 4, 4, 4},
		{1, 0, 4, 3, 3, 4, 0, 1},
		{5, 1, 4, 4, 4, 4, 1, 5}
	};

public:
	virtual std::string getName() const { return "ScoreBot"; }
	virtual otl::Point answer(const otl::Othello& othello) override;
};
