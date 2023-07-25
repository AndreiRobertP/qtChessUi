#pragma once
#include "ChessException.h"

class DoesntExistException : public ChessException
{
public:
	DoesntExistException(const std::string&);
};

