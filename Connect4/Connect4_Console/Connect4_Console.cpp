// Connect4_Console.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>

#include "Board.h"
#include "Connect4Algorithm.h"

void PrintBoard(const Board& board)
{
	system("CLS");
	std::cout << "\n";
	std::cout << " +---------------------------+\n";
	std::cout << " |       Xander Bartels      |\n";
	std::cout << " |         Connect 4         |\n";
	std::cout << " +---------------------------+\n";
	std::cout << "\n";
	std::cout << " +---------------------------+\n";
	for (int row=Board::MAX_DISCS_PER_COLUMN-1; row>=0; --row)
	{
		for (int column=0; column<Board::COLUMNS; ++column)
		{
			auto value = board.GetValue(row, column);
			std::cout << " | " << (value == Value::None ? " " : value == Value::Red ? "R" : "Y");
		}
		std::cout << " |\n";
	}
	std::cout << " +---------------------------+\n";
	std::cout << " | 1 | 2 | 3 | 4 | 5 | 6 | 7 |\n";
	std::cout << " +---------------------------+\n";
}

int main()
{
    Board board{};
	Connect4Algorithm algorithm {};

	bool cont{ true };
    std::string answer;

	do
    {
		PrintBoard(board);

		//let AI do its action
		int columnToPlay = algorithm.GetNextMove(board);
		if (columnToPlay >= 0 && columnToPlay<=Board::COLUMNS)
		{
			board.Drop(Value::Red, columnToPlay);
		}
        
        //print current board
		PrintBoard(board);

        //ask player action
		bool validInput{ true };
		do {
			validInput = true;
			std::cout << "Enter column number you want to drop a disc in (1-7), or G to Give Up : ";
			std::cin >> answer;
			cont = answer != "G" && answer != "g";
			if (cont)
			{
				auto column = answer[0] - '1';
				if (column >= 0 && column < Board::COLUMNS && board.GetSize(column) < Board::MAX_DISCS_PER_COLUMN)
				{
					board.Drop(Value::Yellow, column);
				}
				else
				{
					std::cout << "Invalid input, try again\n";
					validInput = false;
				}
			}
		} while (!validInput);

		//check end of game
		auto winner = board.HasFourInARow();
		if ( winner != Value::None )
		{
			cont = false;
			PrintBoard(board);
			std::cout << "The winner is " << (winner == Value::Red ? "red" : "yellow");
		}

    } while (cont);
}
