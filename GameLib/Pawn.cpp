#include "Pawn.h"

Pawn::Pawn(EColor color) : Piece(EPieceType::Pawn, color)
{
}

bool Pawn::IsMoveRegular(Position p1, Position p2) const
{
	return (!WrongForward(p1, p2) && !MovesBackwards(p1, p2) && !WrongDiagonal(p1, p2));
}

PositionList Pawn::DeterminePattern(Position p1, Position p2) const
{
	PositionList newPattern;

	newPattern.push_back(p2);

	return newPattern;
}

PositionMatrix Pawn::AllMoves(Position p) const
{
	auto x = p.first, y = p.second;

	PositionMatrix newMatrix;

	newMatrix.resize(4);

	Position UpOne = { x - 1, y };	Position DownOne = { x + 1, y };
	Position UpLeft = { x - 1, y - 1 };	Position DownLeft = { x + 1, y - 1 };
	Position UpRight = { x - 1, y + 1 };	Position DownRight = { x + 1, y + 1 };
	Position UpTwo = { x - 2, y };	Position DownTwo = { x + 2, y };

	if (IsColor(EColor::White))
	{
		if(IsInTable(UpOne))
			newMatrix[0].push_back(UpOne);

		if (x == 6)
			newMatrix[1].push_back(UpTwo);

		if (IsInTable(UpLeft))
			newMatrix[2].push_back(UpLeft);

		if (IsInTable(UpRight))
			newMatrix[3].push_back(UpRight);
	}

	if (IsColor(EColor::Black))
	{
		if (IsInTable(DownOne))
			newMatrix[0].push_back(DownOne);

		if (x == 1)
			newMatrix[1].push_back(DownTwo);

		if (IsInTable(DownLeft))
			newMatrix[2].push_back(DownLeft);

		if (IsInTable(DownRight))
			newMatrix[3].push_back(DownRight);
	}

	return newMatrix;
}

bool Pawn::StartingPosition(int x) const
{
	return ((IsColor(EColor::White) && x == 6) || (IsColor(EColor::Black) && x == 1));
}

bool Pawn::MovesTooMuch(Position p1, Position p2) const
{
	int x1 = p1.first,
		y1 = p1.second,
		x2 = p2.first,
		y2 = p2.second;

	return (AbsValue(x2, x1) < 1 || AbsValue(x2, x1) >= 3 || (!StartingPosition(x1) && AbsValue(x2, x1) > 1));
}

bool Pawn::WrongForward(Position p1, Position p2) const
{
	int x1 = p1.first,
		y1 = p1.second,
		x2 = p2.first,
		y2 = p2.second;

	return (MovesTooMuch(p1, p2) || (y1 != y2));
}

bool Pawn::MovesBackwards(Position p1, Position p2) const
{
	int x1 = p1.first,
		y1 = p1.second,
		x2 = p2.first,
		y2 = p2.second;

	return (IsColor(EColor::White) && (x2 - x1 == 1)) || (IsColor(EColor::Black) && (x2 - x1 == -1));
}

bool Pawn::WrongDiagonal(Position p1, Position p2) const
{
	int x1 = p1.first,
		y1 = p1.second,
		x2 = p2.first,
		y2 = p2.second;

	return (IsColor(EColor::White) && x2 - x1 == 1 && AbsValue(y2, y1)) || (IsColor(EColor::Black) && x2 - x1 == -1 && AbsValue(y2, y1));
}
