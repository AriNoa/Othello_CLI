#pragma once
#include <Othello/Model/Othello.h>


class OthelloView {
private:
    std::map<otl::Team, std::string> _teamNames;

public:
    OthelloView(const std::map<otl::Team, std::string>& teamNames);

    void printLine();
    std::string teamToString(const otl::Team& team);
    std::string getStoneStr(const otl::Team& team);
    void drawBoard(const otl::Othello& othello);
    void drawTeamScore(const otl::Team& team, const int& score);

    void drawOthello(const otl::Othello& othello);
};