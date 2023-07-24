#include "ChessLink.h"

ChessLink::ChessLink()
{}

void ChessLink::OnButtonClicked(const std::pair<int, int>& position, bool isFirstClick)
{
}

void ChessLink::OnFileChosen(const std::string& path, FileOperation operation)
{
}

void ChessLink::OnUiEvent(UiEvent event)
{
}

void ChessLink::OnHistoryClicked(int item)
{
}

void ChessLink::OnPromoteOptionChosen(PieceType pieceType)
{
}

void ChessLink::SetUi(IChessUiQtPtr ui)
{
	m_Ui = ui;
	m_Ui->AddListener(this);
}
