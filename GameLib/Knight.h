#pragma once

#include "Piece.h"

class Knight : public Piece
{
public:
	// Constructor
	Knight(EColor);
	
	// Piece methods
	bool IsMoveRegular(Position p1, Position p2) const override;

	PositionList DeterminePattern(Position p1, Position p2) const override;

	PositionMatrix AllMoves(Position p) const override;

private:
	// Other methods
	static bool VertL(Position p1, Position p2)
	{
		int x1 = p1.first,
			y1 = p1.second,
			x2 = p2.first,
			y2 = p2.second;

		return (AbsValue(x2, x1) == 1 && AbsValue(y2, y1) == 2);
	}

	static bool HorizontL(Position p1, Position p2)
	{
		int x1 = p1.first,
			y1 = p1.second,
			x2 = p2.first,
			y2 = p2.second;

		return (AbsValue(x2, x1) == 2 && AbsValue(y2, y1) == 1);
	}
};

