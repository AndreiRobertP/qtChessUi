#include "ChessException.h"

ChessException::ChessException(const std::string& message)
	: std::logic_error(message)
{
}

ChessException::ChessException()
	:std::logic_error("Unknown exception")
{
}
