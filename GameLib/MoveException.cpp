#include "MoveException.h"

MoveException::MoveException(const std::string& message)
	: ChessException(message)
{
}