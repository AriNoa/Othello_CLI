#include "NNBot.h"



NNBot::NNBot(const NeuralNetwork& nn) {
	_nn = nn;
}

otl::Point NNBot::answer(const otl::Othello& othello) {
	using namespace std;
	using namespace otl;

	const Team myTeam = othello.getActiveTeam();
	AlphaBetaSearch ab(_nn, myTeam);
	
	return ab.search(othello, 3);
}
