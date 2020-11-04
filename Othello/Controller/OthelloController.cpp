#include "OthelloController.h"

OthelloController::OthelloController(const std::map<otl::Team, std::shared_ptr<IAgentStrategy>> agents) {
	using namespace std;
	using namespace otl;

	_othello = Othello();
	_agents = agents;

	map<Team, string> teamNames;
	for (auto const& [t, a] : agents) { teamNames[t] = a->getName(); }
	_view = OthelloView(teamNames);
}

std::optional<otl::Othello> OthelloController::run() {
    using namespace std;
    using namespace otl;

    while (true) {
        _view.drawOthello(_othello);

        const Team activeTeam = _othello.getActiveTeam();
        if (activeTeam == Team::None) return _othello;

        const Point putPos = _agents[activeTeam]->answer(_othello);
        _view.drawAnswer(putPos);

        auto putResult = _othello.putStone(putPos);

        if (holds_alternative<string>(putResult)) {
            _view.drawException(get<string>(putResult));
            return nullopt;
        }
    }
}

const otl::Othello& OthelloController::getOthello() const {
    return _othello;
}
