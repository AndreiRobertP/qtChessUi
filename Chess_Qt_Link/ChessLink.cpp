#include "ChessLink.h"


ChessLink::ChessLink()
{
	m_Game = IGame::Produce();
	m_Game->AddListener(this);
}

void ChessLink::OnButtonClicked(const std::pair<int, int>& position, bool isFirstClick)
{
	m_LastPosition = position;

	if (isFirstClick == false) {
		try {
			m_Game->Move(m_Ui->GetSelectedPosition().value(), position);
		}
		catch (std::exception e) {
			m_Ui->ShowMessageBox(e.what());
			m_Ui->UpdateBoard(ConvertToBoardRepresentation());
		}
	}
	else {
		try {
			m_Ui->HighlightPossibleMoves(m_Game->GetMoves(position));
		}
		catch (std::exception e) {
			m_Ui->ShowMessageBox(e.what());
			m_Ui->UpdateBoard(ConvertToBoardRepresentation());
		}
	}
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
	m_Game->PromoteTo(PieceTypeToString(pieceType), m_LastPosition);
}

void ChessLink::SetUi(IChessUiQtPtr ui)
{
	m_Ui = ui;
	m_Ui->AddListener(this);

}

void ChessLink::OnStateChanged(EState state) {
	if (state == EState::Playing) {
		m_Ui->SetMessageLabel(m_Game->GetTurn() == EColor::Black ? "Black's turn" : "White's turn");
		m_Ui->UpdateBoard(ConvertToBoardRepresentation());
		return;
	}
	if (state == EState::Check) {
		m_Ui->SetMessageLabel(m_Game->GetTurn() == EColor::Black ? "Black's turn - CHECK" : "White's turn - CHECK");
		m_Ui->UpdateBoard(ConvertToBoardRepresentation());
		return;
	}
	if (state == EState::BlackWon) {
		m_Ui->SetMessageLabel("");
		m_Ui->ShowMessageBox("Black won!");
		m_Ui->UpdateBoard(ConvertToBoardRepresentation());
		return;
	}
	if (state == EState::WhiteWon) {
		m_Ui->SetMessageLabel("");
		m_Ui->ShowMessageBox("White won!");
		m_Ui->UpdateBoard(ConvertToBoardRepresentation());
		return;
	}
	if (state == EState::Draw) {
		m_Ui->SetMessageLabel("");
		m_Ui->ShowMessageBox("Draw!");
		m_Ui->UpdateBoard(ConvertToBoardRepresentation());
		return;
	}
	if (state == EState::ChoosePiece) {
		m_Ui->ShowPromoteOptions();
		return;
	}
}

void ChessLink::Start()
{
	m_Ui->SetMessageLabel(m_Game->GetTurn() == EColor::Black ? "Black's turn" : "White's turn");
	m_Ui->UpdateBoard(ConvertToBoardRepresentation());
}

BoardRepresentation ChessLink::ConvertToBoardRepresentation()
{
	std::array<std::array<PieceInfo, 8>, 8> result;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			auto tmp = m_Game->GetPieceInfo({ i,j });
			if (tmp == nullptr) {
				result[i][j] = { PieceType::none, PieceColor::none };
			}
			else {
				PieceType pieceType;
				PieceColor pieceColor;
				
				pieceColor = tmp->GetColor() == EColor::Black ? PieceColor::black : PieceColor::white;
				pieceType = ConvertToType(tmp->GetType());

				result[i][j] = { pieceType, pieceColor };
			}
		}
	}
	return result;
}

PieceType ChessLink::ConvertToType(EPieceType type)
{
	switch (type)
	{
	case EPieceType::Rook:
		return PieceType::rook;
		break;
	case EPieceType::Knight:
		return PieceType::knight;
		break;
	case EPieceType::Bishop:
		return PieceType::bishop;
		break;
	case EPieceType::Queen:
		return PieceType::queen;
		break;
	case EPieceType::King:
		return PieceType::king;
		break;
	case EPieceType::Pawn:
		return PieceType::pawn;
		break;
	default:
		break;
	}
}

std::string ChessLink::PieceTypeToString(PieceType type)
{
	switch (type)
	{
	case PieceType::rook:
		return "Rook";
	case PieceType::knight:
		return "Knight";
	case PieceType::bishop:
		return "Bishop";
	case PieceType::queen:
		return "Queen";
	case PieceType::king:
		return "King";
	case PieceType::pawn:
		return "Pawn";
	default:
		return "Unknown"; // Return "Unknown" or an empty string for invalid PieceType.
	}
}





