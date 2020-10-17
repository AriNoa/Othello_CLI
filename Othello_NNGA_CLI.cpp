#include <iostream>
#include <memory>
#include "Othello/AgentStrategy/ManualStrategy.h"
#include "Othello/AgentStrategy/RandomBot.h"
#include "Othello/AgentStrategy/ScoreBot.h"


std::string getStoneStr(const otl::Team& team) {
    using namespace otl;

    switch (team) {
    case Team::None:
        return "□";

    case Team::First:
        return "○";

    case Team::Second:
        return "●";
    }

    return "X";
}

void drawBoard(const std::vector<std::vector<otl::Team>> board) {
    using namespace std;
    using namespace otl;

    for (int x = 0; x < Othello::width; x++) { cout << ' ' << x; }
    cout << endl;

    for (int y = 0; y < Othello::height; y++) {
        cout << y;
        for (int x = 0; x < Othello::width; x++) {
            cout << getStoneStr(board[y][x]);
        }
        cout << endl;
    }
}


void printLine() {
    std::cout << std::endl;
    for (int i = 0; i < 16; i++) { std::cout << '-'; }
    std::cout << std::endl;
}


int main() {
    using namespace std;
    using namespace otl;


    cout << endl;
    cout << "Othello_CLI";
    cout << endl;

    Othello othello;

    shared_ptr<IAgentStrategy> scoreAgent(new ScoreBot());
    shared_ptr<IAgentStrategy> randomAgent(new RandomBot());
    map<Team, shared_ptr<IAgentStrategy>> agents = {
        { Team::First,  scoreAgent },
        { Team::Second, randomAgent }
    };

    while (true) {
        printLine();

        drawBoard(othello.getBoard());

        map<Team, int> score = othello.getScore();

        cout << endl;
        auto printScore = [&agents, &score](Team t) {
            cout << agents[t]->getName() << getStoneStr(t) << " : " << score[t] << endl;
        };
        printScore(Team::First);
        printScore(Team::Second);

        printLine();

        const Team activeTeam = othello.getActiveTeam();
        if (activeTeam == Team::None) break;

        cout << endl << agents[activeTeam]->getName() << getStoneStr(activeTeam) << endl;
        const Point putPos = agents[activeTeam]->answer(othello);
        cout << "Answer" << endl
            << "  X: " << putPos.x << endl
            << "  Y: " << putPos.y << endl;

        auto putResult = othello.putStone(putPos);

        if (holds_alternative<string>(putResult)) {
            cout << endl << get<string>(putResult) << endl;
            return 1;
        }
    }

    return 0;
}
