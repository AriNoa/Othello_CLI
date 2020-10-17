#include "ScoreBot.h"

otl::Point ScoreBot::answer(const otl::Othello& othello) {
	using namespace otl;


	std::vector<Point> canPutPoints;
	int maxScore = -1;

	for (int y = 0; y < Othello::height; y++) {
		for (int x = 0; x < Othello::width; x++) {
			const Point pos = { x, y };

			if (!othello.canPutStone(pos)) continue;

			const int& score = scoreBoard[x][y];
			if (score > maxScore) {
				maxScore = score;
				canPutPoints.clear();
			}
			if (score == maxScore) canPutPoints.push_back(pos);
		}
	}

	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<> randSelect(0, (int)canPutPoints.size() - 1);
	const int randIndex = randSelect(mt);

	return canPutPoints[randIndex];
}
