#include <iostream>
#include <memory>
#include "Othello/Model/Othello.h"
#include "Othello/IAgentStrategy.h"
#include "Othello/RandomBot.h"


void drawBoard(vector<vector<Team>> board) {
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
    cout << endl;
    cout << "Othello_CLI";
    cout << endl;

    Othello othello;
    unique_ptr<IAgentStrategy> randomBot(new RandomBot());

    drawBoard(othello.getBoard());

    while (true) {
        Team activeTeam = othello.getActiveTeam();
        if (activeTeam == Team::None) break;


        Point putPos;


        if (activeTeam == Team::First) {
            do {
                cout << endl << "入力してください！" << endl;
                cout << "X << ";
                cin >> putPos.x;
                cout << "Y << ";
                cin >> putPos.y;
            } while (!othello.canPutStone(putPos));
        } else {
            cout << endl << "Bot..." << endl;
            putPos = randomBot->answer(othello);
            cout << "X << " << putPos.x << endl;
            cout << "Y << " << putPos.y << endl;
        }

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
