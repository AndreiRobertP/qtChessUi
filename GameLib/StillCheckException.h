#pragma once
#include "ChessException.h"
class StillCheckException : public ChessException
{
public:
	StillCheckException(const std::string&);
};

