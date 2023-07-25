#pragma once

#include "Enums.h"

#include <utility>
#include <string>

enum UiEvent
{
    RestartGame,
    PauseTimerButtonClicked,
    DrawProposed,
    DrawAccepted,
    DrawDenied,
};

enum FileOperation {
    Save,
    Load,
};

class IChessUiListener
{
public:
    virtual void OnButtonClicked(const Position& position, bool isFirstClick) = 0;
    virtual void OnFileOperation(const std::string& path, FileOperation operation) = 0;
    virtual void OnUiEvent(UiEvent event) = 0;
    virtual void OnMoveItemSelected(int item) = 0;
    virtual void OnPromoteOption(PieceType pieceType) = 0;

    virtual ~IChessUiListener() = default;
};