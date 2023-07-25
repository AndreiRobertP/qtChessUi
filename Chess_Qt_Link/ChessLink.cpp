#include "ChessLink.h"


ChessLink::ChessLink(IGame* game, IChessUi* ui)
	: m_Game(game)
	, m_Ui(ui)
{
	m_Game->AddListener(this);
}

void ChessLink::OnButtonClicked(const std::pair<int, int>& position, bool isFirstClick)
{
	m_LastPosition = position;

	if (m_Game->IsOver()) {
		return;
	}

	if (isFirstClick == false) {
		try {
			m_Game->Move(m_Ui->GetSelected().value(), position);
		}
		catch (std::exception e) {
			m_Ui->ShowMessage(e.what());
			m_Ui->UpdateBoard(ConvertToBoardRepresentation());
		}
	}
	else {
		try {
			m_Ui->Highlight(m_Game->GetMoves(position));
		}
		catch (std::exception e) {
			m_Ui->ShowMessage(e.what());
			m_Ui->UpdateBoard(ConvertToBoardRepresentation());
		}
	}
}

void ChessLink::OnFileOperation(const std::string& path, FileOperation operation)
{
	//TO BE CONTINUED...
}

void ChessLink::OnUiEvent(UiEvent event)
{
	if (event == UiEvent::RestartGame)
	{
		m_Ui->ResetSelected();
		m_Game->RemoveListener(this);
		//m_Game->Restart();
		m_Game->AddListener(this);
		Start();
		return;
	}
	if (event == UiEvent::DrawProposed)
	{
		m_Game->ProposeDraw();
		return;
	}
	if (event == UiEvent::DrawAccepted)
	{
		m_Game->DrawResponse(true);
		return;
	}
	if (event == UiEvent::DrawDenied)
	{
		m_Game->DrawResponse(false);
		return;
	}
	if (event == UiEvent::PauseTimerButtonClicked)
	{
		//TO BE CONTINUED...
	}
}

void ChessLink::OnMoveItemSelected(int item)
{
}

void ChessLink::OnPromoteOption(PieceType pieceType)
{
	m_Game->PromoteTo(PieceTypeToString(pieceType), m_LastPosition);
}

void ChessLink::OnStateChanged(EState state) {
	if (state == EState::Playing) {
		m_Ui->SetMessage(m_Game->GetTurn() == EColor::Black ? "Black's turn" : "White's turn");
		m_Ui->UpdateBoard(ConvertToBoardRepresentation());
		return;
	}
	if (state == EState::Check) {
		m_Ui->SetMessage(m_Game->GetTurn() == EColor::Black ? "Black's turn - CHECK" : "White's turn - CHECK");
		m_Ui->UpdateBoard(ConvertToBoardRepresentation());
		return;
	}
	if (state == EState::BlackWon) {
		m_Ui->SetMessage("");
		m_Ui->ShowMessage("Black won!");
		m_Ui->UpdateBoard(ConvertToBoardRepresentation());
		return;
	}
	if (state == EState::WhiteWon) {
		m_Ui->SetMessage("");
		m_Ui->ShowMessage("White won!");
		m_Ui->UpdateBoard(ConvertToBoardRepresentation());
		return;
	}
	if (state == EState::Draw) {
		m_Ui->SetMessage("");
		m_Ui->ShowMessage("Draw!");
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
	m_Ui->Show();
	m_Ui->SetMessage(m_Game->GetTurn() == EColor::Black ? "Black's turn" : "White's turn");
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
		return "Unknown";
	}
}





