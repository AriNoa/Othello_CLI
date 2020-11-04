#include "NNBot.h"


NNBot::NNBot(const NeuralNetwork& nn) {
	_nn = nn;
}


std::pair<double, double> NNBot::getInput(const otl::Team& team) const {
	if (team == otl::Team::None) return { 0, 0 };
	if (team == _myTeam) return { 0, 1 };
	return { 1, 0 };
}

std::vector<double> NNBot::getInputs(const std::vector<std::vector<otl::Team>>& board) const {
	std::vector<double> inputs;

	for (int y = 0; y < board.size(); y++) {
		for (int x = 0; x < board[y].size(); x++) {
			const auto input = getInput(board[y][x]);

			inputs.push_back(input.first);
			inputs.push_back(input.second);
		}
	}

	return inputs;
}


otl::Point NNBot::answer(const otl::Othello& othello) {
	using namespace std;
	using namespace otl;

	const auto board = othello.getBoard();

	double max = 0;
	Point maxPos;

	for (int y = 0; y < Othello::height; y++) {
		for (int x = 0; x < Othello::width; x++) {
			const Point pos = { x, y };

			if (!othello.canPutStone(pos)) continue;

			Othello copyOthello = othello;
			copyOthello.putStone(pos);

			const auto inputs = getInputs(copyOthello.getBoard());
			const double output = _nn.forward(inputs).front();

			if (output > max) {
				max = output;
				maxPos = pos;
			}
		}
	}

	return maxPos;
}
