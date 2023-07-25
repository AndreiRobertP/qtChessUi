#pragma once
#include "ChessException.h"

class SameColorException : public ChessException
{
public:
	SameColorException(const std::string&);
};

