#include "NNBot.h"



NNBot::NNBot(const NeuralNetwork& nn) {
	_nn = nn;
}

otl::Point NNBot::answer(const otl::Othello& othello) {
	using namespace std;
	using namespace otl;

	const Team myTeam = othello.getActiveTeam();
	AlphaBetaSearch ab(_nn, myTeam);

	const auto& score = othello.getScore();
	const int stones = score.at(Team::First) + score.at(Team::Second);

	if (64 - fullSearchCount <= stones) return ab.fullSearch(othello);
	
	return ab.search(othello, 3);
}
