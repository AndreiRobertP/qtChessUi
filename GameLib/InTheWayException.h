#pragma once
#include "ChessException.h"

class InTheWayException :  public ChessException
{
public:
	InTheWayException(const std::string&);
};

