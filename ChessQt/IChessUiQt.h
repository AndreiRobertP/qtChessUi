#pragma once
#include <vector>
#include <utility>
#include <string>
#include "Enums.h"
#include "ChessUiQtListener.h"

typedef std::array<std::array<std::pair<PieceType, PieceColor>, 8>, 8> BoardRepresentation;
typedef std::shared_ptr<class IChessUiQt> IChessUiQtPtr;

class IChessUiQt {
public:
    virtual void UpdateHistory(const std::vector<std::string>& history) = 0; //TODO change me...
    virtual void UpdateBoard(const BoardRepresentation& newBoard) = 0;
    virtual void HighlightPossibleMoves(const std::vector<std::pair<int, int>>& possibleMoves) = 0;
    virtual void StartGame() = 0;
    virtual void ShowPromoteOptions() = 0;
    virtual void SetMessageLabel(const std::string& value) = 0;
    virtual void ShowMessageBox(const std::string& value) = 0;
    virtual void SetTimer(const std::string& value, PieceColor color) = 0;
    virtual void ResetSelected() = 0;

    virtual void AddListener(ChessUiQtListener* listener) = 0;
    virtual void RemoveListener(ChessUiQtListener* listener) = 0;

    IChessUiQtPtr Produce();
};
