#include "NEBot.h"


NEBot::NEBot(const NeuralNetwork& nn) {
	_nn = nn;
}

otl::Point NEBot::answer(const otl::Othello& othello) {
	using namespace std;
	using namespace otl;
	using namespace nne;

	const Team myTeam = othello.getActiveTeam();

	const auto& score = othello.getScore();
	const int stones = score.at(Team::First) + score.at(Team::Second);

	if (64 - fullSearchCount <= stones) {
		AlphaBetaSearch ab(_nn, myTeam);
		return ab.fullSearch(othello);
	}

	vector<double> defaultLineEvals;
	LineEvaluation lineEval(_nn, myTeam, othello.getBoard());
	for (const auto& line : BoardEvaluation::lines) {
		defaultLineEvals.push_back(lineEval.evaluate(line));
	}

	BoardEvaluation boardEval(defaultLineEvals, _nn, othello);

	double max = -1;
	Point maxPos;

	for (int y = 0; y < Othello::height; y++) {
		for (int x = 0; x < Othello::width; x++) {
			const Point pos = { x, y };

			if (!othello.canPutStone(pos)) continue;

			const double eval = boardEval.evaluate(pos);

			if (eval > max) {
				max = eval;
				maxPos = pos;
			}
		}
	}

	return maxPos;
}
