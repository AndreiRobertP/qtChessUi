#pragma once

#include <QtWidgets/QMainWindow>
#include "GridButton.h"
#include <QtWidgets/qgridlayout.h>
#include <QLabel>
#include <QListWidget>
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <exception>

#include "IChessUiQt.h"

class ChessUIQt : public QMainWindow, public IChessUiQt
{
    Q_OBJECT

public:
    ChessUIQt(QWidget *parent = nullptr);
    ~ChessUIQt() override;

    void UpdateHistory(const std::vector<std::string>& history) override;
    void UpdateBoard(const BoardRepresentation& newBoard) override;
    void HighlightPossibleMoves(const std::vector<std::pair<int, int>>& possibleMoves) override;
    void StartGame() override;
    void ShowPromoteOptions() override;
    void SetMessageLabel(const std::string& value) override;
    void SetTimer(const std::string& value, PieceColor color) override;
    void ShowMessageBox(const std::string& value) override;
    void ResetSelected() override;

    void AddListener(ChessUiQtListener* listener) override;
    void RemoveListener(ChessUiQtListener* listener) override;

private:
    void InitializeMessage(QGridLayout* mainGridLayout);
    void InitializeButtons(QGridLayout* mainGridLayout);
    void InitializeTimers(QGridLayout* mainGridLayout);
    void InitializeHistory(QGridLayout* mainGridLayout);
    void InitializeBoard(QGridLayout* mainGridLayout);

    void show() override;

private slots:
    void OnButtonClicked(const std::pair<int, int>& position);

    void OnSaveButtonClicked();
    void OnLoadButtonClicked();
    void OnRestartButtonClicked();
    void OnDrawButtonClicked();
    void OnHistoryClicked(QListWidgetItem* item);
    void OnPauseButtonClicked();

private:
    std::array<std::array<GridButton*, 8>, 8> m_grid;
    std::optional<std::pair<int, int>> m_selectedCell;
    QLabel* m_MessageLabel;
    QListWidget* m_HistoryList;
    QLabel* m_BlackTimer, *m_WhiteTimer;
    std::vector<ChessUiQtListener*> m_Listeners;
};

//TODO REMOVE THIS AFTER IMPLEMENTATION
class Helper {
public:
    static std::array<std::array<std::pair<PieceType, PieceColor>, 8>, 8> getDefaultBoard() {
        std::array<std::array<std::pair<PieceType, PieceColor>, 8>, 8> board;
        for (int rank = 0; rank < 8; ++rank) {
            for (int file = 0; file < 8; ++file) {
                if (rank == 0 || rank == 7) {
                    PieceColor color = (rank == 0) ? PieceColor::black : PieceColor::white;
                    PieceType type;
                    switch (file) {
                    case 0:
                    case 7:
                        type = PieceType::rook;
                        break;
                    case 1:
                    case 6:
                        type = PieceType::knight;
                        break;
                    case 2:
                    case 5:
                        type = PieceType::bishop;
                        break;
                    case 3:
                        type = PieceType::queen;
                        break;
                    case 4:
                        type = PieceType::king;
                        break;
                    default:
                        type = PieceType::none;
                        break;
                    }
                    board[rank][file] = std::make_pair(type, color);
                }
                else if (rank == 1 || rank == 6) {
                    // Set up the pawns row with black and white pawns respectively
                    PieceColor color = (rank == 1) ? PieceColor::black : PieceColor::white;
                    board[rank][file] = std::make_pair(PieceType::pawn, color);
                }
                else {
                    // Empty squares for the rest of the board
                    board[rank][file] = std::make_pair(PieceType::none, PieceColor::none);
                }
            }
        }

        return board;
    }
};