#pragma once
#include "Piece.h"

class bishop : public piece
{
public:
	//constractor
	bishop(const unsigned int startRow, const unsigned int startCol, const char color);
	//methods
	virtual Status checkMove(const unsigned int destRow, const unsigned int destCol) override;
};