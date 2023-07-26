#pragma once
#include "IChessUi.h"
#include "IGame.h"
#include <array>

class ChessLink : public IChessUiListener, public IGameListener
{
public:
    ChessLink(IGame* game, IChessUi* ui);

    void OnButtonClicked(const std::pair<int, int>& position, bool isFirstClick) override;
    void OnFileOperation(const std::string& path, FileOperation operation) override;
    void OnUiEvent(UiEvent event) override;
    void OnMoveItemSelected(int item) override;
    void OnPromoteOption(PieceType pieceType) override;

	void OnMove();
	void OnGameOver();
	void OnDraw();
    void OnChoosePiece(Position);
    void OnCheck();

    void Start();

private:
    BoardRepresentation ConvertToBoardRepresentation();
    PieceType ConvertToType(EPieceType type);
    std::string PieceTypeToString(PieceType type);

private:
    IChessUi* m_Ui;
    IGame* m_Game;
    Position m_LastPosition;
};