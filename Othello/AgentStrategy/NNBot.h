#pragma once
#include "IAgentStrategy.h"
#include "NN/NeuralNetwork.h"


namespace nne {
	struct Line {
		otl::Point corner;
		otl::DirVector dir;
		size_t length;
	};

	class LineEvaluation {
	private:
		const NeuralNetwork& _nn;
		const otl::Team& _myTeam;
		const std::vector<std::vector<otl::Team>> _board;

	public:
		LineEvaluation(
			const NeuralNetwork& nn,
			const otl::Team& myTeam,
			const std::vector<std::vector<otl::Team>> board
		);

		std::pair<double, double> getInput(const otl::Team& team) const;
		std::vector<double> getInputs(const Line& line) const;

		double evaluate(const Line& line) const;
	};

	class BoardEvaluation {
	public:
		template<typename T>
		using Board = std::vector<std::vector<T>>;

		static std::vector<nne::Line> initLines(const size_t& length);
		static Board<std::vector<size_t>> initLineIndexBoard(const std::vector<nne::Line>& lines);
		static double calculateEvalSum(const std::vector<double>& evals) {
			double sum = 0;
			for (const auto& eval : evals) { sum += eval; }
			return sum;
		}

		static constexpr size_t lineLength = 3;
		static inline const std::vector<nne::Line> lines = initLines(lineLength);
		static inline const Board<std::vector<size_t>> lineIndexBoard = initLineIndexBoard(lines);

	private:
		const std::vector<double>& _defaultLineEvals;
		const NeuralNetwork& _nn;
		const otl::Othello& _othello;
		const double _defaultEvalSum;

		double _evalSum;
		std::vector<bool> _linesIgnore;

	public:
		BoardEvaluation(
			const std::vector<double>& defaultLineEvals,
			const NeuralNetwork& nn,
			const otl::Othello& othello
		);

		void pointEval(const otl::Point& pos, const LineEvaluation& lineEval);

		double evaluate(const otl::Point& putPos);
	};
}

class NNBot : public IAgentStrategy {
private:
	NeuralNetwork _nn;

public:
	NNBot(const NeuralNetwork& nn);

	virtual std::string getName() const { return "NNBot"; }
	virtual otl::Point answer(const otl::Othello& othello) override;
};
