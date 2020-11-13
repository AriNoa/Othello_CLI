#pragma once
#include "OthelloViewInterface.h"


class OthelloView : public OthelloViewInterface {
private:
    std::map<otl::Team, std::string> _teamNames;

public:
    OthelloView() = default;
    OthelloView(const std::map<otl::Team, std::string>& teamNames);

    static void printLine();
    static std::string teamToString(const otl::Team& team);
    static std::string getStoneStr(const otl::Team& team);
    static void drawBoard(const otl::Othello& othello);

    void drawAnswer(const otl::Point& pos) override;
    void drawException(std::string result) override;

    void drawTeamScore(const otl::Team& team, const int& score);
    void drawOthello(const otl::Othello& othello) override;
};