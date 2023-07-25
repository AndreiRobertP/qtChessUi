#pragma once
#include "Piece.h"

class Queen : public Piece
{
public:
    // Constructor
    Queen(EColor);

    // Piece methods
    bool IsMoveRegular(Position p1, Position p2) const override;

    PositionList DeterminePattern(Position p1, Position p2) const override;
   
    PositionMatrix AllMoves(Position p) const override;
};

