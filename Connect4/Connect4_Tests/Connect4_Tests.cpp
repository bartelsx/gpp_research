#include "pch.h"
#include "CppUnitTest.h"

#include "Board.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Connect4Tests
{
	TEST_CLASS(BoardTests)
	{
	public:

		TEST_METHOD(NewBoardContainsNoDiscs)
		{
			//Act
			Board b{};

			//Assert
			for (int i = 0; i < 7; ++i)
			{
				Assert::AreEqual(0, int(b.GetSize(i)));
			}
		}

		TEST_METHOD(Drop_AddsDiscToColumn)
		{
			//Arrange
			Board b{};

			//Act
			b.Drop(Value::Red, 3);

			//Assert
			Assert::AreEqual(int(Value::Red), int(b.GetValue(0, 3)));
		}

		TEST_METHOD(Drop_CantDropTooManyDiscsInOneColumn)
		{
			//Arrange
			Board b{};

			//Act & Assert
			Assert::ExpectException<std::out_of_range>([&b]()
				{
					for (int row = 0; row <= Board::MAX_DISCS_PER_COLUMN; ++row)
					{
						b.Drop(Value::Red, 3);
					}

				});
		}

		TEST_METHOD(GetValue_ReturnsEmptyWhenNotEnoughDiscsInThatColumn)
		{
			//Arrange
			Board b{};

			//Act
			b.Drop(Value::Red, 3);

			//Assert
			Assert::AreEqual(int(Value::None), int(b.GetValue(1, 3)));
		}

		TEST_METHOD(GetValue_ReturnsDiscValueWhenEnoughDiscsInThatColumn)
		{
			//Arrange
			Board b{};

			//Act
			b.Drop(Value::Red, 3);
			b.Drop(Value::Yellow, 3);

			//Assert
			Assert::AreEqual(int(Value::Yellow), int(b.GetValue(1, 3)));
		}

		TEST_METHOD(HasForInARow_ReturnsNone)
		{
			//Arrange
			Board b{};

			//Act
			b.Drop(Value::Yellow, 1);
			b.Drop(Value::Yellow, 1);
			b.Drop(Value::Yellow, 1);

			//Assert
			Assert::AreEqual(int(Value::None), int(b.HasFourInARow()));
		}

		TEST_METHOD(HasForInARow_ReturnsWinner_Vertical)
		{
			//Arrange
			Board b{};

			//Act
			b.Drop(Value::Yellow, 1);
			b.Drop(Value::Yellow, 1);
			b.Drop(Value::Yellow, 1);
			b.Drop(Value::Yellow, 1);

			//Assert
			Assert::AreEqual(int(Value::Yellow), int(b.HasFourInARow()));
		}

		TEST_METHOD(CalculateScore_YYYY_Horizontal_Left)
		{
			//Arrange
			Board b{};

			//Act
			b.Drop(Value::Yellow, 0);
			b.Drop(Value::Yellow, 1);
			b.Drop(Value::Yellow, 2);
			b.Drop(Value::Yellow, 3);

			//Assert
			//Expected value is 1070 == 1000 (YYYY) + 50 (YYYE) + 20 (YYEE)
			Assert::AreEqual(1067, b.CalculateScore(Value::Yellow));
		}

		TEST_METHOD(CalculateScore_YYYY_Vertical)
		{
			//Arrange
			Board b{};

			//Act
			b.Drop(Value::Yellow, 3);
			b.Drop(Value::Yellow, 3);
			b.Drop(Value::Yellow, 3);
			b.Drop(Value::Yellow, 3);

			//Assert
			//Expected value is 1070 == 1000 (YYYY) + 50 (YYYE) + 20 (YYEE)
			Assert::AreEqual(1058, b.CalculateScore(Value::Yellow));
		}

		TEST_METHOD(CalculateScore_YYYY_ForwardDiagonal)
		{
			//Arrange
			Board b{};

			b.Drop(Value::Yellow, 1);
			b.Drop(Value::Red, 2);
			b.Drop(Value::Yellow, 2);
			b.Drop(Value::Red, 3);
			b.Drop(Value::Red, 3);
			b.Drop(Value::Yellow, 3);
			b.Drop(Value::Red, 4);
			b.Drop(Value::Red, 4);
			b.Drop(Value::Red, 4);
			b.Drop(Value::Yellow, 4);

			//Act
			int score = b.CalculateScore(Value::Yellow);

			//Assert
			//Expected value is 990 == 1000 (YYYY) + 50 (YYYE) + 20 (YYEE) - 40 (RRRE Hor) - 40 (RRRE diag)
			Assert::AreEqual(981, score);
		}
	

		TEST_METHOD(CalculateScore_YYYY_BackwardDiagonal)
		{
			//Arrange
			Board b{};

			b.Drop(Value::Red, 1);
			b.Drop(Value::Red, 1);
			b.Drop(Value::Red, 1);
			b.Drop(Value::Yellow, 1);
			b.Drop(Value::Red, 2);
			b.Drop(Value::Red, 2);
			b.Drop(Value::Yellow, 2);
			b.Drop(Value::Red, 3);
			b.Drop(Value::Yellow, 3);
			b.Drop(Value::Yellow, 4);

			//Act
			auto score = b.CalculateScore(Value::Yellow);

			//Assert
			//Expected value is 970 == 1000 (YYYY) + 50 (YYYE) - 40 (RRRE Hor) - 40 (RRRE diag)
			Assert::AreEqual(964, score);
		}
	TEST_METHOD(CalculateScore_YEYY_Lose)
		{
			//Arrange
			Board b{};

			
			b.Drop(Value::Yellow, 1);
			//b.Drop(Value::Yellow, 2);
			b.Drop(Value::Yellow, 3);
			b.Drop(Value::Yellow, 4);

			//Act
			auto score = b.CalculateScore(Value::Yellow);

			//Assert
			//Expected value is 970 == 1000 (YYYY) + 50 (YYYE) - 40 (RRRE Hor) - 40 (RRRE diag)
			Assert::AreEqual(107, score);
		}
	
	};
}
;