#include "RandomBot.h"


Point RandomBot::answer(const Othello& othello) {
	std::vector<Point> canPutPoints;
	
	for (int y = 0; y < Othello::height; y++) {
		for (int x = 0; x < Othello::width; x++) {
			const Point pos = { x, y };

			if (othello.canPutStone(pos)) canPutPoints.push_back(pos);
		}
	}

	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<> randSelect(0, (int)canPutPoints.size()-1);
	const int randIndex = randSelect(mt);

	return canPutPoints[randIndex];
}
