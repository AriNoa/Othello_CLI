#pragma once
#include <memory>
#include <optional>
#include "Othello/View/OthelloView.h"
#include "Othello/AgentStrategy/IAgentStrategy.h"

class OthelloController {
private:
	otl::Othello _othello;
	std::map<otl::Team, std::shared_ptr<IAgentStrategy>> _agents;
	OthelloView _view;

public:
	OthelloController() = default;
	OthelloController(const std::map<otl::Team, std::shared_ptr<IAgentStrategy>> agents);

	std::optional<otl::Othello> run();
	
	const otl::Othello& getOthello() const;
};