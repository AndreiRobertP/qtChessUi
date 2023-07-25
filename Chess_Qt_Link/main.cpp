#include "ChessLink.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChessLink chessLink;
    IChessUiQtPtr ui = IChessUiQt::Produce();
    chessLink.SetUi(ui);
    ui->show();
    chessLink.Start();
    return a.exec();
}
