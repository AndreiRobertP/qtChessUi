#pragma once
#include "IChessUiQt.h"

class ChessLink : public ChessUiQtListener
{
public:
    ChessLink();

    void OnButtonClicked(const std::pair<int, int>& position, bool isFirstClick) override;
    void OnFileChosen(const std::string& path, FileOperation operation) override;
    void OnUiEvent(UiEvent event) override;
    void OnHistoryClicked(int item) override;
    void OnPromoteOptionChosen(PieceType pieceType) override;

    void SetUi(IChessUiQtPtr ui);
private:
    IChessUiQtPtr m_Ui;
};

