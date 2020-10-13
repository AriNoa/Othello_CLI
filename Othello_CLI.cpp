#include <iostream>
#include <memory>
#include "Othello/ManualStrategy.h"
#include "Othello/RandomBot.h"


std::string getStoneStr(const Team& team) {
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

void drawBoard(const std::vector<std::vector<Team>> board) {
    using namespace std;

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


    cout << endl;
    cout << "Othello_CLI";
    cout << endl;

    Othello othello;

    shared_ptr<IAgentStrategy> manualAgent(new ManualStrategy());
    shared_ptr<IAgentStrategy> randomAgent(new RandomBot());
    map<Team, shared_ptr<IAgentStrategy>> agents = {
        { Team::First,  manualAgent },
        { Team::Second, randomAgent }
    };

    while (true) {
        printLine();

        drawBoard(othello.getBoard());

        map<Team, int> score = othello.getScore();

        cout << endl;
        auto printScore = [&agents, &score](Team t){
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
