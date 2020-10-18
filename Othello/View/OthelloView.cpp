#include <iostream>
#include "OthelloView.h"


OthelloView::OthelloView(const std::map<otl::Team, std::string>& teamNames) {
    _teamNames = teamNames;
}


void OthelloView::printLine() {
    using namespace std;

    cout << endl
        << "----------------"
        << endl;
}

std::string OthelloView::teamToString(const otl::Team& team) {
    using namespace otl;

    switch (team) {
    case Team::None:
        return "None";

    case Team::First:
        return "First";

    case Team::Second:
        return "Second";
    }

    return "XXX";
}

std::string OthelloView::getStoneStr(const otl::Team& team) {
    using namespace otl;

    switch (team) {
    case Team::None:
        return " ";

    case Team::First:
        return "›";

    case Team::Second:
        return "œ";
    }

    return "X";
}

void OthelloView::drawBoard(const otl::Othello& othello) {
    using namespace std;
    using namespace otl;

    const vector<std::vector<Team>> board = othello.getBoard();

    cout << ' ';
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

void OthelloView::drawTeamScore(const otl::Team& team, const int& score) {
    using namespace std;
    using namespace otl;

    string stone = getStoneStr(team);
    string teamName = _teamNames[team];

    cout << stone << teamName << " : " << score << endl;
}


void OthelloView::drawAnswer(const otl::Point& pos) {
    using namespace std;

    cout 
        << "Answer" << endl
        << "  X: " << pos.x << endl
        << "  Y: " << pos.y << endl;
}

void OthelloView::drawException(std::string result) {
    using namespace std;

    cout
        << endl 
        << result
        << endl;
}

void OthelloView::drawOthello(const otl::Othello& othello) {
    using namespace std;
    using namespace otl;

    printLine();

    drawBoard(othello);
    
    cout << endl;

    map<Team, int> score = othello.getScore();
    for (auto const& [t, s] : score) {  drawTeamScore(t, s); }

    Team activeTeam = othello.getActiveTeam();

    if (activeTeam != Team::None) {
        string stone = getStoneStr(activeTeam);
        string teamStr = teamToString(activeTeam);
        cout
            << endl
            << "The next player is " << stone << teamStr
            << endl;
    }

    printLine();
}