#pragma once

enum class EState
{
	Playing,
	Draw,
	WhiteWon,
	BlackWon,
	DrawIsProposed,
	ChoosePiece,
	Check,
};