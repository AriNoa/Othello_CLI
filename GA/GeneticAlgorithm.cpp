#include "GeneticAlgorithm.h"



GeneticAlgorithm::GeneticAlgorithm(const GenomeVector& genomes) {
	_genomes = genomes;
}

GeneticAlgorithm::GenomeVector GeneticAlgorithm::selectElite(IndividualVector& individuals) {
	using namespace std;
	vector<IndividualVector::iterator> selectGenomeItrs;

	for (auto indItr = individuals.begin(); indItr != individuals.end(); ++indItr) {
		bool insertFlag = false;
		for (auto gItr = selectGenomeItrs.begin(); gItr != selectGenomeItrs.end(); ++gItr) {
			if (indItr->eval > (*gItr)->eval) {
				selectGenomeItrs.insert(gItr, indItr);
				insertFlag = true;
				break;
			}
		}
		
		if (!insertFlag) selectGenomeItrs.push_back(indItr);
		if (selectGenomeItrs.size() > eliteNum) selectGenomeItrs.resize(eliteNum);
	}

	GenomeVector selectGenomes;

	for (const auto& itr : selectGenomeItrs) {
		selectGenomes.push_back(itr->genome);
	}


	sort(selectGenomeItrs.begin(), selectGenomeItrs.end(), greater<IndividualVector::iterator>());
	for (const auto& itr : selectGenomeItrs) { individuals.erase(itr); }

	return selectGenomes;
}

GeneticAlgorithm::GenomeVector GeneticAlgorithm::selectRoulette(IndividualVector& individuals) {
	using namespace std;

	int total = 0;
	for_each(individuals.cbegin(), individuals.cend(), [&total](const Individual& i) {
		total += i.eval;
	});

	random_device rnd;
	mt19937 mt(rnd());

	GenomeVector selectGenomes;

	for (size_t count = 0; count < rouletteNum; count++) {
		int range = 0;
		std::uniform_int_distribution<> rand(1, total);
		const int random = rand(mt);

		for (size_t index = 0; index < individuals.size(); index++) {
			range += individuals[index].eval;
			if (random <= range) {
				selectGenomes.push_back(individuals[index].genome);
				total -= individuals[index].eval;
				individuals.erase(individuals.begin() + index);
				break;
			}
		}
	}

	return selectGenomes;
}

GeneticAlgorithm::GenomeVector GeneticAlgorithm::selectRandom(IndividualVector& individuals) {
	using namespace std;

	random_device rnd;
	mt19937 mt(rnd());

	GenomeVector selectGenomes;

	for (size_t count = 0; count < randomNum; count++) {
		uniform_int_distribution<> rand(0, (int)individuals.size() - 1);
		const int random = rand(mt);

		selectGenomes.push_back(individuals[random].genome);
		individuals.erase(individuals.begin() + random);
	}

	return selectGenomes;
}

GeneticAlgorithm::Genome GeneticAlgorithm::crossing(const Genome& first, const Genome& second) {
	using namespace std;

	Genome newGenome;

	random_device rnd;
	mt19937 mt(rnd());
	std::uniform_real_distribution<> rand(0, 1);

	for (size_t i = 0; i < first.size(); i++) {
		const double random = rand(mt);

		newGenome.push_back(
			(first[i] - second[i]) * random + second[i]
		);
	}

	return newGenome;
}

GeneticAlgorithm::GenomeVector GeneticAlgorithm::crossing(GenomeVector selectGenomes) {
	using namespace std;

	random_device rnd;
	mt19937 mt(rnd());
	shuffle(selectGenomes.begin(), selectGenomes.end(), mt);

	GenomeVector genomes;
	size_t count = 0;

	size_t index = 0;
	size_t dist = 1;

	while (count < populationNum) {
		size_t secondIndex = index + dist;
		if (secondIndex >= selectGenomes.size()) secondIndex = secondIndex - selectGenomes.size();

		genomes.push_back(make_shared<Genome>(
			crossing(*selectGenomes[index], *selectGenomes[secondIndex])
		));

		count++;
		index++;

		if (index >= selectGenomes.size()) {
			index = 0;
			dist++;
		}
	}

	return genomes;
}

GeneticAlgorithm::Genome GeneticAlgorithm::mutation(Genome& genome) {
	using namespace std;

	const double mutationRate = (double)1 / genome.size();

	random_device rnd;
	mt19937 mt(rnd());
	std::uniform_real_distribution<> randMut(0, 1);
	std::uniform_real_distribution<> randGen(-1, 1);

	for (auto& gene : genome) {
		const double random = randMut(mt);

		if (random < mutationRate) { gene = randGen(mt); }
	}

	return genome;
}

const GeneticAlgorithm::GenomeVector& GeneticAlgorithm::evolution(const std::vector<int>& evals) {
	IndividualVector individuals;
	for (size_t i = 0; i < evals.size(); i++) {
		individuals.push_back(
			{ _genomes[i], evals[i] }
		);
	}

	GenomeVector selectGenomes;
	const GenomeVector eliteGenomes = selectElite(individuals);
	const GenomeVector rouletteGenomes = selectRoulette(individuals);
	const GenomeVector randomGenomes = selectRandom(individuals);

	auto& elite = eliteGenomes.front();

	selectGenomes.insert(selectGenomes.end(), eliteGenomes.begin(), eliteGenomes.end());
	selectGenomes.insert(selectGenomes.end(), rouletteGenomes.begin(), rouletteGenomes.end());
	selectGenomes.insert(selectGenomes.end(), randomGenomes.begin(), randomGenomes.end());

	_genomes = crossing(selectGenomes);
	_genomes.pop_back();

	for (auto& genome : _genomes) { mutation(*genome); }

	_genomes.push_back(elite);

	return _genomes;
}

const GeneticAlgorithm::GenomeVector& GeneticAlgorithm::getGenomes() {
	return _genomes;
}
