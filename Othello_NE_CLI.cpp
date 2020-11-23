#include <iostream>
#include <iomanip>
#include <random>
#include <fstream>
#include "Othello/Controller/OthelloController.h"
#include "Othello/View/OthelloView.h"
#include "Othello/View/OthelloExceptionView.h"
#include "Othello/AgentStrategy/NNBot.h"
#include "Othello/AgentStrategy/ManualStrategy.h"
#include "Othello/AgentStrategy/RandomBot.h"
#include "Othello/AgentStrategy/ScoreBot.h"
#include "Othello/AgentStrategy/LeftUpBot.h"
#include "GA/GeneticAlgorithm.h"
#include "NE/ParseFunctions.h"


std::vector<double> createGenome(
    const size_t& inputSize,
    const std::vector<size_t>& nnSize
) {
	std::vector<double> genome;
    size_t frontSize = inputSize;

	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_real_distribution<> rand(-1, 1);

	for (size_t layerIndex = 0; layerIndex < nnSize.size(); layerIndex++) {
		for (size_t neuronIndex = 0; neuronIndex < nnSize[layerIndex]; neuronIndex++) {
			for (size_t weightIndex = 0; weightIndex < frontSize; weightIndex++) {
				genome.push_back(rand(mt));
			}

			genome.push_back(rand(mt));
		}
	}

	return genome;
}

otl::Team getWiener(const std::map<otl::Team, int>& score) {
	using namespace otl;
	const int& fScore = score.at(Team::First);
	const int& sScore = score.at(Team::Second);

	if (fScore > sScore) return Team::First;
	if (fScore < sScore) return Team::Second;
	
	return Team::None;
}


int main() {
    using namespace std;
    using namespace otl;

	cout << "Othello_NE_CLI" << endl;

	vector<shared_ptr<IAgentStrategy>> randomBots(4, make_shared<RandomBot>());
	vector<shared_ptr<IAgentStrategy>> enemyAgents = {
		make_shared<ScoreBot>(),
		make_shared<LeftUpBot>()
	};

	enemyAgents.insert(
		enemyAgents.cend(), randomBots.begin(), randomBots.end()
	);
			
    const size_t inputSize = 6;
    const std::vector<size_t> nnSize = { 8, 1 };

	std::vector<std::shared_ptr<std::vector<double>>> genomes;

	for (size_t ind = 0; ind < 50; ind++) {
		auto genome = make_shared<std::vector<double>>(
			createGenome(inputSize, nnSize)
		);

		genomes.push_back(genome);
	}

	GeneticAlgorithm gg(genomes);

	vector<NeuralNetwork> nns;
	for (const auto& genome : genomes) {
		nns.push_back(
			toNN(*genome, inputSize, nnSize)
		);
	}

	std::shared_ptr<OthelloViewInterface> exceptionView = make_shared<OthelloExceptionView>();

	for (size_t generation = 0; generation < 100; generation++) {
		vector<shared_ptr<IAgentStrategy>> bots;
		for (const auto& nn : nns) {
			bots.push_back(make_shared<NNBot>(nn));
		}

		vector<int> evals(bots.size(), 0);

		for (size_t fIndex = 0; fIndex < bots.size(); fIndex++) {
			for (size_t sIndex = 0; sIndex < bots.size(); sIndex++) {
				if (fIndex == sIndex) continue;

				map<Team, shared_ptr<IAgentStrategy>> agents = {
					{ Team::First,  bots[fIndex] },
					{ Team::Second, bots[sIndex] }
				};

				OthelloController controller(agents, exceptionView);

				auto othello_opt = controller.run();
				if (!othello_opt) return 1;

				const Othello othello = othello_opt.value();
				const Team winner = getWiener(othello.getScore());

				if (winner == Team::First)	evals[fIndex]++;
				if (winner == Team::Second) evals[sIndex]++;
			}

			for (auto enemy : enemyAgents) {
				map<Team, shared_ptr<IAgentStrategy>> agents = {
					{ Team::First,  bots[fIndex] },
					{ Team::Second, enemy }
				};

				OthelloController controller(agents, exceptionView);

				auto othello_opt = controller.run();
				if (!othello_opt) return 1;

				const Othello othello = othello_opt.value();
				const Team winner = getWiener(othello.getScore());

				if (winner == Team::First)	evals[fIndex] += 2;
			}
		}

		nns.clear();
		genomes = gg.evolution(evals);
		for (const auto& genome : genomes) {
			nns.push_back(
				toNN(*genome, inputSize, nnSize)
			);
		}

		if (generation % 1 == 0) {
			cout << generation << "世代: " << setprecision(4) << evals.back() << endl;

			std::ofstream ofs("NN.txt");
			if (!ofs) return 1;
			ofs << toText(*genomes.back());
		}
	}

	shared_ptr<IAgentStrategy> manual(new ManualStrategy());
	shared_ptr<IAgentStrategy> nnAgent(new NNBot(nns.back()));

	map<Team, shared_ptr<IAgentStrategy>> agents = {
		{ Team::First,  manual },
		{ Team::Second, nnAgent }
	};

	std::shared_ptr<OthelloViewInterface> view = make_shared<OthelloView>(
		map<otl::Team, std::string>({
			{ Team::First,  "Player" },
			{ Team::Second, "NN_Agent" }
		})
	);
	OthelloController controller(agents, view);

	controller.run();


    return 0;
}
