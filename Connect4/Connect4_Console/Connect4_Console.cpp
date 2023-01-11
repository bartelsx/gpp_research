// Connect4_Console.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <conio.h>

#include "Board.h"
#include "Connect4Algorithm.h"


#define LEVEL 4 //1 to 6
#define MACHINE_COLOR Value::Red
#define MACHINE_PLAYS_FIRST true

#define NORMAL 7
#define RED 12
#define YELLOW 14

void PrintBoard(const Board& board)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	system("CLS");
	std::cout << "\n";
	std::cout << " +---------------------------+\n";
	std::cout << " |       Xander Bartels      |\n";
	std::cout << " |         Connect 4         |\n";
	std::cout << " +---------------------------+\n";
	std::cout << "\n";
	std::cout << " +---------------------------+\n";
	for (int row = Board::MAX_DISCS_PER_COLUMN - 1; row >= 0; --row)
	{
		for (int column = 0; column < Board::COLUMNS; ++column)
		{
			auto value = board.GetValue(row, column);

			std::cout << " | ";

			SetConsoleTextAttribute(hConsole, value == Value::None ? NORMAL : value == Value::Red ? RED : YELLOW);
			std::cout << (value == Value::None ? " " : value == Value::Red ? "R" : "Y");
			SetConsoleTextAttribute(hConsole, NORMAL);
		}
		std::cout << " |\n";
	}
	std::cout << " +---------------------------+\n";
	std::cout << " | 1 | 2 | 3 | 4 | 5 | 6 | 7 |\n";
	std::cout << " +---------------------------+\n";
}

void LetMachineMakeMove(Connect4Algorithm& algorithm, Board& board)
{
	std::cout << "I'm thinking ...";

	//let AI do its action
	int columnToPlay = algorithm.GetNextMove(board);
	if (columnToPlay >= 0 && columnToPlay <= Board::COLUMNS)
	{
		board.Drop(MACHINE_COLOR, columnToPlay);
	}
	else
	{
		std::cout << "Machine can not make a move :O ";
	}

}

bool LetHumanMakeMove(Board& board)
{
	std::string answer;

	//ask player action
	bool validInput;
	do {
		validInput = true;
		std::cout << "Enter column number you want to drop a disc in (1-7), or G to Give Up : ";
		std::cin >> answer;
		if (answer == "G" || answer == "g")
		{
			return false;
		}

		auto column = answer[0] - '1';
		if (column >= 0 && column < Board::COLUMNS && board.GetSize(column) < Board::MAX_DISCS_PER_COLUMN)
		{
			board.Drop(MACHINE_COLOR == Value::Red ? Value::Yellow : Value::Red, column);
		}
		else
		{
			std::cout << "Invalid input, try again\n";
			validInput = false;
		}
	} while (!validInput);
	return true;
}

int main()
{
	Board board{};
	Connect4Algorithm algorithm{MACHINE_COLOR, LEVEL};

	bool endOfGame{ false };
	bool machineIsPlaying{ MACHINE_PLAYS_FIRST };

	do
	{
		PrintBoard(board);

		if (machineIsPlaying)
		{
			LetMachineMakeMove(algorithm, board);
		}
		else
		{
			if (!LetHumanMakeMove(board))
			{
				std::cout << "You gave up - you lose !";
				endOfGame = true;
			}
		}
		machineIsPlaying = !machineIsPlaying;

		//check end of game
		auto winner = board.HasFourInARow();
		if (winner != Value::None)
		{
			endOfGame = true;
			PrintBoard(board);
			std::cout << "The winner is " << (winner == Value::Red ? "red" : "yellow");
		}

	} while (!endOfGame);
}
