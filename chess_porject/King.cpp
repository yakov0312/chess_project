#include "King.h"

king::king(const unsigned int startRow, const unsigned int startCol, const char color) : piece(startRow, startCol, color, KING), _isCheck(false)
{

}

bool king::setIsCheck(bool isCheck)
{
	return this->_isCheck = isCheck;
}

bool king::getIsCheck() const
{
	return this->_isCheck;
}

Status king::checkMove(const unsigned int destRow, const unsigned int destCol)
{
	std::array<unsigned int, ARRAY_SIZE> place = this->getCurPlace();
	if (place[ROW_INDEX] == destRow && place[COL_INDEX] == destCol)
	{
		return DEST_SOURCE_EQUAL;
	}
	unsigned int rowDifference = abs((int)place[ROW_INDEX] - (int)destRow);
	unsigned int colDifference = abs((int)place[COL_INDEX] - (int)destCol);
	if ((rowDifference == 1 && colDifference == 0) || (colDifference == 1 && rowDifference == 0) || (colDifference == 1 && rowDifference == 1))
	{
		return VALID_MOVE;
	}
	return INVALID_MOVE;
}
