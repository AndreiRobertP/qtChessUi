#pragma once
#include "IChessUiQt.h"
#include "IGame.h"
#include <array>

class ChessLink : public ChessUiQtListener, public IGameListener
{
public:
    ChessLink();

    void OnButtonClicked(const std::pair<int, int>& position, bool isFirstClick) override;
    void OnFileChosen(const std::string& path, FileOperation operation) override;
    void OnUiEvent(UiEvent event) override;
    void OnHistoryClicked(int item) override;
    void OnPromoteOptionChosen(PieceType pieceType) override;

    void SetUi(IChessUiQtPtr ui);
    void OnStateChanged(EState state);

    void Start();

private:
    BoardRepresentation ConvertToBoardRepresentation();
    PieceType ConvertToType(EPieceType type);
    std::string PieceTypeToString(PieceType type);

private:
    IChessUiQtPtr m_Ui;
    IGamePtr m_Game;
    Position m_LastPosition;
};