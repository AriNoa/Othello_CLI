#include "RandomBot.h"


Point RandomBot::answer(const Othello& othello) {
	Point pos;
	int _x = 0, _y = 0;
	int select;

	int data[64][2] = { 0 };

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {

			pos.x = i;
			pos.y = j;

			if (othello.canPutStone(pos)) {
				data[_x][_y++] = i;
				data[_x++][_y--] = j;
			}
		}
	}

	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<> randSelect(0, _x);
	select = randSelect(mt);

	pos.x = data[select][0];
	pos.y = data[select][1];

	return pos;
}
