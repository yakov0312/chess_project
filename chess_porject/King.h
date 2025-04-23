#pragma once
#include "Piece.h"

class king : public piece
{
public:
	//constractor
	king(const unsigned int startRow, const unsigned int starCol, const char color);
	//methods
	virtual Status checkMove(const unsigned int destRow, const unsigned int destCol) override;
	//setters
	bool setIsCheck(bool isCheck);
	//getters
	bool getIsCheck() const;

private:
	bool _isCheck;
};