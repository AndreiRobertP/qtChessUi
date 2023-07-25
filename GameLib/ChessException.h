#pragma once

#include <stdexcept>

class ChessException : public std::logic_error
{
public:
	ChessException();
	ChessException(const std::string&);
};

