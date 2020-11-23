#include "Othello.h"
#include <iostream>


namespace otl {
	Othello::Othello() {
		_board = initialBoard;
	}

	Othello::Othello(const std::vector<std::vector<Team>>& board, const Team& activeTeam) {
		_board = board;
		_activeTeam = activeTeam;
		_score = {
			{Team::First,	0},
			{Team::Second,	0},
		};

		for (size_t y = 0; y < height; y++) {
			for (size_t x = 0; x < width; x++) {
				const Team& team = _board[y][x];

				if (team != Team::None) continue;

				_score[team]++;
			}
		}
	}

	std::variant<
		std::pair<std::vector<std::vector<Team>>, Team>,
		std::string
	> Othello::putStone(const Point& point) {
		if (!PointIsInBoard(point)) {
			return "与えられた位置は盤面の外です";
		}

		if (_board[point.y][point.x] != Team::None) {
			return "与えられた位置には既に石が置かれています";
		}

		if (!canTurnOverStone(point)) {
			return "与えられた位置に石を置いても石を返すことはできません";
		}

		updateBoard(point, _activeTeam);

		_activeTeam = getEnemyTeam(_activeTeam);
		if (canPutStones()) return std::pair(_board, _activeTeam);

		_activeTeam = getEnemyTeam(_activeTeam);
		if (canPutStones()) return std::pair(_board, _activeTeam);

		_activeTeam = Team::None;
		return std::pair(_board, _activeTeam);
	}


	bool Othello::canTurnOverLine(const Point& point, const DirVector& dvec) const {
		Point pos = point;
		bool hasEnemyStone = false;

		while (true) {
			pos += dvec;
			if (!PointIsInBoard(pos)) return false;
			const Team p_team = _board[pos.y][pos.x];
			if (p_team == Team::None) return false;

			if (p_team == _activeTeam) return hasEnemyStone;

			hasEnemyStone = true;
		}
	}

	bool Othello::canTurnOverStone(const Point& point) const {
		const std::vector<DirVector> dirVecs = otl::createDirVectors();

		for (int i = 0; i < 8; i++) {
			if (canTurnOverLine(point, dirVecs[i])) return true;
		}

		return false;
	}

	bool Othello::canPutStone(const Point& point) const {
		if (!PointIsInBoard(point)) return false;

		if (_board[point.y][point.x] != Team::None) return false;

		if (!canTurnOverStone(point)) return false;

		return true;
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
		_board[updatePos.y][updatePos.x] = team;
		_score[team] += 1;

		const std::vector<DirVector> dirVecs = otl::createDirVectors();

		for (int i = 0; i < 8; i++) {
			const DirVector& dirVec = dirVecs[i];
			if (!canTurnOverLine(updatePos, dirVec)) continue;
			
			Point pos = updatePos;
			while (true) {
				pos += dirVec;
				Team p_team = _board[pos.y][pos.x];

				if (p_team == Team::None) break;
				if (p_team == team) break;

				_board[pos.y][pos.x] = team;
				_score[team] += 1;
				_score[getEnemyTeam(team)] -= 1;
			}
		}
	}
};