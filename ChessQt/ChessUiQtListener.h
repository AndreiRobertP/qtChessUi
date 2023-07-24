#pragma once
#include <utility>
#include <string>
#include "Enums.h"

enum UiEvent
{
    RestartButtonClicked,
    PauseTimerButtonClicked,
    DrawProposed,
    DrawAccepted,
    DrawDenied,
};

enum FileOperation {
    Save,
    Load,
};

class ChessUiQtListener
{
public:
    virtual void OnButtonClicked(const std::pair<int, int>& position, bool isFirstClick) = 0;
    virtual void OnFileChosen(const std::string& path, FileOperation operation) = 0;
    virtual void OnUiEvent(UiEvent event) = 0;
    virtual void OnHistoryClicked(int item) = 0;
    virtual void OnPromoteOptionChosen(PieceType pieceType) = 0;
};