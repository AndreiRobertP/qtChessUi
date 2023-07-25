#pragma once
#include "ChessException.h"
class PromoteException :  public ChessException
{
public:
	PromoteException(const std::string&);
};

