#include "Board.h"
#include "Rook.h"
#include "Queen.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Knight.h"
#include <cctype>

unsigned int board::_numOfMoves = 0;

board::board()
{
	int i = 0;
	int j = 0;
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			this->_board[i][j] = nullptr;
		}
	}
	//init the black side
	this->_board[0][0] = new rook(0, 0, COLOR_BLACK);
	this->_board[0][1] = new knight(0, 1, COLOR_BLACK);
	this->_board[0][2] = new bishop(0, 2, COLOR_BLACK);
	this->_board[0][3] = new queen(0, 3, COLOR_BLACK);
	this->_blackKing = new king(0, 4, COLOR_BLACK);
	this->_board[0][4] = this->_blackKing;
	this->_board[0][5] = new bishop(0, 5, COLOR_BLACK);
	this->_board[0][6] = new knight(0, 6, COLOR_BLACK);
	this->_board[0][BOARD_SIZE - 1] = new rook(0, BOARD_SIZE - 1, COLOR_BLACK);
	for (i = 0; i < BOARD_SIZE; i++)
	{
		this->_board[1][i] = new pawn(1, i, COLOR_BLACK);
	}

	//init the white side 
	this->_board[BOARD_SIZE - 1][0] = new rook(BOARD_SIZE - 1, 0, COLOR_WHITE);
	this->_board[BOARD_SIZE - 1][1] = new knight(BOARD_SIZE - 1, 1, COLOR_WHITE);
	this->_board[BOARD_SIZE - 1][2] = new bishop(BOARD_SIZE - 1, 2, COLOR_WHITE);
	this->_board[BOARD_SIZE - 1][3] = new queen(BOARD_SIZE - 1, 3, COLOR_WHITE);
	this->_whiteKing = new king(BOARD_SIZE - 1, 4, COLOR_WHITE);
	this->_board[BOARD_SIZE - 1][4] = this->_whiteKing;
	this->_board[BOARD_SIZE - 1][5] = new bishop(BOARD_SIZE - 1, 5, COLOR_WHITE);
	this->_board[BOARD_SIZE - 1][6] = new knight(BOARD_SIZE - 1, 6, COLOR_WHITE);
	this->_board[BOARD_SIZE - 1][BOARD_SIZE - 1] = new rook(BOARD_SIZE - 1, BOARD_SIZE - 1, COLOR_WHITE);
	for (i = 0; i < BOARD_SIZE; i++)
	{
		this->_board[BOARD_SIZE - 2][i] = new pawn(BOARD_SIZE - 2, i, COLOR_WHITE);
	}
}

board::~board()
{
	int i = 0;
	int j = 0;
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			delete this->_board[i][j];
			this->_board[i][j] = nullptr;
		}
	}
}

Status board::movPiece(const std::array<unsigned int, ARRAY_SIZE> sourcePoint, const std::array<unsigned int, ARRAY_SIZE> destPoint, const char colorTurn, const bool test)
{
	if (this->_board[sourcePoint[ROW_INDEX]][sourcePoint[COL_INDEX]] == nullptr || this->_board[sourcePoint[ROW_INDEX]][sourcePoint[COL_INDEX]]->getColor() != colorTurn)
	{
		return SOURCE_EMPTY;
	}
	Status status = this->checkMove(sourcePoint, destPoint);
	if (status == VALID_MOVE)
	{
		piece* ptr = this->_board[destPoint[ROW_INDEX]][destPoint[COL_INDEX]];
		this->_board[destPoint[ROW_INDEX]][destPoint[COL_INDEX]] = this->_board[sourcePoint[ROW_INDEX]][sourcePoint[COL_INDEX]];
		this->_board[sourcePoint[ROW_INDEX]][sourcePoint[COL_INDEX]] = nullptr;
		this->_board[destPoint[ROW_INDEX]][destPoint[COL_INDEX]]->setCurPlace(destPoint);
		//check if the move will cause check to the player
		if ((colorTurn == COLOR_BLACK && this->isCheckTo(_blackKing) == true) || ( colorTurn == COLOR_WHITE && this->isCheckTo(_whiteKing) == true))
		{
			this->_board[destPoint[ROW_INDEX]][destPoint[COL_INDEX]]->setCurPlace(sourcePoint);
			this->_board[sourcePoint[ROW_INDEX]][sourcePoint[COL_INDEX]] = this->_board[destPoint[ROW_INDEX]][destPoint[COL_INDEX]];
			this->_board[destPoint[ROW_INDEX]][destPoint[COL_INDEX]] = ptr;
			return CAUSE_CHECK;
		}
		if (test == true)
		{
			return VALID_MOVE;
		}
		//check if the move will cause check to the opp
		else if ((colorTurn == COLOR_BLACK && isCheckTo(this->_whiteKing) == true) ||(colorTurn == COLOR_WHITE && isCheckTo(this->_blackKing) == true))
		{
			delete ptr;
			return VALID_MOVE_CHECK;
		}
		delete ptr;
	}
	return status;
}

Status board::checkMove(const std::array<unsigned int, ARRAY_SIZE>& source, const std::array<unsigned int, ARRAY_SIZE>& dest) const 
{
	Status status;
	char pieceType = _board[source[ROW_INDEX]][source[COL_INDEX]]->getType();
	if (pieceType == ROOK)
	{
		status = this->moveRook(source, dest);
	}

	else if (pieceType == KNIGHT)
	{
		status = this->moveKnight(source, dest);
	}

	else if (pieceType == BISHOP)
	{
		status = this->moveBishop(source, dest);
	}

	else if (pieceType == QUEEN)
	{
		status = this->moveQueen(source, dest);
	}

	else if (pieceType == KING)
	{
		status = this->moveKing(source, dest);
	}

	else if (pieceType == PAWN)
	{
		status = this->movePawn(source, dest);
	}
	return status;
}

std::array<unsigned int, ARRAY_SIZE> board::convertStrToInt(const std::string& point)
{
	unsigned int rowArr[BOARD_SIZE] = { 7,6,5,4,3,2,1,0 };
	unsigned int col = point[0] - 97;
	unsigned int row = rowArr[point[1] - 49];
	return std::array<unsigned int, ARRAY_SIZE>{row, col};
}

const unsigned int board::oneMove(const std::string& move)
{
	char colorTurn = ' ';
	int status = 0;
	if (this->_numOfMoves % 2 == 0)
	{
		colorTurn = COLOR_WHITE;
	}
	else
	{
		colorTurn = COLOR_BLACK;
	}
	status = this->movPiece(this->convertStrToInt(move.substr(0, 2)) ,this->convertStrToInt(move.substr(2, 2)) , colorTurn, false);
	if (status == VALID_MOVE || status == VALID_MOVE_CHECK)
	{
		this->_numOfMoves += 1;
	}
	if (status == VALID_MOVE_CHECK)
	{
		char color = COLOR_BLACK;
		if (colorTurn == COLOR_BLACK)
		{
			color = COLOR_WHITE;
		}
		if (this->checkWin(color) == true)
		{
			return VALID_MOVE_CHECKMATE;
		}
	}
	return status;
}

bool board::checkWin(const char colorTurn)
{
	std::array<unsigned int, ARRAY_SIZE> source = { 0, 0 };
	std::array<unsigned int, ARRAY_SIZE> dest = { 0, 0 };

	king* currentKing = (colorTurn == COLOR_WHITE) ? this->_whiteKing : this->_blackKing;

	for (unsigned int rowP = 0; rowP < BOARD_SIZE; rowP++)
	{
		for (unsigned int colP = 0; colP < BOARD_SIZE; colP++)
		{
			piece* currentPiece = this->_board[rowP][colP];

			if (currentPiece != nullptr && currentPiece->getColor() == colorTurn)
			{
				source = { rowP, colP };

				for (unsigned int rowM = 0; rowM < BOARD_SIZE; rowM++)
				{
					for (unsigned int colM = 0; colM < BOARD_SIZE; colM++)
					{
						dest = { rowM, colM };

						if (this->checkMove(source, dest) == VALID_MOVE)
						{
							piece* capturedPiece = this->_board[dest[ROW_INDEX]][dest[COL_INDEX]];
							this->_board[dest[ROW_INDEX]][dest[COL_INDEX]] = this->_board[source[ROW_INDEX]][source[COL_INDEX]];
							this->_board[source[ROW_INDEX]][source[COL_INDEX]] = nullptr;
							this->_board[dest[ROW_INDEX]][dest[COL_INDEX]]->setCurPlace(dest);

							bool stillInCheck = this->isCheckTo(currentKing);

							// Undo move
							this->_board[source[ROW_INDEX]][source[COL_INDEX]] = this->_board[dest[ROW_INDEX]][dest[COL_INDEX]];
							this->_board[source[ROW_INDEX]][source[COL_INDEX]]->setCurPlace(source);
							this->_board[dest[ROW_INDEX]][dest[COL_INDEX]] = capturedPiece;

							if (!stillInCheck)
							{
								return false;
							}
						}
					}
				}
			}
		}
	}

	return true; // Checkmate: no valid moves
}

Status board::moveBishop(const std::array<unsigned int, ARRAY_SIZE>& source, const std::array<unsigned int, ARRAY_SIZE>& dest) const
{
	Status status = this->_board[source[ROW_INDEX]][source[COL_INDEX]]->checkMove(dest[ROW_INDEX], dest[COL_INDEX]);
	if (status == VALID_MOVE)
	{
		char color = this->_board[source[ROW_INDEX]][source[COL_INDEX]]->getColor();
		if(this->eatIsValid(dest, color) == true)
		{
			int mRow = (dest[ROW_INDEX] > source[ROW_INDEX]) ? 1 : -1;
			int mCol = (dest[COL_INDEX] > source[COL_INDEX]) ? 1 : -1;
			int row = 0;
			int col = 0;
			for (row = source[ROW_INDEX] + mRow, col = source[COL_INDEX] + mCol; row != dest[ROW_INDEX] && col != dest[COL_INDEX]; row += mRow, col += mCol)
			{
				if (this->_board[row][col] != nullptr)
				{
					return INVALID_MOVE;
				}
			}
			return VALID_MOVE;
		}
		return CANNOT_EAT;
	}
	return status;
}

Status board::moveKing(const std::array<unsigned int, ARRAY_SIZE>& source, const std::array<unsigned int, ARRAY_SIZE>& dest) const
{
	Status status = this->_board[source[ROW_INDEX]][source[COL_INDEX]]->checkMove(dest[ROW_INDEX], dest[COL_INDEX]);
	char color = this->_board[source[ROW_INDEX]][source[COL_INDEX]]->getColor();
	if (status == VALID_MOVE)
	{
		if (this->eatIsValid(dest, color) == true)
		{
			return VALID_MOVE;
		}
		return CANNOT_EAT;
	}
	return status;
}

Status board::moveKnight(const std::array<unsigned int, ARRAY_SIZE>& source, const std::array<unsigned int, ARRAY_SIZE>& dest) const
{
	Status status = this->_board[source[ROW_INDEX]][source[COL_INDEX]]->checkMove(dest[ROW_INDEX], dest[COL_INDEX]);
	char color = this->_board[source[ROW_INDEX]][source[COL_INDEX]]->getColor();
	if (status == VALID_MOVE)
	{
		if(this->eatIsValid(dest, color) == true)
		{
			return VALID_MOVE;
		}
		return CANNOT_EAT;
	}
	return status;
}

Status board::moveQueen(const std::array<unsigned int, ARRAY_SIZE>& source, const std::array<unsigned int, ARRAY_SIZE>& dest) const
{
	Status status = this->_board[source[ROW_INDEX]][source[COL_INDEX]]->checkMove(dest[ROW_INDEX], dest[COL_INDEX]);
	char color = this->_board[source[ROW_INDEX]][source[COL_INDEX]]->getColor();
	if (status == VALID_MOVE)
	{
		if (this->eatIsValid(dest, color) == true)
		{
			status = this->moveBishop(source, dest);
			if (status == VALID_MOVE)
			{
				return status;
			}
			if (source[ROW_INDEX] == dest[ROW_INDEX] || source[COL_INDEX] == dest[COL_INDEX])
			{
				status = this->moveRook(source, dest);
				return status;
			}
			return INVALID_MOVE;
		}
		return CANNOT_EAT;
	}
	return status;
}

bool board::eatIsValid(const std::array<unsigned int, ARRAY_SIZE>& dest, const char color) const
{
	if (this->_board[dest[ROW_INDEX]][dest[COL_INDEX]] == nullptr)
	{
		return true;
	}
	if (this->_board[dest[ROW_INDEX]][dest[COL_INDEX]]->getColor() != color)
	{
		return true;
	}
	return false;
}

bool board::isCheckTo(const king* King) const
{
	unsigned int i = 0;
    unsigned int j = 0;
	std::array<unsigned int, ARRAY_SIZE> source = { i, j };
	std::array<unsigned int, ARRAY_SIZE> kingPlace = King->getCurPlace();
	char kingColor = King->getColor();
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			source = { i, j };
			if (this->_board[i][j] != nullptr && this->_board[i][j]->getColor() != kingColor && this->checkMove(source, kingPlace) == VALID_MOVE)
			{
				return true;
			}
		}
		int z = 0;
	}
	return false;
}

std::string board::getBoard() const
{
	int i = 0;
	int j = 0;
	std::string board = "";
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (this->_board[i][j] == nullptr)
			{
				board += "#";
				continue;
			}
			if (this->_board[i][j]->getColor() == COLOR_BLACK)
			{
				board += char(std::tolower(this->_board[i][j]->getType()));
				continue;
			}
			board += this->_board[i][j]->getType();
		}
	}
	return board;
}

Status board::moveRook(const std::array<unsigned int, ARRAY_SIZE>& source, const std::array<unsigned int, ARRAY_SIZE>& dest) const
{
	Status status = this->_board[source[ROW_INDEX]][source[COL_INDEX]]->checkMove(dest[ROW_INDEX], dest[COL_INDEX]);
	char color = this->_board[source[ROW_INDEX]][source[COL_INDEX]]->getColor();
	if (status == VALID_MOVE)
	{
		if (this->eatIsValid(dest, color) == true)
		{
			int m = 0;
			//if he move horizontally
			int rowOrCol = ROW_INDEX;
			if (source[COL_INDEX] != dest[COL_INDEX])
			{
				rowOrCol = COL_INDEX;
			}
			m = (source[rowOrCol] < dest[rowOrCol]) ? 1 : -1;
			int direction = 0;
			for (direction = source[rowOrCol] + m; direction != dest[rowOrCol]; direction += m)
			{
				if (rowOrCol == ROW_INDEX)
				{
					if (this->_board[direction][source[COL_INDEX]] != nullptr)
					{
						return INVALID_MOVE;
					}
				}
				else
				{
					if (this->_board[source[ROW_INDEX]][direction] != nullptr)
					{
						return INVALID_MOVE;
					}
				}
			}
			return VALID_MOVE;
		}
		return CANNOT_EAT;
	}
	return status;
}

Status board::movePawn(const std::array<unsigned int, ARRAY_SIZE>& source, const std::array<unsigned int, ARRAY_SIZE>& dest) const
{
	Status status = this->_board[source[ROW_INDEX]][source[COL_INDEX]]->checkMove(dest[ROW_INDEX], dest[COL_INDEX]);
	char color = this->_board[source[ROW_INDEX]][source[COL_INDEX]]->getColor();
	int difRow = (int)source[ROW_INDEX] - dest[ROW_INDEX];
	if (status == VALID_MOVE)
	{
		if (abs(difRow) == 2)
		{
			int m = 1;
			if (color == COLOR_WHITE)
			{
				m = -1;
			}
			if (this->_board[(source[ROW_INDEX]) + m][(source[COL_INDEX])] != nullptr)
			{
				return INVALID_MOVE;
			}
		}
		if (this->_board[dest[ROW_INDEX]][source[COL_INDEX]] == nullptr)
		{
			return VALID_MOVE;
		}
		return INVALID_MOVE;
	}
	if (status == INVALID_MOVE)
	{
		int difCol = (int)source[COL_INDEX] - dest[COL_INDEX];
		//black
		if (color == COLOR_BLACK && abs(difCol) == 1 && difRow == -1 && this->_board[dest[ROW_INDEX]][dest[COL_INDEX]] != nullptr && this->_board[dest[ROW_INDEX]][dest[COL_INDEX]]->getColor() != color)
		{
			return VALID_MOVE;
		}
		//white
		else if (color == COLOR_WHITE && abs(difCol) == 1 && difRow == 1 && this->_board[dest[ROW_INDEX]][dest[COL_INDEX]] != nullptr && this->_board[dest[ROW_INDEX]][dest[COL_INDEX]]->getColor() != color)
		{
			status = VALID_MOVE;
		}
	}
	return status;
}
