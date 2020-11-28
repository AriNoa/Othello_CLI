#include "AlphaBetaSearch.h"
#include <algorithm>

std::vector<otl::Point> AlphaBetaSearch::getMovables(const otl::Othello& othello) {
	using namespace std;
	using namespace otl;

	vector<Point> movables;

	for (int y = 0; y < Othello::height; y++) {
		for (int x = 0; x < Othello::width; x++) {
			const Point pos = { x, y };

			if (othello.canPutStone(pos)) movables.push_back(pos);
		}
	}

	return movables;
}

double AlphaBetaSearch::endEval(
	const otl::Othello& othello,
	double a,
	double b
) {
	using namespace std;
	using namespace otl;
	using namespace nne;

	const Team team = othello.getActiveTeam();

	vector<double> defaultLineEvals;
	LineEvaluation lineEval(_nn, team, othello.getBoard());
	for (const auto& line : BoardEvaluation::lines) {
		defaultLineEvals.push_back(lineEval.evaluate(line));
	}

	BoardEvaluation boardEval(defaultLineEvals, _nn, othello);

	auto movables = getMovables(othello);

	for (const auto& pos : movables) {
		const double e = boardEval.evaluate(pos);
		a = max(a, e);
		if (a >= b) return a;
	}

	return a;
}

double AlphaBetaSearch::alphaBetaEvaluate(
	const otl::Othello& othello,
	const int& depth,
	double a,
	double b
) {
	using namespace std;
	using namespace otl;
	using namespace nne;

	if (depth <= 1) return endEval(othello, a, b);

	const Team team = othello.getActiveTeam();
	const Team nextTeam = getEnemyTeam(team);
	auto movables = getMovables(othello);

	if (movables.empty()) {
		Othello copyOthello = othello;
		copyOthello.setActiveTeam(nextTeam);
		alphaBetaEvaluate(copyOthello, depth - 1, a, b);
	}

	for (const auto& pos : movables) {
		Othello copyOthello = othello;
		copyOthello.updateBoard(pos, team);
		copyOthello.setActiveTeam(nextTeam);

		const double e = alphaBetaEvaluate(copyOthello, depth - 1, a, b);

		if (team == _myTeam) {
			a = max(a, e);
			if (a >= b) return a;
		} else {
			b = min(b, e);
			if (b <= a) return b;
		}
	}

	return team == _myTeam ? a : b;
}

otl::Point AlphaBetaSearch::search(const otl::Othello& othello, const int& depth) {
	using namespace std;
	using namespace otl;
	using namespace nne;

	const Team team = othello.getActiveTeam();
	const Team nextTeam = getEnemyTeam(team);
	auto movables = getMovables(othello);

	double max = DBL_MIN;
	Point putPos = movables.front();

	for (const auto& pos : movables) {
		Othello copyOthello = othello;
		copyOthello.updateBoard(pos, team);
		copyOthello.setActiveTeam(nextTeam);

		const double e = alphaBetaEvaluate(copyOthello, depth - 1, DBL_MIN, DBL_MAX);

		if (e > max) {
			max = e;
			putPos = pos;
		}
	}

	return putPos;
}

int AlphaBetaSearch::fullEval(const otl::Othello& othello) {
	const auto& score = othello.getScore();
	const auto& myScore = score.at(_myTeam);
	const auto& enemyScore = score.at(getEnemyTeam(_myTeam));

	return myScore - enemyScore;
}

int AlphaBetaSearch::alphaBetaFullEvaluate(
	const otl::Othello& othello,
	const bool& passed,
	int a,
	int b
) {
	using namespace std;
	using namespace otl;
	using namespace nne;

	const Team team = othello.getActiveTeam();
	const Team nextTeam = getEnemyTeam(team);
	auto movables = getMovables(othello);

	if (movables.empty()) {
		if (passed) return fullEval(othello);

		Othello copyOthello = othello;
		copyOthello.setActiveTeam(nextTeam);
		alphaBetaFullEvaluate(copyOthello, true, a, b);
	}

	for (const auto& pos : movables) {
		Othello copyOthello = othello;
		copyOthello.updateBoard(pos, team);
		copyOthello.setActiveTeam(nextTeam);

		const int e = alphaBetaFullEvaluate(copyOthello, false, a, b);

		if (team == _myTeam) {
			a = max(a, e);
			if (a >= b) return a;
		} else {
			b = min(b, e);
			if (b <= a) return b;
		}
	}

	return team == _myTeam ? a : b;
}

otl::Point AlphaBetaSearch::fullSearch(const otl::Othello& othello) {
	using namespace std;
	using namespace otl;
	using namespace nne;

	const Team team = othello.getActiveTeam();
	const Team nextTeam = getEnemyTeam(team);
	auto movables = getMovables(othello);

	int max = INT_MIN;
	Point putPos = movables.front();

	for (const auto& pos : movables) {
		Othello copyOthello = othello;
		copyOthello.updateBoard(pos, team);
		copyOthello.setActiveTeam(nextTeam);

		const int e = alphaBetaFullEvaluate(copyOthello, false, INT_MIN, INT_MAX);

		if (e > max) {
			max = e;
			putPos = pos;
		}
	}

	return putPos;
}
