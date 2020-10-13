#include <iostream>
#include <memory>
#include "Othello/ManualStrategy.h"
#include "Othello/RandomBot.h"


void drawBoard(const std::vector<std::vector<Team>> board) {
    using namespace std;

    for (int y = 0; y < Othello::height; y++) {
        for (int x = 0; x < Othello::width; x++) {
            switch (board[y][x]) {
            case Team::None:
                cout << "□";
                break;

            case Team::First:
                cout << "○";
                break;

            case Team::Second:
                cout << "●";
                break;
            }
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
            cout << agents[t]->getName() << " : " << score[t] << endl;
        };
        printScore(Team::First);
        printScore(Team::Second);

        printLine();

        const Team activeTeam = othello.getActiveTeam();
        if (activeTeam == Team::None) break;

        const Point putPos = agents[activeTeam]->answer(othello);
        cout << endl 
            << agents[activeTeam]->getName() << endl
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
