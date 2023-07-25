#pragma once
#include "ChessException.h"

class DrawProposedException : public ChessException
{
public:
	DrawProposedException(const std::string&);
};

