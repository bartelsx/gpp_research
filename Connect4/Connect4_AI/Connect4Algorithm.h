#include "Board.h"
#include <iostream>


class Connect4Algorithm
{
	Value m_MachinePlayer;
	Value m_HumanPlayer;
	int m_Level;

	int MiniMax(Board& board, int depth, bool maximizingPlayer, int& col)
	{
		Value winner = board.HasFourInARow();
		if (m_MachinePlayer == winner) return 1'000'000;
		if (m_HumanPlayer == winner) return -1'000'000;

		if (depth == 0)
		{
			return board.CalculateScore(m_MachinePlayer);
		}

		if (board.IsFull()) return 0;

		if (maximizingPlayer)
		{
			int value{ INT32_MIN };
			int bestColumn{ -1 };
			for (int c = 0; c < Board::COLUMNS; ++c)
			{
				if (board.GetSize(c) < Board::MAX_DISCS_PER_COLUMN)
				{
					//std::cout << "Finding Max for column " << c << "\n";
					board.Drop(m_MachinePlayer, c);
					int column;
					int score = MiniMax(board, depth - 1, false, column);
					board.RemoveDisc(c);
					//std::cout << " - Column " << c << ", score: " << score << "\n";
					if (value < score)
					{
						value = score;
						bestColumn = c;
						//std::cout << "Setting best column to " << bestColumn << " (c is " << c << ")\n";
					}
					
				}
			}
			//std::cout << "Max: Depth=" << depth << ", bestColumn=" << bestColumn << ", value=" << value << "\n";
			col = bestColumn;
			return value;
		}
		else //minimizing player
		{
			int value{ INT32_MAX };
			int bestColumn{ -1 };
			for (int c = 0; c < Board::COLUMNS; ++c)
			{
				if (board.GetSize(c) < Board::MAX_DISCS_PER_COLUMN)
				{
					//std::cout << "Finding Min for column " << c << "\n";
					board.Drop(m_HumanPlayer, c);
					int column;
					int score = MiniMax(board, depth - 1, true, column);
					board.RemoveDisc(c);
					//std::cout << " - Column " << c << ", score: " << score << "\n";
					if (value > score)
					{
						value = score;
						bestColumn = c;
					}
					
				}
			}
			//std::cout << "Min: Depth=" << depth << ", bestColumn=" << bestColumn << ", value=" << value << "\n";
			col = bestColumn;
			return value;
		}
	}

public:
	Connect4Algorithm(Value machinePlayer = Value::Red, int level = 2)
		: m_MachinePlayer{ machinePlayer }
		, m_Level{ level }
	{
		m_HumanPlayer = m_MachinePlayer == Value::Red ? Value::Yellow : Value::Red;
	}

	int GetNextMove(Board& board)
	{
		//Minimax algorithm
		int column;
		MiniMax(board, 2 + m_Level, true, column);
		return column;
	}
};
