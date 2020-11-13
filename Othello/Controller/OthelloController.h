#pragma once
#include <memory>
#include <optional>
#include "Othello/View/OthelloViewInterface.h"
#include "Othello/AgentStrategy/IAgentStrategy.h"

class OthelloController {
private:
	otl::Othello _othello;
	std::map<otl::Team, std::shared_ptr<IAgentStrategy>> _agents;
	std::shared_ptr<OthelloViewInterface> _view;

public:
	OthelloController() = default;
	OthelloController(
		const std::map<otl::Team, std::shared_ptr<IAgentStrategy>>& agents,
		const std::shared_ptr<OthelloViewInterface>& view
	);

	std::optional<otl::Othello> run();
	
	const otl::Othello& getOthello() const;
};