#pragma once

#include <vector>
#include <utility>
#include <string>
#include <memory>
#include <optional>

#include "Enums.h"
#include "IChessUiListener.h"

using PieceInfo = std::pair<PieceType, PieceColor>;
using BoardRepresentation = std::array<std::array<PieceInfo, 8>, 8>;
using IChessUiQtPtr = std::shared_ptr<class IChessUi>;

using OptionalPosition = std::optional<Position>;

using MovesList = std::vector<std::string>;

class IChessUi 
{
public:
    virtual void UpdateBoard(const BoardRepresentation& board) = 0;

    virtual OptionalPosition GetSelected() = 0;
    virtual void ResetSelected() = 0;
    virtual void Highlight(const PositionList& positions) = 0;
    
    virtual void ShowPromoteOptions() = 0;
    
    virtual void SetMessage(const std::string& value) = 0;
    virtual void ShowMessage(const std::string& value) = 0;
    virtual void SetClipboard(const std::string& value) = 0;

    virtual void UpdateMoves(const MovesList& moves) = 0;
    
    virtual void SetTimer(const std::string& value, PieceColor color) = 0;

    virtual void AddListener(IChessUiListener* listener) = 0;
    virtual void RemoveListener(IChessUiListener* listener) = 0;

    virtual void Show() = 0;

    static IChessUiQtPtr Produce();

    virtual ~IChessUi() = default;
};