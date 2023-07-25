#pragma once

enum class PieceType {
	none, king, rook, bishop, queen, knight, pawn
};

enum class PieceColor {
	none, black, white
};

using Position = std::pair<int, int>;
using PositionList = std::vector<Position>;
