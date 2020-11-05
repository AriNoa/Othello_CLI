#include <iostream>
#include <iomanip>
#include <random>
#include "Othello/Controller/OthelloController.h"
#include "Othello/AgentStrategy/NNBot.h"
#include "Othello/AgentStrategy/ManualStrategy.h"
#include "GA/GeneticAlgorithm.h"
#include "NNGA/ParseFunctions.h"


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

int main() {
    using namespace std;
    using namespace otl;

    const size_t inputSize = 128;
    const std::vector<size_t> nnSize = { 128, 1 };

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

	for (size_t generation = 0; generation < 100; generation++) {
		vector<shared_ptr<IAgentStrategy>> bots;
		for (const auto& nn : nns) {
			bots.push_back(make_shared<NNBot>(nn));
		}

		vector<int> evals(bots.size(), 0);

		for (size_t bIndex = 0; bIndex < bots.size(); bIndex++) {
			for (size_t eIndex = 0; eIndex < bots.size(); eIndex++) {
				if (bIndex == eIndex) continue;

				map<Team, shared_ptr<IAgentStrategy>> agents = {
					{ Team::First,  bots[bIndex] },
					{ Team::Second, bots[eIndex] }
				};

				Othello othello;

				while (true) {
					const Team activeTeam = othello.getActiveTeam();
					if (activeTeam == Team::None) break;

					const Point putPos = agents[activeTeam]->answer(othello);

					auto putResult = othello.putStone(putPos);

					if (holds_alternative<string>(putResult)) {
						cout << endl << putPos.x << ", " << putPos.y;
						cout << endl << get<string>(putResult) << endl;
						//return 1;
						break;
					}
				}

				const auto score = othello.getScore();
				const int& fScore = score.at(Team::First);
				const int& sScore = score.at(Team::Second);

				if (fScore == sScore) continue;

				if (fScore > sScore) {
					evals[bIndex]++;
				} else {
					evals[eIndex]++;
				}
			}
		}

		if (generation % 10 == 0) {
			cout << generation << "世代: " << setprecision(4) << evals.back() << endl;
		}

		nns.clear();
		genomes = gg.evolution(evals);
		for (const auto& genome : genomes) {
			nns.push_back(
				toNN(*genome, inputSize, nnSize)
			);
		}
	}

	shared_ptr<IAgentStrategy> manual(new ManualStrategy());
	shared_ptr<IAgentStrategy> nnAgent(new NNBot(nns.back()));

	map<Team, shared_ptr<IAgentStrategy>> agents = {
		{ Team::First,  manual },
		{ Team::Second, nnAgent }
	};

	OthelloController controller(agents);

	controller.run();


    return 0;
}
