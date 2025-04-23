/*
This file servers as an example of how to use Pipe.h file.
It is recommended to use the following code in your project,
in order to read and write information from and to the Backend
*/
#include "Pipe.h"
#include <iostream>
#include <thread>
#include "Board.h"

using std::cout;
using std::endl;
using std::string;


void main()
{
	srand(time_t(NULL));


	Pipe p;
	bool isConnect = p.connect();

	string ans;
	while (!isConnect)
	{
		cout << "cant connect to graphics" << endl;
		cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
		std::cin >> ans;

		if (ans == "0")
		{
			cout << "trying connect again.." << endl;
			Sleep(5000);
			isConnect = p.connect();
		}
		else
		{
			p.close();
			return;
		}
	}

	board chess;
	string startBoard = chess.getBoard() + "0";
	string move = "";
	unsigned int status;

	p.sendMessageToGraphics(startBoard.data());   // send the board string

	// get message from graphics
	move = p.getMessageFromGraphics();

	while (move != "quit")
	{
		status = chess.oneMove(move);
		p.sendMessageToGraphics(std::to_string(status).data());
		move = p.getMessageFromGraphics();
	}

	p.close();
}