#pragma once

#include <QtWidgets/QMainWindow>
#include "GridButton.h"
#include <QtWidgets/qgridlayout.h>
#include <QLabel>
#include <QListWidget>
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QClipboard>
#include <QApplication>
#include <exception>

#include "IChessUi.h"

class ChessUi : public QMainWindow, public IChessUi
{
    Q_OBJECT

public:
    ChessUi(QWidget *parent = nullptr);
    ~ChessUi() override;

    void UpdateMoves(const std::vector<std::string>& history) override;
    void UpdateBoard(const BoardRepresentation& newBoard) override;
    void Highlight(const std::vector<std::pair<int, int>>& possibleMoves) override;
    void ShowPromoteOptions() override;
    void SetMessage(const std::string& value) override;
    void SetClipboard(const std::string& value) override;
    void SetTimer(const std::string& value, PieceColor color) override;
    void ShowMessage(const std::string& value) override;
    void ResetSelected() override;
    std::optional<std::pair<int, int>> GetSelected() override;

    void AddListener(IChessUiListener* listener) override;
    void RemoveListener(IChessUiListener* listener) override;

private:
    void InitializeMessage(QGridLayout* mainGridLayout);
    void InitializeButtons(QGridLayout* mainGridLayout);
    void InitializeTimers(QGridLayout* mainGridLayout);
    void InitializeHistory(QGridLayout* mainGridLayout);
    void InitializeBoard(QGridLayout* mainGridLayout);

    void Show() override;

private slots:
    void OnButtonClicked(const std::pair<int, int>& position);

    void OnSaveButtonClicked();
    void OnLoadButtonClicked();
    void OnRestartButtonClicked();
    void OnDrawButtonClicked();
    void OnHistoryClicked(QListWidgetItem* item);
    void OnPauseButtonClicked();
    void OnCopyFENButtonClicked();
    void OnCopyPGNButtonClicked();

private:
    std::array<std::array<GridButton*, 8>, 8> m_grid;
    std::optional<std::pair<int, int>> m_selectedCell;
    QLabel* m_MessageLabel;
    QListWidget* m_HistoryList;
    QLabel* m_BlackTimer, *m_WhiteTimer;
    std::vector<IChessUiListener*> m_Listeners;
};
