#pragma once

#include "IGame.h"
#include "Board.h"
#include "Piece.h"
#include "EState.h"

#include<vector>
#include<memory>


class Game : public IGame
{
public:
	// Constructor
	Game();
	Game(const Board& b, EColor color = EColor::White);
	Game(const CharMatrix& matrix, EColor color = EColor::White);
	

	// IGame methods
	void Move(Position p1, Position p2) override;
	void ProposeDraw() override;
	void DrawResponse(bool) override;

	IPieceInfoPtr GetPieceInfo(Position) const override;
	EColor GetTurn() const override;

	bool IsDraw() const override;
	bool IsOver() const override;
	bool IsDrawProposed() const override;

	bool ChoosePiece() const override;
	void PromoteTo(const std::string& string, Position p) override;

	//Other methods
	PiecesPtr GetPiece(Position) const;
	bool Stalemate() const;

	PositionList GetMoves(Position p)const override;

	void AddListener(IGameListener* listener) override;
	void RemoveListener(IGameListener* listener) override;

private:
	void SwitchTurn();
	void UpdateState(EState);

private:
	Board m_gameboard;
	EColor m_turn;
	EState m_state;
	std::vector<IGameListener*> m_Listeners;
};