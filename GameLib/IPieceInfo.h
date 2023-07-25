#pragma once

#include "EPieceType.h"
#include "EColor.h"

#include <memory>

using IPieceInfoPtr = std::shared_ptr<class IPieceInfo>;

class IPieceInfo
{
public:
	static IPieceInfoPtr Produce(EPieceType type, EColor color);

	virtual EPieceType GetType() const = 0;
	
	virtual EColor GetColor() const = 0;

	virtual ~IPieceInfo() = default;
};
