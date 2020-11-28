#pragma once
#include "Othello/AgentStrategy/NNBot/NNEval.h"


class AlphaBetaSearch {
	static std::vector<otl::Point> getMovables(const otl::Othello& othello);

private:
	const NeuralNetwork& _nn;
	const otl::Team& _myTeam;

public:
	AlphaBetaSearch(
		const NeuralNetwork& nn,
		const otl::Team& myTeam
	) :_nn(nn), _myTeam(myTeam) {}

	double endEval(
		const otl::Othello& othello,
		double a,
		double b
	);

	double alphaBetaEvaluate(
		const otl::Othello& othello,
		const int& depth,
		double a,
		double b
	);

	otl::Point search(
		const otl::Othello& othello,
		const int& depth
	);
};