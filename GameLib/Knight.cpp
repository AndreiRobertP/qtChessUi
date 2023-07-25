#include "Knight.h"

Knight::Knight(EColor color) :Piece(EPieceType::Knight, color)
{
}

bool Knight::IsMoveRegular(Position p1, Position p2) const
{
    return (VertL(p1,p2) || HorizontL(p1, p2));
}

PositionList Knight::DeterminePattern(Position p1, Position p2) const
{
    PositionList newPattern;

    if (IsInTable(p2))
    {
        newPattern.push_back(p2);
    }

    return newPattern;
}

PositionMatrix Knight::AllMoves(Position p) const
{
    PositionMatrix newMatrix;
    
    newMatrix.resize(8);

    auto x = p.first, y = p.second;

    Position  L1 = { x - 1, y - 2 },
              L2 = { x - 2, y - 1 },
              L3 = { x - 2, y + 1 },
              L4 = { x - 1, y + 2 },
              L5 = { x + 1, y + 2 },
              L6 = { x + 2, y + 1 },
              L7 = { x + 2, y - 1 },
              L8 = { x + 1, y - 2 };

    if (IsInTable(L1))
    {
        newMatrix[0].push_back({ x - 1, y - 2 });
    }

    if (IsInTable(L2))
    {
        newMatrix[1].push_back({ x - 2, y - 1 });
    }

    if (IsInTable(L3))
    {
        newMatrix[2].push_back({ x - 2, y + 1 });
    }

    if (IsInTable(L4))
    {
        newMatrix[3].push_back({ x - 1, y + 2 });
    }

    if (IsInTable(L5))
    {
        newMatrix[4].push_back({ x + 1, y + 2 });
    }

    if (IsInTable(L6))
    {
        newMatrix[5].push_back({ x + 2, y + 1 });
    }

    if (IsInTable(L7))
    {
        newMatrix[6].push_back({ x + 2, y - 1 });
    }

    if (IsInTable(L8))
    {
        newMatrix[7].push_back({ x + 1, y - 2 });
    }

    return newMatrix;
}
