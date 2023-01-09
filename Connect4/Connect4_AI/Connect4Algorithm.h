#pragma once
#include "Board.h"


class Connect4Algorithm
{
	Value m_MachinePlayer;
	Value m_HumanPlayer;
	int m_Level;

	int AlphaBeta(Board& board, int depth, int alpha, int beta, bool maximizingPlayer, int& col)
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
					int score = AlphaBeta(board, depth - 1, alpha, beta, false, column);
					board.RemoveDisc(c);
					//std::cout << " - Column " << c << ", score: " << score << "\n";
					if (value < score)
					{
						value = score;
						bestColumn = c;
						//std::cout << "Setting best column to " << bestColumn << " (c is " << c << ")\n";
					}
					alpha = alpha > value ? alpha : value;
					if (alpha >= beta)
					{
						break;
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
					int score = AlphaBeta(board, depth - 1, alpha, beta, true, column);
					board.RemoveDisc(c);
					//std::cout << " - Column " << c << ", score: " << score << "\n";
					if (value > score)
					{
						value = score;
						bestColumn = c;
					}
					beta = beta < value ? beta : value;
					if (alpha >= beta)
					{
						break;
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
		int alpha{ INT32_MIN };
		int beta{ INT32_MAX };
		AlphaBeta(board, 2 + m_Level, alpha, beta, true, column);
		return column;
	}
};
