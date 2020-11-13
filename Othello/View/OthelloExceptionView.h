#pragma once
#include "OthelloViewInterface.h"

class OthelloExceptionView : public OthelloViewInterface {
public:
    void drawAnswer(const otl::Point& pos) override {}
    void drawException(std::string result) override;
    void drawOthello(const otl::Othello& othello) override {}
};

