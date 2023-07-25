#pragma once
#include "Piece.h"

class Pawn : public Piece
{
public:
    // Constructor
    Pawn(EColor);

    // Piece methods
    bool IsMoveRegular(Position p1, Position p2) const override;

    PositionList DeterminePattern(Position p1, Position p2) const override;

    PositionMatrix AllMoves(Position p) const override;

private:
    bool StartingPosition(int x) const;
    bool MovesTooMuch(Position p1, Position p2) const;
    bool WrongForward(Position p1, Position p2) const;
    bool MovesBackwards(Position p1, Position p2) const;
    bool WrongDiagonal(Position p1, Position p2) const;
};

