#pragma once
#include <vector>
#include <map>
#include <utility>
#include <variant>
#include <string>
#include "Point.h"
#include "Team.hpp"
#include "DirVector.hpp"


namespace otl {
	class Othello {
	public:
		static constexpr int width = 8;
		static constexpr int height = 8;

#define N Team::None
#define F Team::First
#define S Team::Second
		static inline const std::vector<std::vector<Team>> initialBoard = {
			{N, N, N, N, N, N, N, N},
			{N, N, N, N, N, N, N, N},
			{N, N, N, N, N, N, N, N},
			{N, N, N, S, F, N, N, N},
			{N, N, N, F, S, N, N, N},
			{N, N, N, N, N, N, N, N},
			{N, N, N, N, N, N, N, N},
			{N, N, N, N, N, N, N, N},
		};
#undef N
#undef F
#undef S

		static constexpr bool PointIsInBoard(Point point) {
			return
				0 <= point.x && point.x < width &&
				0 <= point.y && point.y < height;
		}

	private:
		std::vector<std::vector<Team>> board;
		Team activeTeam = Team::First;
		std::map<Team, int> score = {
			{Team::First,	2},
			{Team::Second,	2},
		};

	public:
		Othello();

		std::variant<
			std::pair<std::vector<std::vector<Team>>, Team>,
			std::string
		> putStone(const Point& point);

		inline std::vector<std::vector<Team>> getBoard() const { return board; }
		constexpr Team getActiveTeam() const { return activeTeam; }
		inline std::map<Team, int> getScore() const { return score; }

		bool canTurnOverLine(const Point& point, const DirVector& dvec) const;
		bool canTurnOverStone(const Point& point) const;
		bool canTurnOverStones() const;
		bool canPutStone(const Point& point) const;

		void updateBoard(const Point& updatePos, const Team& team);
	};
}