#include "PieceInfo.h"

#include <memory>

PieceInfo::PieceInfo(EPieceType type, EColor color) 
	: m_type(type)
	, m_color(color)
{
}

IPieceInfoPtr IPieceInfo::Produce(EPieceType type, EColor color)
{
	return std::make_shared<PieceInfo>(type, color);
}

EPieceType PieceInfo::GetType() const
{
	return m_type;
}

EColor PieceInfo::GetColor() const
{
	return m_color;
}
