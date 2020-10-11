#include <iostream>
#include "Othello/Model/Othello.h"
#include "Othello/IAgentStrategy.h"
#include "Othello/RandomBot.h"


int main() {
    using namespace std;
    using namespace otl;
    cout << endl;
    cout << "Othello_CLI";
    cout << endl;

    Othello othello;
    IAgentStrategy* randomBot = new RandomBot();

    bool flag_of_bot = false;

    do {
        for (int y = 0; y < Othello::height; y++) {
            for (int x = 0; x < Othello::width; x++) {
                switch (othello.getBoard()[y][x]) {
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

        map<Team, int> score = othello.getScore();
        cout << endl << "First: " << score[Team::First];
        cout << endl << "Second: " << score[Team::Second];
        cout << endl << "Active team: " << size_t(othello.getActiveTeam()) << endl;

        Point putPos;

        if (!flag_of_bot) {
            do {
                cout << endl << "入力してください！" << endl;
                cout << "X << ";
                cin >> putPos.x;
                cout << "Y << ";
                cin >> putPos.y;
            } while (!othello.canPutStone(putPos));
        }
        else {
            cout << endl << "Bot..." << endl;
            putPos = randomBot->answer(othello);
            cout << "X << " << putPos.x << endl;
            cout << "Y << " << putPos.y << endl;;
        }

        flag_of_bot = !flag_of_bot;

        auto res = othello.putStone(putPos);

        if (holds_alternative<string>(res)) {
            cout << get<string>(res) << endl;
            return 1;
        }
    } while (othello.getActiveTeam() != Team::None);

    delete randomBot;
    return 0;
}
