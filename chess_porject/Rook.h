#pragma once
#include "Piece.h"

class rook : public piece
{

public:
	//constractor
	rook(const unsigned int startRow, const unsigned int startCol, char color);
	//methods
	virtual Status checkMove(const unsigned int destRow, const unsigned int destCol) override;
};