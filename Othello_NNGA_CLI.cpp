#include <iostream>
#include <iomanip>
#include <random>
#include "Othello/Controller/OthelloController.h"
#include "Othello/View/OthelloView.h"
#include "Othello/View/OthelloExceptionView.h"
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

	cout << "Othello_NNGA_CLI" << endl;

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

	std::shared_ptr<OthelloViewInterface> exceptionView = make_shared<OthelloExceptionView>();

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

				OthelloController controller(agents, exceptionView);

				auto othello_opt = controller.run();
				if (!othello_opt) return 1;

				const auto score = othello_opt.value().getScore();
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

		if (generation % 1 == 0) {
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
