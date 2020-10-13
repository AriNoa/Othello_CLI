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

    drawBoard(othello.getBoard());

    while (true) {
        const Team activeTeam = othello.getActiveTeam();
        if (activeTeam == Team::None) break;

        const Point putPos = agents[activeTeam]->answer(othello);

        auto putResult = othello.putStone(putPos);

        if (holds_alternative<string>(putResult)) {
            cout << get<string>(putResult) << endl;
            return 1;
        }

        map<Team, int> score = othello.getScore();
        cout << endl
            << "FirstStone: " << score[Team::First] << endl
            << "SecondStone: " << score[Team::Second] << endl;

        auto board = get<std::pair<std::vector<std::vector<Team>>, Team>>(putResult).first;
        drawBoard(board);
    }

    return 0;
}
