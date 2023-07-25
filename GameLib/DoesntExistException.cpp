#include "DoesntExistException.h"

DoesntExistException::DoesntExistException(const std::string& message)
	: ChessException(message)
{
}
