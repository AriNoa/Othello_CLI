#pragma once


namespace otl {
	enum class Team {
		None = 0,
		First,
		Second
	};

	inline Team getEnemyTeam(Team myTeam) {
		switch (myTeam) {
		case Team::First:
			return Team::Second;

		case Team::Second:
			return Team::First;

		default:
			return Team::None;
		}
	}
}