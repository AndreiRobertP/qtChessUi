#pragma once

#include "ChessException.h"

class TurnException : public ChessException
{
public:
    TurnException(const std::string&);
};

