#include "Pawn.h"

pawn::pawn(const unsigned int startRow, const unsigned int startCol, const char color) : piece(startRow, startCol, color, PAWN), _isFirstMove(true)
{

}

Status pawn::checkMove(const unsigned int destRow, const unsigned int destCol)
{
    std::array<unsigned int, ARRAY_SIZE> place = this->getCurPlace();
    if (place[ROW_INDEX] == destRow && place[COL_INDEX] == destCol)
    {
        return DEST_SOURCE_EQUAL;
    }
    else if (this->getColor() == COLOR_BLACK && this->_isFirstMove == true && destRow - place[ROW_INDEX] == 2 && destCol == place[COL_INDEX])
    {
        this->setIsFirstMoveFalse();
        return VALID_MOVE;
    }
    else if (this->getColor() == COLOR_WHITE && this->_isFirstMove == true && place[ROW_INDEX] - destRow  == 2 && destCol == place[COL_INDEX])
    {
        this->setIsFirstMoveFalse();
        return VALID_MOVE;
    }
    else if (destRow - place[ROW_INDEX] == 1 && destCol == place[COL_INDEX] && this->getColor() == COLOR_BLACK)
    {
        return VALID_MOVE;
    }
    else if (place[ROW_INDEX] - destRow == 1 && destCol == place[COL_INDEX] && this->getColor() == COLOR_WHITE)
    {
        return VALID_MOVE;
    }
    return INVALID_MOVE;
}

void pawn::setIsFirstMoveFalse()
{
	this->_isFirstMove = false;
}

bool pawn::getIsFirstMove() const
{
	return this->_isFirstMove;
}