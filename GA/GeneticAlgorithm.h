#pragma once
#include <vector>
#include <list>
#include <utility>
#include <memory>
#include <algorithm>
#include <random>


class GeneticAlgorithm {
public:
	using Genome = std::vector<double>;

	struct Individual {
		std::shared_ptr<Genome> genome;
		int eval;
	};

	using GenomeVector = std::vector<std::shared_ptr<Genome>>;
	using IndividualVector = std::vector<Individual>;


	//1世代あたりの個体数
	static constexpr size_t populationNum = 50;

	//エリート主義で選択される個体数
	static constexpr size_t eliteNum = 2;
	//ルーレット方式で選択される個体数
	static constexpr size_t rouletteNum = 8;
	//ランダムで選択される個体数
	static constexpr size_t randomNum = 2;

private:
	GenomeVector _genomes;

public:
	GeneticAlgorithm() = default;
	GeneticAlgorithm(const GenomeVector& genomes);

	GenomeVector selectElite(IndividualVector& individuals);
	GenomeVector selectRoulette(IndividualVector& individuals);
	GenomeVector selectRandom(IndividualVector& individuals);

	Genome crossing(const Genome& first, const Genome& second);
	GenomeVector crossing(GenomeVector selectGenomes);

	Genome mutation(Genome& genome);

	const GenomeVector& evolution(const std::vector<int>& evals);
	const GenomeVector& getGenomes();
};