#pragma once
#include "Othello/Model/Othello.h"


class OthelloView {
private:
    std::map<otl::Team, std::string> _teamNames;

public:
    OthelloView() = default;
    OthelloView(const std::map<otl::Team, std::string>& teamNames);

    static void printLine();
    static std::string teamToString(const otl::Team& team);
    static std::string getStoneStr(const otl::Team& team);
    static void drawBoard(const std::vector<std::vector<otl::Team>>& board);

    static void drawAnswer(const otl::Point& pos);
    static void drawException(std::string result);

    void drawTeamScore(const otl::Team& team, const int& score);
    void drawOthello(const otl::Othello& othello);
};