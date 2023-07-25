#pragma once

#include "IPieceInfo.h"

class PieceInfo : public IPieceInfo
{
public:
	// Constructor
	PieceInfo(EPieceType type, EColor color);

	// IPieceInfo methods
	EPieceType GetType()const override;
	EColor GetColor()const override;

private:
	EPieceType m_type;
	EColor m_color;
};

