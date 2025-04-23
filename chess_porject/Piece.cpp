#include "Piece.h"

piece::piece(const unsigned int startRow, const unsigned int startCol, const char color, const char type) : _color(color), _type(type)
{
	this->_place[ROW_INDEX] = startRow;
	this->_place[COL_INDEX] = startCol;
}

piece::~piece()
{
	this->_color = ' ';
	this->_place.fill(0);
}

void piece::setCurPlace(const std::array<unsigned int, ARRAY_SIZE>& dest)
{
	this->_place = dest;
}

std::array<unsigned int, ARRAY_SIZE>  piece::getCurPlace() const
{
	return this->_place;
}

char piece::getType() const
{
	return this->_type;
}

char piece::getColor() const
{
	return this->_color;
}