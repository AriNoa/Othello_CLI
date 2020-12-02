#pragma once
#include <array>
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

		using BoardType = std::array<std::array<otl::Team, width>, height>;

#define N Team::None
#define F Team::First
#define S Team::Second
		static inline const BoardType initialBoard = {
			std::array<otl::Team, width>
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
		BoardType _board;
		Team _activeTeam = Team::First;
		std::map<Team, int> _score = {
			{Team::First,	2},
			{Team::Second,	2},
		};

	public:
		Othello();
		Othello(
			const BoardType& board,
			const Team& activeTeam
		);

		std::variant<
			std::pair<BoardType, Team>,
			std::string
		> putStone(const Point& point);

		inline const BoardType& getBoard() const { return _board; }
		constexpr const Team& getActiveTeam() const { return _activeTeam; }
		inline const std::map<Team, int>& getScore() const { return _score; }

		bool canTurnOverLine(const Point& point, const DirVector& dvec) const;
		bool canTurnOverStone(const Point& point) const;
		bool canPutStone(const Point& point) const;
		bool canPutStones() const;

		void updateBoard(const Point& updatePos, const Team& team);

		void setBoard(const BoardType& board);
		void setActiveTeam(const Team& activeTeam);
	};
}