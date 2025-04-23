#pragma once
#include "Piece.h"
#include "King.h"
#include <string>


class piece;

class board
{
public:
	//constractor
	board();

	//deconstractor
	~board();

	//game methods
	const unsigned int oneMove(const std::string& move);
	std::string getBoard() const;

private: 
	//game methods
	bool checkWin(const char colorTrun);
	bool isCheckTo(const king* King)const;
	bool eatIsValid(const std::array<unsigned int, ARRAY_SIZE>& dest, const char color) const;
	//move pieces
	Status movPiece(const std::array<unsigned int, ARRAY_SIZE> sourcePoint, const std::array<unsigned int, ARRAY_SIZE> destPoint, const char colorTurn, const bool test);
	Status checkMove(const std::array<unsigned int, ARRAY_SIZE>& source, const std::array<unsigned int, ARRAY_SIZE>& dest) const;
	Status moveRook(const std::array<unsigned int, ARRAY_SIZE>& source, const std::array<unsigned int, ARRAY_SIZE>& dest) const;
	Status movePawn(const std::array<unsigned int, ARRAY_SIZE>& source, const std::array<unsigned int, ARRAY_SIZE>& dest) const;
	Status moveBishop(const std::array<unsigned int, ARRAY_SIZE>& source, const std::array<unsigned int, ARRAY_SIZE>& dest) const;
	Status moveKing(const std::array<unsigned int, ARRAY_SIZE>& source, const std::array<unsigned int, ARRAY_SIZE>& dest) const;
	Status moveKnight(const std::array<unsigned int, ARRAY_SIZE>& source, const std::array<unsigned int, ARRAY_SIZE>& dest) const;
	Status moveQueen(const std::array<unsigned int, ARRAY_SIZE>& source, const std::array<unsigned int, ARRAY_SIZE>& dest) const;

	//statics
	static std::array<unsigned int, ARRAY_SIZE> convertStrToInt(const std::string& point);
	static unsigned int _numOfMoves;

	//vars
	piece* _board[BOARD_SIZE][BOARD_SIZE];
	king* _whiteKing;
	king* _blackKing;
};