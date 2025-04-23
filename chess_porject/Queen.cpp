#include "Queen.h"

queen::queen(const unsigned int startRow, const unsigned int startCol, const char color) : piece(startRow, startCol, color, QUEEN)
{

}

Status queen::checkMove(const unsigned int destRow, const unsigned int destCol)
{
	std::array<unsigned int, ARRAY_SIZE> place = getCurPlace();
	if (place[ROW_INDEX] == destRow && place[COL_INDEX] == destCol)
	{
		return DEST_SOURCE_EQUAL;
	}
	unsigned int rowDifference = abs((int)place[ROW_INDEX] - (int)destRow);
	unsigned int colDifference = abs((int)place[COL_INDEX] - (int)destCol);
	if ((place[ROW_INDEX] == destRow || place[COL_INDEX] == destCol) || colDifference == rowDifference)
	{
		return VALID_MOVE;
	}
	return INVALID_MOVE;
}
