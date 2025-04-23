#pragma once
#include <iostream>
#include <array>
#include "constants.h"

class piece
{
public: 
	//constractor
	piece(const unsigned int startRow, const unsigned int startCol, const char color, const char type);
	//deconstractor
	virtual ~piece();
	//methods
	virtual Status checkMove(const unsigned int destRow, const unsigned int destCol) = 0;
	//setters
	void setCurPlace(const std::array<unsigned int, ARRAY_SIZE>& dest);
	//getters
	std::array<unsigned int, ARRAY_SIZE> getCurPlace() const;
	char getType() const;
	char getColor() const;

private:
	std::array<unsigned int, ARRAY_SIZE> _place;
	char _color;
	char _type;
};