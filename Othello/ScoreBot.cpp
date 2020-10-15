#include "ScoreBot.h"

Point ScoreBot::answer(const Othello& othello)
{
	std::vector<Point> canPutPoints;
	//std::vector<Point> randomSelectPoints;
	int maxPoint = -1;

	for (int y = 0; y < Othello::height; y++) {
		for (int x = 0; x < Othello::width; x++) {
			const Point pos = { x, y };

			if (!othello.canPutStone(pos)) continue;
			if (scoreBoard[x][y] > maxPoint) {
				maxPoint = scoreBoard[x][y];
				canPutPoints.clear();
			}
			if (scoreBoard[x][y] == maxPoint) canPutPoints.push_back(pos);
		}
	}
	/*
	for (int i = 0; i < canPutPoints.size(); i++) {
		if (maxPoint == scoreBoard[canPutPoints[i].x][canPutPoints[i].y]) {
			randomSelectPoints.push_back(canPutPoints[i]);
		};
	}
	*/
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<> randSelect(0, canPutPoints.size() - 1);
	const int randIndex = randSelect(mt);

	return canPutPoints[randIndex];
}
