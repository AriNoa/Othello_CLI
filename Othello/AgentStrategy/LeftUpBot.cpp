#include "LeftUpBot.h"


otl::Point LeftUpBot::answer(const otl::Othello& othello) {
	using namespace otl;
	
	const auto board = othello.getBoard();

	for (int y = 0; y < Othello::height; y++) {
		for (int x = 0; x < Othello::width; x++) {
			const Point pos = { x, y };

			if (othello.canPutStone(pos)) return pos;
		}
	}

	return { 0, 0 };
}
