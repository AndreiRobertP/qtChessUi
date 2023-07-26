#include "ChessUi.h"


IChessUiQtPtr IChessUi::Produce() {
    return std::make_shared<ChessUi>();
}

ChessUi::ChessUi(QWidget *parent)
    : QMainWindow(parent)
{
    //Widget containing everything
    QWidget* mainWidget = new QWidget();
    QGridLayout* mainGridLayout = new QGridLayout();
    
    InitializeBoard(mainGridLayout);
    InitializeMessage(mainGridLayout);
    InitializeButtons(mainGridLayout);
    InitializeTimers(mainGridLayout);
    InitializeHistory(mainGridLayout);

    mainWidget->setLayout(mainGridLayout);
    this->setCentralWidget(mainWidget);
}

ChessUi::~ChessUi()
{
    //No delete?
    //https://doc.qt.io/qt-6/objecttrees.html
}

void ChessUi::InitializeMessage(QGridLayout * mainGridLayout)
{
    m_MessageLabel = new QLabel();
    m_MessageLabel->setText("Waiting for white player");
    m_MessageLabel->setAlignment(Qt::AlignCenter);
    m_MessageLabel->setStyleSheet("font-size: 20px; font-weight: bold;");

    mainGridLayout->addWidget(m_MessageLabel, 0, 1, 1, 1);
}

void ChessUi::InitializeButtons(QGridLayout* mainGridLayout)
{
    QPushButton* saveButton = new QPushButton("Save");
    QPushButton* loadButton = new QPushButton("Load");
    QPushButton* restartButton = new QPushButton("Restart");
    QPushButton* drawButton = new QPushButton("Draw");
    QPushButton* copyFENButton = new QPushButton("Copy FEN");
    QPushButton* copyPGNButton = new QPushButton("Copy PGN");

    QWidget* buttonContainer = new QWidget();
    QGridLayout* btnGrid = new QGridLayout();

    btnGrid->addWidget(saveButton, 0, 0);
    btnGrid->addWidget(loadButton, 0, 1);
    btnGrid->addWidget(restartButton, 0, 2);
    btnGrid->addWidget(drawButton, 0, 3);
    btnGrid->addWidget(copyFENButton, 1, 0, 1, 2);
    btnGrid->addWidget(copyPGNButton, 1, 2, 1, 2);

    connect(saveButton, &QPushButton::pressed, this, &ChessUi::OnSaveButtonClicked);
    connect(loadButton, &QPushButton::pressed, this, &ChessUi::OnLoadButtonClicked);
    connect(restartButton, &QPushButton::pressed, this, &ChessUi::OnRestartButtonClicked);
    connect(drawButton, &QPushButton::pressed, this, &ChessUi::OnDrawButtonClicked);
    connect(copyFENButton, &QPushButton::pressed, this, &ChessUi::OnCopyFENButtonClicked);
    connect(copyPGNButton, &QPushButton::pressed, this, &ChessUi::OnCopyPGNButtonClicked);

    buttonContainer->setLayout(btnGrid);
    mainGridLayout->addWidget(buttonContainer, 0, 0, 1, 1);
}

void ChessUi::InitializeTimers(QGridLayout* mainGridLayout)
{
    QWidget* timerContainer = new QWidget();
    QGridLayout* timerGrid = new QGridLayout();

    QLabel* blackTimerLbl = new QLabel("Black timer: ");
    m_BlackTimer = new QLabel("00:00:00");

    QPushButton* pauseTimerBtn = new QPushButton(" Pause | Resume");
    connect(pauseTimerBtn, &QPushButton::pressed, this, &ChessUi::OnPauseButtonClicked);

    QLabel* whiteTimerLbl = new QLabel("    White timer: ");
    m_WhiteTimer = new QLabel("00:00:00");

    timerContainer->setFixedWidth(400);

    timerGrid->addWidget(blackTimerLbl, 0, 0);
    timerGrid->addWidget(m_BlackTimer, 0, 1);
    timerGrid->addWidget(pauseTimerBtn, 0, 2);
    timerGrid->addWidget(whiteTimerLbl, 0, 3);
    timerGrid->addWidget(m_WhiteTimer, 0, 4);

    timerContainer->setLayout(timerGrid);
    mainGridLayout->addWidget(timerContainer, 2, 0, 1, 2, Qt::AlignCenter);
}

void ChessUi::InitializeHistory(QGridLayout* mainGridLayout)
{
    m_HistoryList = new QListWidget();
    m_HistoryList->setMinimumWidth(250);
    m_HistoryList->setMaximumWidth(350);
    connect(m_HistoryList, &QListWidget::itemActivated, this, &ChessUi::OnHistoryClicked);
    mainGridLayout->addWidget(m_HistoryList, 1, 0, 1, 1);
}

void ChessUi::InitializeBoard(QGridLayout* mainGridLayout)
{
    QGridLayout* chessGridLayout = new QGridLayout();
    QWidget* board = new QWidget();

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            m_grid[i][j] = new GridButton({ i,j }, PieceType::none, PieceColor::none);
            chessGridLayout->addWidget(m_grid[i][j], i, j, 1, 1);
            connect(m_grid[i][j], &GridButton::Clicked, this, &ChessUi::OnButtonClicked);
        }
    }

    board->setLayout(chessGridLayout);
    mainGridLayout->addWidget(board, 1, 1, 1, 1);
}

void ChessUi::Show()
{
    QMainWindow::show();
}

void ChessUi::OnButtonClicked(const std::pair<int, int>&position)
{
    //At second click
    if (m_selectedCell.has_value()) {
        if (position != m_selectedCell.value()) {
            for (const auto& listener : m_Listeners) {
                listener->OnButtonClicked(position, false);
            }
        }

        //Deselect prev. pressed button
        m_grid[m_selectedCell.value().first][m_selectedCell.value().second]->setSelected(false);
        ResetSelected();
    }
    //At first click
    else {
        m_selectedCell = position;
        m_grid[position.first][position.second]->setSelected(true);

        for (const auto& listener : m_Listeners) {
            listener->OnButtonClicked(position, true);
        }
    }
}

void ChessUi::OnSaveButtonClicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    
    QStringList fileNames;
    if (dialog.exec())
        fileNames = dialog.selectedFiles();
}

void ChessUi::OnLoadButtonClicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);

    QStringList fileNames;
    if (dialog.exec())
        fileNames = dialog.selectedFiles();
}

void ChessUi::OnRestartButtonClicked()
{
    for (const auto& listener : m_Listeners) {
        listener->OnUiEvent(RestartGame);
    }
}

void ChessUi::OnDrawButtonClicked()
{
    for (const auto& listener : m_Listeners) {
        listener->OnUiEvent(DrawProposed);
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Draw proposal", "Do you accept a draw?", QMessageBox::Yes | QMessageBox::No);

    UiEvent option;
    if (reply == QMessageBox::Yes) {
        option = DrawAccepted;
    }
    else {
        option = DrawDenied;
    }

    for (const auto& listener : m_Listeners) {
        listener->OnUiEvent(option);
    }
}

void ChessUi::OnHistoryClicked(QListWidgetItem* item)
{
    int index = m_HistoryList->currentRow();
    
    for (const auto& listener : m_Listeners) {
        listener->OnMoveItemSelected(index);
    }
}

void ChessUi::OnPauseButtonClicked()
{
    for (const auto& listener : m_Listeners) {
        listener->OnUiEvent(PauseTimerButtonClicked);
    }
}

void ChessUi::OnCopyFENButtonClicked()
{
    for (const auto& listener : m_Listeners) {
        listener->OnUiEvent(CopyFEN);
    }
}

void ChessUi::OnCopyPGNButtonClicked()
{
	for (const auto& listener : m_Listeners) {
		listener->OnUiEvent(CopyPGN);
	}
}

void ChessUi::UpdateMoves(const std::vector<std::string>& history)
{
    m_HistoryList->clear();
    int numMoves = 10;
    for (int i = 0; i < history.size(); i++) {
        m_HistoryList->addItem(QString::fromStdString(history[i]));
    }
}

void ChessUi::UpdateBoard(const BoardRepresentation& newBoard)
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            m_grid[i][j]->setPiece(newBoard[i][j]);
            m_grid[i][j]->setSelected(false);
            m_grid[i][j]->setHighlighted(false);
        }
    }
}

void ChessUi::Highlight(const std::vector<std::pair<int, int>>& possibleMoves)
{
    for (const auto& position : possibleMoves) {
        m_grid[position.first][position.second]->setHighlighted(true);
    }
}

void ChessUi::ShowPromoteOptions()
{
    QInputDialog dialog;
    QList<QString> options;
    options.append("Rook");
    options.append("Bishop");
    options.append("Queen");
    options.append("Knight");

    dialog.setComboBoxItems(options);
    dialog.setModal(true);

    bool ok;
    QString item = QInputDialog::getItem(this, tr("Pawn promote"),
        tr("Promote pawn to: "), options, 0, false, &ok);

    if (ok && !item.isEmpty())
    {
        PieceType promoteTo;

        if (item == "Rook")
            promoteTo = PieceType::rook;
        else if (item == "Bishop")
            promoteTo = PieceType::bishop;
        else if (item == "Queen")
            promoteTo = PieceType::queen;
        else if (item == "Knight")
            promoteTo = PieceType::knight;
        else throw std::exception("No such piece");

        for (const auto& listener : m_Listeners) {
            listener->OnPromoteOption(promoteTo);
        }
    }
}

void ChessUi::SetMessage(const std::string& value)
{
    m_MessageLabel->setText(QString::fromStdString(value));
}

void ChessUi::SetClipboard(const std::string& value)
{
	QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(QString::fromStdString(value));
}

void ChessUi::SetTimer(const std::string& value, PieceColor color)
{
    if (color == PieceColor::black) {
        m_BlackTimer->setText(QString::fromStdString(value));
    }
    else {
        m_WhiteTimer->setText(QString::fromStdString(value));
    }
}

void ChessUi::ShowMessage(const std::string& value)
{
    QMessageBox msgBox;
    msgBox.setText(QString::fromStdString(value));
    msgBox.exec();
}

void ChessUi::ResetSelected()
{
    m_selectedCell.reset();

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            m_grid[i][j]->setSelected(false);
            m_grid[i][j]->setHighlighted(false);
        }
    }
}

std::optional<std::pair<int, int>> ChessUi::GetSelected()
{
    return m_selectedCell;
}

void ChessUi::AddListener(IChessUiListener* listener)
{
    m_Listeners.push_back(listener);
}

void ChessUi::RemoveListener(IChessUiListener* listener)
{
    for (auto it = m_Listeners.begin(); it != m_Listeners.end(); ++it)
    {
        if (*it == listener)
        {
            m_Listeners.erase(it);
            break;
        }
    }
}

