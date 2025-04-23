#include "Knight.h"

knight::knight(const unsigned int startRow, const unsigned int startCol, const char color) : piece(startRow, startCol, color, KNIGHT)
{

}

Status knight::checkMove(const unsigned int destRow, const unsigned int destCol)
{
    std::array<unsigned int, ARRAY_SIZE> place = this->getCurPlace();
    if (place[ROW_INDEX] == destRow && place[COL_INDEX] == destCol)
    {
        return DEST_SOURCE_EQUAL;
    }
    unsigned int rowDifference = abs((int)place[ROW_INDEX] - (int)destRow);
    unsigned int colDifference = abs((int)place[COL_INDEX] - (int)destCol);
    if ((rowDifference == 2 && colDifference == 1) || (rowDifference == 1 && colDifference == 2))
    {
        return VALID_MOVE;
    }
    return INVALID_MOVE;
}
