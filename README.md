## ► Instalare qt: 
Link: https://www.qt.io/download-qt-installer-oss?hsCtaTracking=99d9dd4f-5681-48d2-b096-470725510d34%7C074ddad0-fdef-4e53-8aa8-5e8a876d6ab4   
### INSTALAM 6.5.1 2019 MSVC x64
Atentie: Daca nu are toata lumea din echipa aceasi versiune instalata nu o sa mearga. Pentru a putea fi folosit qt in Visual Studio trebuie instalat MSVC x64 (deci si lib-ul cu jocul ar trebui sa fie si pe x64).
Cel mai bine in lasam in locatia default.
![Capture](https://github.com/AndreiRobertP/qtChessUi/assets/115709086/1e727946-8363-4af1-bcd9-c7d4b889d180)

## ► Instalare extensie Qt Visual Studio Tools
Din VS > Extensions > Manage Extensions
![capture2](https://github.com/AndreiRobertP/qtChessUi/assets/115709086/244dc76f-abb6-4a7f-b86e-b96b6df52a0a)

## ► Selectam versiune de Qt pentru extensie
Extensions > Qt VS Tools > Qt versions si adaugam path catre Qt (C:\Qt\6.5.1\msvc2019_64).
![capture3](https://github.com/AndreiRobertP/qtChessUi/assets/115709086/bb2d9f9f-7223-44df-a184-8be0ce7b270f)

## Utilizare
Pentru creare proiect nou → Qt Widgets Application 
![Capture4](https://github.com/AndreiRobertP/qtChessUi/assets/115709086/f2b8dee9-ec8a-4f23-aacf-5e283264dce5)

Ar fi bine sa adaugati la gitignore: https://github.com/github/gitignore/blob/main/Qt.gitignore

## Fisiere importante:
ChessUIQt .h/.cpp
GridButton .h/.cpp
Folder res/
main.cpp
Enums.h (poate fi inlocuit)
