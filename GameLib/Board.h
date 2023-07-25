#pragma once

#include "Piece.h"
#include "IPieceInfo.h"

#include<array>
#include<string>

using ChessBoard = std::array<std::array<PiecesPtr, 8>, 8>;
using CharMatrix = std::array<std::array<char, 8>, 8>;
using Matrix = std::vector<std::vector<int>>;
using Array = std::vector<int>;

class Board
{
public:
	// Constructors
	Board();
	Board(const CharMatrix&);

	// Setters
	PiecesPtr& operator[](Position p);

	// Getters
	IPieceInfoPtr GetPieceInfo(Position p) const;
	PiecesPtr GetPiece(Position p) const;

	// Functions
	bool IsOver(EColor color) const;
	bool VerifyTheWay(Position p1, Position p2);
	bool IsCheck(Position p, EColor color) const;
	bool IsSameWay(Position p1, Position p2, EColor color) const;
	bool IsCheckMate(EColor color) const;
	bool IsDraw() const;
	bool Stalemate(EColor color) const;

	Position FindCheck(Position p, EColor color) const;
	Position FindKing(EColor) const;
	PieceVector RemainingPieces() const;

	void PromoteTo(const std::string& string, Position p, EColor color);
	void UpdatePiece(EPieceType type, Position p, EColor color);

	void Move(Position p1, Position p2);
	PositionList GetMoves(Position p) const;

	bool Check3Fold(const Array& array) const;

private:
	static bool PawnGoesDiagonally(Position p1, Position p2);

	bool OnlyKing(EColor color)const;
	bool FindHelp(Position p, EColor color) const;
	bool KillCheck(Position p, EColor color) const;
	bool IsDefended(Position p, EColor color) const;
	bool SameBishop()const;
	bool PawnException(Position p1, Position p2)const;
	bool IsCastle(Position p1, Position p2);

	void Castle(Position p1, Position p2);

	PositionList DefendedPositions(Position p, EColor color) const;

	int Find(PieceVector v, EPieceType Piece) const;

	static EColor OppositeColor(EColor color)
	{
		if (color == EColor::White)
			return EColor::Black;
		return EColor::White;
	}

	int Convert(Position p) const;

	Array GetCurrentPosition() const;

	void UpdatePrevPositions();

	void InitializeWhite(char c, Position p);
	void InitializeBlack(char c, Position p);


private:
	ChessBoard m_board;
	Matrix m_prevPositions;
};