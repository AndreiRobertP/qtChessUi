#pragma once
#include "Piece.h"

class Rook : public Piece
{
public:
	// Constructor
	Rook(EColor);
	
	// Piece methods
	bool IsMoveRegular(Position p1, Position p2) const override;

	PositionList DeterminePattern(Position p1, Position p2) const override;
	
	PositionMatrix AllMoves(Position p) const override;

	// Other methods
	static bool RookMove(Position p1, Position p2)
	{
		auto x1 = p1.first,
			x2 = p2.first,
			y1 = p1.second,
			y2 = p2.second;

		return ((x1 == x2) ^ (y1 == y2));
	}
};