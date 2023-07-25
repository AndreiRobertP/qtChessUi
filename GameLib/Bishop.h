#pragma once
#include "Piece.h"

class Bishop : public Piece
{
public:
    // Constructor
    Bishop(EColor);
    
    // Piece methods
    bool IsMoveRegular(Position p1, Position p2) const override;

    PositionList DeterminePattern(Position p1, Position p2) const override;

    PositionMatrix AllMoves(Position p) const override;

	// Other methods
	static bool BishopMove(Position p1, Position p2)
	{
		auto x1 = p1.first,
			x2 = p2.first,
			y1 = p1.second,
			y2 = p2.second;

		return (AbsValue(x2, x1) == AbsValue(y2, y1) && AbsValue(x2, x1) != 0);
	}
};

