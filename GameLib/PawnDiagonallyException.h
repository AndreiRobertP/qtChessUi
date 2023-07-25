#pragma once
#include "ChessException.h"
class PawnDiagonallyException : public ChessException
{
public:
	PawnDiagonallyException(const std::string&);
};

