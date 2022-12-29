#pragma once

#include <array>
#include <stdexcept>
#include <vector>

enum class Value
{ None, Red, Yellow  };

class Board
{

	std::array<std::vector<Value>, 7> m_values{};

	void AssertColumn(int column) const
	{
		if (column < 0 || column >= COLUMNS)
			throw new std::out_of_range("Column number can't be less than 0 or greater than 6");
	}

	int CountInWindow(int startRow, int startCol, int deltaRow, int deltaCol, Value piece) const
	{
		int row{ startRow }, col{ startCol };
		int count{};

		for (int i=0; i<4; ++i)
		{
			if (row<0 || row>MAX_DISCS_PER_COLUMN || col<0 || col>COLUMNS)
			{
				break;
			}
			if (GetValue(row, col)==piece)
			{
				++count;
			}
			row += deltaRow;
			col += deltaCol;
		}
		return count;
	}


	int ScoreWindow(int startRow, int startCol, int deltaRow, int deltaCol, Value piece)
	{
		auto opponent = piece == Value::Red ? Value::Yellow : Value::Red;
		int score{};

		auto same = CountInWindow(startRow, startCol, deltaRow, deltaCol, piece);
		auto empty = CountInWindow(startRow, startCol, deltaRow, deltaCol, Value::None);
		if ( same == 4)
		{
			score += 1000;
		}
		else if (same==3 && empty==1)
		{
			score += 50;
		}
		else if (same==2 && empty==2)
		{
			score += 20;
		}

		if (/*opponent count == 3*/same == 0 && empty == 1 )
		{
			score -= 40;
		}

		return score;
	}

public:
	static const int COLUMNS = 7;
	static const int MAX_DISCS_PER_COLUMN = 6;

	int GetSize(int column) const
	{
		if (column < 0 || column >= Board::COLUMNS) return 0;
		return int(m_values[column].size());
	}

	void Drop(Value disc, int column)
	{
		AssertColumn(column);

		if (m_values[column].size() >= Board::MAX_DISCS_PER_COLUMN)
		{
			throw std::out_of_range("Can't add that many discs to the same column");
		}

		m_values[column].push_back(disc);
	}

	void RemoveDisc(int column)
	{
		AssertColumn(column);

		if (m_values[column].empty())
		{
			throw std::out_of_range("Can't remove disc from empty column");
		}

		m_values[column].pop_back();
	}

	Value GetValue(int row, int column) const
	{
		AssertColumn(column);

		if (m_values[column].size() <= row)
		{
			return Value::None;
		}

		return m_values[column][row];
	}

	Value HasFourInARow()
	{
		//Check Vertical
		for (int col=0; col<COLUMNS; ++col)
		{
			for (int row=0; row+3<m_values[col].size(); ++row)
			{
				auto v1 = GetValue(row, col);
				if (v1 != Value::None 
					&& v1 == GetValue(row+1, col) 
					&& v1 == GetValue(row+2, col) 
					&& v1 == GetValue(row+3,col))
				{
					return v1;
				}
			}
		}
		return Value::None;
	}

	int CalculateScore(Value discColor)
	{
		int score{-3*GetSize(3)};

		//Vertical
		for (int c=0; c<COLUMNS; ++c)
		{
			for (int r=0; r < MAX_DISCS_PER_COLUMN-3; ++r)
			{
				score += ScoreWindow(r, c, 1, 0, discColor);
			}
		}

		//Horizontal
		for (int r=0; r<MAX_DISCS_PER_COLUMN; ++r)
		{
			for (int c=0; c < COLUMNS-3; ++c)
			{
				score += ScoreWindow(r, c, 0, 1, discColor);
			}
		}

		//forward diagonal
		for (int r=0; r<MAX_DISCS_PER_COLUMN-3; ++r)
		{
			for (int c=0; c < COLUMNS-3; ++c)
			{
				score += ScoreWindow(r, c, 1, 1, discColor);
			}
		}

		//backward diagonal 
		
		for (int r=0; r<MAX_DISCS_PER_COLUMN-3; ++r)
		{
			for (int c=3; c < COLUMNS; ++c)
			{
				score += ScoreWindow(r, c, 1, -1, discColor);
			}
		}

		return score;
	}

	bool IsFull()
	{
		for (int c=0; c<COLUMNS; ++c)
		{
			if (GetSize(c)<MAX_DISCS_PER_COLUMN)
			{
				return false;
			}
		}
		return true;
	}

};

