#include "Rook.h"
//constractor of rook
rook::rook(const unsigned int startRow, const unsigned int startCol, char color) : piece(startRow, startCol, color, ROOK)
{

}
/*
the function will check if the rook can go to dest
input: destCol, destRow
output: status of move
*/
Status rook::checkMove(const unsigned int destRow, const unsigned int destCol)
{
	std::array<unsigned int, ARRAY_SIZE> place = getCurPlace();
	if (place[ROW_INDEX] == destRow && place[COL_INDEX] == destCol)
	{
		return DEST_SOURCE_EQUAL;
	}
	else if ((place[ROW_INDEX] == destRow || place[COL_INDEX] == destCol))
	{
		return VALID_MOVE;
	}
	return INVALID_MOVE;
}
