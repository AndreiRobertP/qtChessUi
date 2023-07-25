#pragma once
#include "ChessException.h"

class PositionException : public ChessException
{
public:
	PositionException(const std::string&);
};

