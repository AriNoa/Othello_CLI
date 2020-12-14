#pragma once
#include <fstream>
#include "Othello/AgentStrategy/IAgentStrategy.h"
#include "AlphaBetaSearch.h"
#include "NE/ParseFunctions.h"


class NNBot : public IAgentStrategy {
public:
	static constexpr size_t inputSize = 6;
	static inline const std::vector<size_t> nnSize = { 8, 1 };
	static std::string readAll(std::string filePath) {
		std::ifstream ifs(filePath);
		if (!ifs) throw "Error: file is not opened.";

		std::string str;
		std::string tmp;
		while (std::getline(ifs, tmp)) {
			str += tmp + '\n';
		}

		return str;
	}

	static constexpr int searchDepth = 5;
	static constexpr int fullSearchCount = 12;

private:
	NeuralNetwork _nn;

public:
	NNBot(const NeuralNetwork& nn);
	NNBot(const std::string& filePath);

	virtual std::string getName() const { return "NNBot"; }
	virtual otl::Point answer(const otl::Othello& othello) override;
};
