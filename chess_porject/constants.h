#pragma once


//states
enum Status
{
	VALID_MOVE,
	VALID_MOVE_CHECK,
	SOURCE_EMPTY,
	CANNOT_EAT,
	CAUSE_CHECK,
	WRONG_INDEX,
	INVALID_MOVE,
	DEST_SOURCE_EQUAL,
	VALID_MOVE_CHECKMATE
};

//pieces
constexpr char ROOK = 'R';
constexpr char BISHOP = 'B';
constexpr char KING = 'K';
constexpr char KNIGHT = 'N';
constexpr char QUEEN = 'Q';
constexpr char PAWN = 'P';

//colors
constexpr char COLOR_BLACK = 'B';
constexpr char COLOR_WHITE = 'W';

//array related
constexpr int COL_INDEX = 1;
constexpr int ROW_INDEX = 0;
constexpr int ARRAY_SIZE = 2;

constexpr int  BOARD_SIZE = 8;