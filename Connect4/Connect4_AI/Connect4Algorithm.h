#include "Board.h"
#include <iostream>

class Connect4Algorithm
{
	Value m_MachinePlayer;
	Value m_HumanPlayer;

	int AlphaBeta(Board& board, int depth, int& alpha, int& beta, bool maximizingPlayer, int& col)
	{
		if (depth==0) 
		{
			if (maximizingPlayer)
			{
				return -board.CalculateScore(m_HumanPlayer);
			}
			else
			{
				return board.CalculateScore(m_MachinePlayer);
			}
		}
		Value winner = board.HasFourInARow();
		if (board.IsFull()) return 0;
		if (m_MachinePlayer == winner) return INT32_MAX;
		if (m_HumanPlayer == winner) return INT32_MIN;

		if (maximizingPlayer)
		{
			int value{ INT32_MIN };
			int bestColumn{};
			for (int c=0; c<Board::COLUMNS; ++c)
			{
				if (board.GetSize(c)<Board::MAX_DISCS_PER_COLUMN)
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
					alpha = std::max(alpha, value);
					//if (alpha >= beta)
					//{
					//	break;
					//}
				}
			}
			//std::cout << "Max: Depth=" << depth << ", bestColumn=" << bestColumn << ", value=" << value << "\n";
			col = bestColumn;
			return value;
		}
		else //minimizing player
		{
			int value{ INT32_MAX };
			int bestColumn{};
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
					beta = std::min(beta, value);
					//if (alpha >= beta)
					//{
					//	break;
					//}
				}
			}
			//std::cout << "Min: Depth=" << depth << ", bestColumn=" << bestColumn << ", value=" << value << "\n";
			col = bestColumn;
			return value;
		}
	}

public:
	Connect4Algorithm(Value machinePlayer=Value::Red)
		: m_MachinePlayer{machinePlayer}
	{
		m_HumanPlayer = m_MachinePlayer == Value::Red ? Value::Yellow : Value::Red;
	}

	int GetNextMove(Board& board)
	{
		//Minimax algorithm with alpha-beta pruning
		int alpha{ INT32_MIN }, beta{ INT32_MAX };
		int column;
		AlphaBeta(board, 2, alpha, beta, true, column);
		return column;
	}
};
