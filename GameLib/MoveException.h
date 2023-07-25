#pragma once

#include "ChessException.h"

class MoveException :  public ChessException
{
public:
	MoveException(const std::string&);
};

