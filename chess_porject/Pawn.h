#pragma once
#include "Piece.h"

class pawn : public piece
{
public:
	//constractor
	pawn(const unsigned int startRow, const unsigned int startCol, const char color);
	//methods
	virtual Status checkMove(const unsigned int destRow, const unsigned int destCol) override;
	//setters
	void setIsFirstMoveFalse();
	//getters
	bool getIsFirstMove() const;
private: 
	bool _isFirstMove;
};