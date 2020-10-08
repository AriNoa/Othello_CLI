#include "Othello.h"


namespace otl {
	Othello::Othello() {
		board = initialBoard;
	}

	std::variant<
		std::pair<std::vector<std::vector<Team>>, Team>,
		std::string
	> Othello::putStone(const Point& point) {
		if (!PointIsInBoard(point)) {
			return "与えられた位置は盤面の外です";
		}

		if (board[point.y][point.x] != Team::None) {
			return "与えられた位置には既に石が置かれています";
		}

		if (!canPutStone(point)) {
			return "与えられた位置に石を置いても石を返すことはできません";
		}

		updateBoard(point, activeTeam);

		activeTeam = getEnemyTeam(activeTeam);
		if (canPutStones()) return std::pair(board, activeTeam);

		activeTeam = getEnemyTeam(activeTeam);
		if (canPutStones()) return std::pair(board, activeTeam);

		return std::pair(board, Team::None);
	}


	bool Othello::canTurnOverLine(const Point& point, const DirVector& dvec) const {
		Point pos = point;
		bool hasEnemyStone = false;

		while (true) {
			pos += dvec;
			if (!PointIsInBoard(pos)) return false;
			const Team p_team = board[pos.y][pos.x];
			if (p_team == Team::None) return false;

			if (p_team == activeTeam) return hasEnemyStone;

			hasEnemyStone = true;
		}

		throw "ここが実行されたら実装が間違ってる";
	}

	bool Othello::canPutStone(const Point& point) const {
		const std::vector<DirVector> dirVecs = {
			{ -1, -1 },	{ 0, -1 },	{ 1, -1 },
			{ -1, 0  },				{ 1, 0  },
			{ -1, 1  },	{ 0, 1  },	{ 1, 1  },
		};

		for (int i = 0; i < 8; i++) {
			if (canTurnOverLine(point, dirVecs[i])) return true;
		}

		return false;
	}

	bool Othello::canPutStones() const {
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				if (canPutStone(Point{ x, y })) return true;
			}
		}

		return false;
	}


	void Othello::updateBoard(const Point& updatePos, const Team& team) {
		board[updatePos.y][updatePos.x] = team;
		score[team] += 1;

		const std::vector<DirVector> dirVecs = {
			{ -1, -1 },	{ 0, -1 },	{ 1, -1 },
			{ -1, 0  },				{ 1, 0  },
			{ -1, 1  },	{ 0, 1  },	{ 1, 1  },
		};

		for (int i = 0; i < 8; i++) {
			const DirVector& dirVec = dirVecs[i];
			if (!canTurnOverLine(updatePos, dirVec)) continue;
			
			Point pos = updatePos;
			while (true) {
				pos += dirVec;
				Team p_team = board[pos.y][pos.x];

				if (p_team == Team::None) break;
				if (p_team == team) break;

				board[pos.y][pos.x] = team;
				score[team] += 1;
				score[getEnemyTeam(team)] -= 1;
			}
		}
	}
};