#include "RandomBot.h"


Point RandomBot::answer(const Othello& othello) {
	std::vector<Point> canPutPoints;

	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			Point pos = { x, y };

			if (othello.canPutStone(pos)) canPutPoints.push_back(pos);
		}
	}

	const int randIndex = rand() % canPutPoints.size();
	return canPutPoints[randIndex];
}
