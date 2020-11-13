#pragma once
#include "Othello/Model/Othello.h"


class OthelloViewInterface {
public:
	virtual ~OthelloViewInterface() {};

	virtual void drawAnswer(const otl::Point& pos) = 0;
	virtual void drawException(std::string result) = 0;
	virtual void drawOthello(const otl::Othello& othello) = 0;
};
