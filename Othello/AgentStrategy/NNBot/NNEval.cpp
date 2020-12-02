#include "NNEval.h"


nne::LineEvaluation::LineEvaluation(
	const NeuralNetwork& nn,
	const otl::Team& myTeam,
	const otl::Othello::BoardType& board
)	: _nn(nn)
	, _myTeam(myTeam)
	, _board(board) {
}

std::pair<double, double> nne::LineEvaluation::getInput(const otl::Team& team) const {
	if (team == otl::Team::None) return { 0, 0 };
	if (team == _myTeam) return { 0, 1 };
	return { 1, 0 };
}

std::vector<double> nne::LineEvaluation::getInputs(const Line& line) const {
	std::vector<double> inputs;

	for (size_t i = 0; i < line.length; i++) {
		const otl::Point pos = line.corner + line.dir * (int)i;

		const auto input = getInput(_board[pos.y][pos.x]);

		inputs.push_back(input.first);
		inputs.push_back(input.second);
	}

	return inputs;
}

double nne::LineEvaluation::evaluate(const Line& line) const {
	const auto inputs = getInputs(line);

	return _nn.forward(inputs).front();
}


std::vector<nne::Line> nne::BoardEvaluation::initLines(const size_t& length) {
	using namespace std;
	using namespace otl;

	std::vector<nne::Line> lines;

	const size_t XB = 0;
	const size_t YB = 0;
	const size_t XE = Othello::width - 1;
	const size_t YE = Othello::height - 1;

	const vector<pair<Point, DirVector>> vecs = {
		{{XB, YB}, { 1,  1}},
		{{XB, YE}, { 1, -1}},
		{{XE, YB}, {-1,  1}},
		{{XE, YE}, {-1, -1}},
	};

	for (const auto& vec : vecs) {
		const otl::Point& corner = vec.first;
		const int& dx = vec.second.x;
		const int& dy = vec.second.y;
		lines.push_back({ corner, {dx, dy}, length });
		lines.push_back({ corner, { 0, dy}, length });
		lines.push_back({ corner, {dx,  0}, length });
	}

	return lines;
}

nne::BoardEvaluation::Board<std::vector<size_t>> nne::BoardEvaluation::initLineIndexBoard(
	const std::vector<nne::Line>& lines
) {
	using namespace std;
	using namespace otl;

	Board<vector<size_t>> indexBoard = Board<vector<size_t>>(
		Othello::height, vector<vector<size_t>>(Othello::width)
	);

	for (size_t index = 0; index < lines.size(); index++) {
		const Line& line = lines[index];
		const Point& corner = line.corner;
		const DirVector& dir = line.dir;

		for (size_t i = 0; i < line.length; i++) {
			const Point& pos = corner + dir * (int)i;

			indexBoard[pos.y][pos.x].push_back(index);
		}
	}

	return indexBoard;
}

nne::BoardEvaluation::BoardEvaluation(
	const std::vector<double>& defaultLineEvals,
	const NeuralNetwork& nn,
	const otl::Othello& othello
)	: _defaultLineEvals(defaultLineEvals)
	, _nn(nn)
	, _othello(othello)
	, _defaultEvalSum(calculateEvalSum(_defaultLineEvals)) {
	_evalSum = _defaultEvalSum;
	_linesIgnore = std::vector<bool>(lines.size(), false);
}

void nne::BoardEvaluation::pointEval(const otl::Point& pos, const LineEvaluation& lineEval) {
	for (const auto& index : lineIndexBoard[pos.y][pos.x]) {
		if (_linesIgnore[index]) continue;

		const Line& line = lines[index];
		const double eval = lineEval.evaluate(line);
		_evalSum += eval - _defaultLineEvals[index];

		_linesIgnore[index] = true;
	}
}

double nne::BoardEvaluation::evaluate(const otl::Point& putPos) {
	using namespace std;
	using namespace otl;

	_evalSum = _defaultEvalSum;
	_linesIgnore = std::vector<bool>(lines.size(), false);

	const auto dirVecs = createDirVectors();
	const Othello::BoardType& board = _othello.getBoard();
	const Team& myTeam = _othello.getActiveTeam();

	Othello copyOthello = _othello;
	copyOthello.putStone(putPos);
	const Othello::BoardType& nextBoard = copyOthello.getBoard();

	const LineEvaluation lineEval(_nn, myTeam, nextBoard);

	pointEval(putPos, lineEval);

	for (const auto& dir : dirVecs) {
		if (!_othello.canTurnOverLine(putPos, dir)) continue;

		size_t i = 0;
		while (true) {
			i++;
			Point pos = putPos + dir * (int)i;
			if (board[pos.y][pos.x] == myTeam) break;
			pointEval(pos, lineEval);
		}
	}

	return _evalSum;
}