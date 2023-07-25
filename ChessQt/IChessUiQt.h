#pragma once
#include <vector>
#include <utility>
#include <string>
#include <memory>
#include <optional>
#include "Enums.h"
#include "ChessUiQtListener.h"

using PieceInfo = std::pair<PieceType, PieceColor>;
using BoardRepresentation = std::array<std::array<PieceInfo, 8>, 8>;
using IChessUiQtPtr = std::shared_ptr<class IChessUiQt>;

class IChessUiQt {
public:
    virtual void UpdateHistory(const std::vector<std::string>& history) = 0;
    
    virtual void UpdateBoard(const BoardRepresentation& newBoard) = 0;

    virtual void ResetSelected() = 0;
    virtual void HighlightPossibleMoves(const std::vector<std::pair<int, int>>& possibleMoves) = 0;
    
    virtual void ShowPromoteOptions() = 0;
    
    virtual void SetMessageLabel(const std::string& value) = 0;
    
    virtual void ShowMessageBox(const std::string& value) = 0;
    
    virtual void SetTimer(const std::string& value, PieceColor color) = 0;

    virtual void AddListener(ChessUiQtListener* listener) = 0;
    virtual void RemoveListener(ChessUiQtListener* listener) = 0;

    virtual std::optional<std::pair<int, int>> GetSelectedPosition() = 0;

    virtual void show() = 0;

    static IChessUiQtPtr Produce();
};