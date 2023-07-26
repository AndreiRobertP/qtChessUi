#include "ChessLink.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	auto game = IGame::Produce();
	auto ui = IChessUi::Produce();

	ChessLink chessLink(game.get(), ui.get());

	chessLink.Start();

	return a.exec();
}
