#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"

Queen::Queen(EColor color) :Piece(EPieceType::Queen, color)
{
}

bool Queen::IsMoveRegular(Position p1, Position p2) const
{
	return (Rook::RookMove(p1, p2) || Bishop::BishopMove(p1, p2));
}

PositionList Queen::DeterminePattern(Position p1, Position p2) const
{
	PositionList newPosition;

	int x1 = p1.first, 
		y1 = p1.second,
		x2 = p2.first, 
		y2 = p2.second;

	if (x1 == x2 || y1 == y2)
	{
		Rook R(EColor::White);
		newPosition = R.DeterminePattern(p1, p2);
	}
	else
	{
		Bishop B(EColor::White);
		newPosition = B.DeterminePattern(p1, p2);
	}

	return newPosition;
}

PositionMatrix Queen::AllMoves(Position p) const
{
	Rook R(EColor::White);
	Bishop B(EColor::White);

	PositionMatrix rookMoves = R.AllMoves(p);
	PositionMatrix bishopMoves = B.AllMoves(p);
	
	PositionMatrix newMatrix;

	newMatrix.resize(8);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < rookMoves[i].size(); j++)
		{
			newMatrix[i].push_back(rookMoves[i][j]);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < bishopMoves[i].size(); j++)
		{
			newMatrix[i + 4].push_back(bishopMoves[i][j]);
		}
	}

	return newMatrix;
}
