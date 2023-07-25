#include "TurnException.h"

TurnException::TurnException(const std::string& message)
	: ChessException(message)
{
}
