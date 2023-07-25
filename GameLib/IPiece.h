#pragma once

#include "Position.h"
#include "EPieceType.h"
#include "EColor.h"
#include <utility>
#include <vector>

using PositionMatrix = std::vector<PositionList>;

class IPiece
{
public:
	virtual bool IsMoveRegular(Position p1, Position p2) const = 0 ;

	virtual PositionList DeterminePattern(Position p1, Position p2) const = 0;
	
	virtual PositionMatrix AllMoves(Position p) const = 0;
};
