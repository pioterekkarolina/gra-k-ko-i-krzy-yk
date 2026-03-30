//Karolina Pioterek, nr. indeksu: 197843, EIT, Zadanie domowe Podstawt Programowania 2025/26
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cstdlib>  

using namespace std;
//deklaracje funkcji
int GenerateSVGNoughtsAndCrosses(char board[3][3]);
void PlayWithPC(char board[3][3]);
void RandomMoveX(char board[3][3]);
void RandomAnyMove(char board[3][3]);
bool Blok(char board[3][3], int& row, int& col);

// Generowanie pliku SVG podstawowa wersja
int GenerateSVG() {

    ofstream file("empty.svg");

    file << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n";
    file << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"1000\" height=\"1000\" version=\"1.1\">\n";
    file << "</svg>\n";

    file.close();

    return 1;
}

// funkcje pomocnicze do sprawdzeniia czy linia nachodzi na ko³o lub prostok¹t
bool pointInCircle(int px, int py, int cx, int cy, int r) {
    return (px - cx) * (px - cx) + (py - cy) * (py - cy) <= r * r;
}

bool pointInRect(int px, int py, int x, int y, int width, int height) {
    return px >= x && px <= x + width &&
        py >= y && py <= y + height;
}

// Generowanie pliku SVG rozszerzonego
int GenerateSVGExtension() {

    int cx = 0, cy = 0, r = 0, x = 0, y = 0, width = 0, height = 0, stroke_width = 0, x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    string color_circle{}, color_rect{}, color_line{};

    //KO£O
    cout << "Provide the parameters of the:\n" << "\tcircle:\n" << "\tx: ";
    cin >> cx;
    // sprawdzanie czy parametr nie przekracza rozdzielczosci ekranu
    if (cx > 1000) {
        do {
            cout << "circle parameter x must be less than 1000 enter it again: ";
            cin >> cx;
        } while (cx > 1000);
    }
    cout << "\ty: ";
    cin >> cy;
    // sprawdzanie czy parametr nie przekracza rozdzielczosci ekranu
    if (cy > 1000) {
        do {
            cout << "circle parameter y must be less than 1000 enter it again: ";
            cin >> cy;
        } while (cy > 1000);
    }
    cout << "\tradius: ";
    cin >> r;
    //sprawdzanie czy promien jest wiekszy od zera
    if (r <= 0) {
        do {
            cout << "radius has to be greater then 0\n" << "type radius again: ";
            cin >> r;
        } while (r <= 0);
    }
    cout << "\tcolor: ";
    cin >> color_circle;

    //PROSTOKAT
    cout << "Provide the parameters of the:\n" << "\trectangle:\n" << "\tx: ";
    cin >> x;
    // sprawdzanie czy parametr nie przekracza rozdzielczosci ekranu
    if (x > 1000) {
        do {
            cout << "rectangle parameter x must be less than 1000 enter it again: ";
            cin >> x;
        } while (x > 1000);
    }
    cout << "\ty: ";
    cin >> y;
    // sprawdzanie czy parametr nie przekracza rozdzielczosci ekranu
    if (y > 1000) {
        do {
            cout << "rectangle parameter y must be less than 1000 enter it again: ";
            cin >> y;
        } while (y > 1000);
    }
    cout << "\twidth: ";
    cin >> width;
    cout << "\theight: ";
    cin >> height;
    cout << "\tcolor: ";
    cin >> color_rect;

    //sprawdzaznie czy figury ko³o i prostok¹t na siebie nachdz¹
    bool overlap = (x + width) > (cx - r) && x < (cx + r) && (y + height) >(cy - r) && y < (cy + r);

    while (overlap) {
        cout << "The rectangle overlaps the circle. Enter x and y again.\n";
        cout << "x: ";
        cin >> x;
        cout << "y: ";
        cin >> y;

        overlap = (x + width) > (cx - r) && x < (cx + r) && (y + height) >(cy - r) && y < (cy + r);
    }

    //LINIA
    cout << "Provide the parameters of the:\n" << "\tline:\n" << "\tx1: ";
    cin >> x1;
    // sprawdzanie czy parametr nie przekracza rozdzielczosci ekranu
    if (x1 > 1000) {
        do {
            cout << "line parameter x1 must be less than 1000 enter it again: ";
            cin >> x1;
        } while (x1 > 1000);
    }
    cout << "\ty1: ";
    cin >> y1;
    // sprawdzanie czy parametr nie przekracza rozdzielczosci ekranu
    if (y1 > 1000) {
        do {
            cout << "line parameter y1 must be less than 1000 enter it again: ";
            cin >> y1;
        } while (y1 > 1000);
    }
    cout << "\tx2: ";
    cin >> x2;
    // sprawdzanie czy parametr nie przekracza rozdzielczosci ekranu
    if (x2 > 1000) {
        do {
            cout << "line parameter x2 must be less than 1000 enter it again: ";
            cin >> x2;
        } while (x2 > 1000);
    }
    cout << "\ty2: ";
    cin >> y2;
    // sprawdzanie czy parametr nie przekracza rozdzielczosci ekranu
    if (y2 > 1000) {
        do {
            cout << "line parameter y2 must be less than 1000 enter it again: ";
            cin >> y2;
        } while (y2 > 1000);
    }
    cout << "\tstroke width: ";
    cin >> stroke_width;
    cout << "\tcolor: ";
    cin >> color_line;

    //sprawdzanie czylinia nachodzi na prostok¹t lb ko³o 
    bool overlapLine = pointInCircle(x1, y1, cx, cy, r) || pointInCircle(x2, y2, cx, cy, r) || pointInRect(x1, y1, x, y, width, height) || pointInRect(x2, y2, x, y, width, height);

    while (overlapLine) {
        cout << "The line overlaps another figure, enter again:\n";
        cout << "x1: ";
        cin >> x1;
        cout << "y1: ";
        cin >> y1;
        cout << "x2: ";
        cin >> x2;
        cout << "y2: ";
        cin >> y2;

        overlapLine = pointInCircle(x1, y1, cx, cy, r) || pointInCircle(x2, y2, cx, cy, r) || pointInRect(x1, y1, x, y, width, height) || pointInRect(x2, y2, x, y, width, height);
    }

    ofstream file("empty.svg");

    if (!file) cout << "file does not exsist!";

    file << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n";
    file << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"1000\" height=\"1000\" version=\"1.1\">\n";

    //ko³o
    file << "<circle cx=\"" << cx
        << "\" cy=\"" << cy
        << "\" r=\"" << r
        << "\" fill=\"" << color_circle << "\" />\n";

    //kwadrat
    file << "<rect x=\"" << x
        << "\" y=\"" << y
        << "\" width=\"" << width
        << "\" height=\"" << height
        << "\" fill=\"" << color_rect << "\" />\n";

    //linia
    file << "<line x1=\"" << x1
        << "\" y1=\"" << y1
        << "\" x2=\"" << x2
        << "\" y2=\"" << y2
        << "\" stroke-width=\"" << stroke_width
        << "\" stroke=\"" << color_line << "\" />\n";

    file << "</svg>\n";

    file.close();

    return 1;
}

// linijka z vertikalnymi liniami
void board_1(char board[3][3], int row) {

    int tab[3] = {};

    for (int i = 0; i < 3; ++i) {
        if (i < 2) {
            cout << " " << board[row][i] << " " << char(0xBA);
        }
        else cout << " " << board[row][i];
    }
    cout << "\n";
}

// linijka z horyzonalnymi liniami
void board_2() {

    for (int i = 0; i < 3; ++i) {
        cout << char(0xCD) << char(0xCD) << char(0xCD);
        if (i < 2) cout << char(0xCE);
    }
    cout << "\n";
}

// flunkcja sprawdza kto wygrywa
bool WhoWin(char board[3][3], char mark) {

    // wiersze
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == mark &&
            board[i][1] == mark &&
            board[i][2] == mark)
            return true;
    }

    // kolumny
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == mark &&
            board[1][i] == mark &&
            board[2][i] == mark)
            return true;
    }

    // przek¹tne
    if (board[0][0] == mark &&
        board[1][1] == mark &&
        board[2][2] == mark)
        return true;

    if (board[0][2] == mark &&
        board[1][1] == mark &&
        board[2][0] == mark)
        return true;

    return false;
}

//blokowanie
bool Blok(char board[3][3], int& row, int& col) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';        // symulacja ruchu gracza
                if (WhoWin(board, 'O')) {
                    board[i][j] = ' ';    // cofniêcie
                    row = i;
                    col = j;
                    return true;
                }
                board[i][j] = ' ';        // cofniêcie
            }
        }
    }
    return false;
}

// randomowy ruch 
void RandomMoveX(char board[3][3]) {

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 'X') {
                //szukamy pustego pola obok X
                for (int r = -1; r <= 1; r++) {// r to przesuniecie w wierszu wzdledem i
                    for (int c = -1; c <= 1; c++) {//c przesuniecie w kolumnie wzgledem j
                        int nextRow = i + r;
                        int nextCol = j + c;
                        if (nextRow >= 0 && nextRow < 3 && nextCol >= 0 && nextCol < 3 && board[nextRow][nextCol] == ' ') {
                            board[nextRow][nextCol] = 'X';
                            return; // ruch wykonany
                        }
                    }
                }
            }
        }
    }

    //jeœli nie ma pola obok X mo¿emy wstawiæ w pierwsze wolne

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'X';
                return; // ruch wykonany
            }
        }
    }
    return;
}

// awaryjny losowyruch jak ie ma jeszce znaku na tablicy
void RandomAnyMove(char board[3][3]) {

    int i, j;

    // losujemy dopóki nie znajdziemy pustego pola
    do {
        i = rand() % 3;
        j = rand() % 3;
    } while (board[i][j] != ' '); // powtarzaj a¿ znajdziesz puste

    board[i][j] = 'X'; // postaw X
}

//g³ówna funkcjagry z PC
void PCMove(char board[3][3]) {
    int row, col;

    // blok
    if (Blok(board, row, col)) {
        board[row][col] = 'X';
    }
    RandomMoveX(board);  // stawianie znaku losowo obok w³asnego

}

//gra z PC
void PlayWithPC(char board[3][3]) {

    string coord;//koordynaty
    char mark;
    int czasO = 30, czasX = 30;
    clock_t start;

    for (int i = 0; i < 9; i++) {
        if (i % 2 == 0) {
            mark = 'O';
            //liczenie czasu
            start = clock();

            cout << "specify where you want to place the mark: ";
            cin >> coord;

            //kolumna
            int col;
            if (coord[0] == 'A') {
                col = 0;
            }
            else if (coord[0] == 'B') {
                col = 1;
            }
            else if (coord[0] == 'C') {
                col = 2;
            }
            else {
                cout << "Wrong column!\n";
                i--;
                continue;
            }
            //rz¹d
            int row;
            if (coord[1] == '1') {
                row = 0;
            }
            else if (coord[1] == '2') {
                row = 1;
            }
            else if (coord[1] == '3') {
                row = 2;
            }
            else {
                cout << "Wrong row!\n";
                i--;
                continue;
            }
            // stwianie kó³ka 

            if (board[row][col] == ' ') {
                board[row][col] = mark;
            }
            else {
                cout << "This field is already taken!\n";
                i--;
                continue;
            }

            //cas
            int timePassed = (clock() - start) / CLOCKS_PER_SEC;

            if (mark == 'O') czasO -= timePassed;
            else czasX -= timePassed;

            if (czasO <= 0 || czasX <= 0) {
                cout << "Time is up, player " << mark << " lost!\n";
                return;
            }

            if (WhoWin(board, mark)) {
                cout << "\tPlayer " << mark << " wins!\n";
                return;// return 0 koñczy funkcje kó³ko i krzyzyk i wraca do maina
            }

            //plansza
            cout << "  A " << "  B  " << " C" << endl;
            cout << "1";
            board_1(board, 0);
            cout << " ";
            board_2();
            cout << "2";
            board_1(board, 1);
            cout << " ";
            board_2();
            cout << "3";
            board_1(board, 2);
        }
        else {
            mark = 'X';
            PCMove(board);

        }

        GenerateSVGNoughtsAndCrosses(board);

    }
}

//funkcja do gryw kó³ko i krzyzyk
int NoughtsAndCrosses(char board[3][3]) {

    //liczenie czasu
    int czasO = 30, czasX = 30;
    clock_t start;

    string coord;//koordynaty
    char mark;

    for (int i = 0; i < 9; i++) {
        if (i % 2 == 0) mark = 'O';
        else mark = 'X';

        //liczenie czasu
        start = clock();

        cout << "specify where you want to place the mark: ";
        cin >> coord;

        //kolumna
        int col;
        if (coord[0] == 'A') {
            col = 0;
        }
        else if (coord[0] == 'B') {
            col = 1;
        }
        else if (coord[0] == 'C') {
            col = 2;
        }
        else {
            cout << "Wrong column!\n";
            i--;
            continue;
        }
        //rz¹d
        int row;
        if (coord[1] == '1') {
            row = 0;
        }
        else if (coord[1] == '2') {
            row = 1;
        }
        else if (coord[1] == '3') {
            row = 2;
        }
        else {
            cout << "Wrong row!\n";
            i--;
            continue;
        }
        // stwianie kó³ka 

        if (board[row][col] == ' ') {
            board[row][col] = mark;
        }
        else {
            cout << "This field is already taken!\n";
            i--;
            continue;
        }

        //cas
        int timePassed = (clock() - start) / CLOCKS_PER_SEC;

        if (mark == 'O') czasO -= timePassed;
        else czasX -= timePassed;

        if (czasO <= 0 || czasX <= 0) {
            cout << "Czas minal! Gracz " << mark << " przegral!\n";
            return 0;
        }

        GenerateSVGNoughtsAndCrosses(board);

        if (WhoWin(board, mark)) {
            cout << "\tPlayer " << mark << " wins!";
            return 0;// return 0 koñczy funkcje kó³ko i krzyzyk i wraca do maina
        }


        //plansza
        cout << "  A " << "  B  " << " C" << endl;
        cout << "1";
        board_1(board, 0);
        cout << " ";
        board_2();
        cout << "2";
        board_1(board, 1);
        cout << " ";
        board_2();
        cout << "3";
        board_1(board, 2);

    }


    return 0;
}

// Generowanie pliku SVG dla kó³ka i krzyzyka
int GenerateSVGNoughtsAndCrosses(char board[3][3]) {

    ofstream file("empty.svg");

    if (!file) cout << "file does not exsist!";

    file << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n";
    file << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"1000\" height=\"1000\" version=\"1.1\">\n";

    //wspl srodkapola(kwadracika)
    int cx[3] = { 80, 220, 360 };
    int cy[3] = { 110, 250, 390 };

    // rysowanie znakow
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {

            //kolo
            if (board[i][j] == 'O') {
                file << "<circle cx=\"" << cx[j] << "\" cy=\"" << cy[i] << "\" r=\"40\" fill=\"none\" stroke=\"purple\" stroke-width=\"5\" />\n";
            }
            //iks
            if (board[i][j] == 'X') {
                file << "<line x1=\"" << cx[j] - 30 << "\" y1=\"" << cy[i] - 30 << "\" x2=\"" << cx[j] + 30 << "\" y2=\"" << cy[i] + 30 << "\" stroke=\"purple\" stroke-width=\"5\" />\n";

                file << "<line x1=\"" << cx[j] + 30 << "\" y1=\"" << cy[i] - 30 << "\" x2=\"" << cx[j] - 30 << "\" y2=\"" << cy[i] + 30 << "\" stroke=\"purple\" stroke-width=\"5\" />\n";
            }


        }
    }

    // plansza do gry
    //linia vert od prawej
    file << "<line x1=\"150\" y1=\"100\" x2=\"150\" y2=\"400\" stroke-width=\"5\" stroke=\"purple\" />\n";
    //linia vert od lewej
    file << "<line x1=\"290\" y1=\"100\" x2=\"290\" y2=\"400\" stroke-width=\"5\" stroke=\"purple\" />\n";
    //linia horyz od gory
    file << "<line x1=\"60\" y1=\"180\" x2=\"380\" y2=\"180\" stroke-width=\"5\" stroke=\"purple\" />\n";
    //linia horyz od dolu
    file << "<line x1=\"60\" y1=\"320\" x2=\"380\" y2=\"320\" stroke-width=\"5\" stroke=\"purple\" />\n";


    file << "</svg>\n";

    file.close();

    return 1;
}


int menu() {

    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };
    char key;

    do {
        cout << R"(                    _____                    _____                    _____                    _____          
                   /\    \                  /\    \                  /\    \                  /\    \         
                  /::\____\                /::\    \                /::\____\                /::\____\        
                 /::::|   |               /::::\    \              /::::|   |               /:::/    /        
                /:::::|   |              /::::::\    \            /:::::|   |              /:::/    /         
               /::::::|   |             /:::/\:::\    \          /::::::|   |             /:::/    /          
              /:::/|::|   |            /:::/__\:::\    \        /:::/|::|   |            /:::/    /           
             /:::/ |::|   |           /::::\   \:::\    \      /:::/ |::|   |           /:::/    /            
            /:::/  |::|___|______    /::::::\   \:::\    \    /:::/  |::|   | _____    /:::/    /      _____  
           /:::/   |::::::::\    \  /:::/\:::\   \:::\    \  /:::/   |::|   |/\    \  /:::/____/      /\    \ 
          /:::/    |:::::::::\____\/:::/__\:::\   \:::\____\/:: /    |::|   /::\____\|:::|    /      /::\____\
          \::/    / ~~~~~/:::/    /\:::\   \:::\   \::/    /\::/    /|::|  /:::/    /|:::|____\     /:::/    /
           \/____/      /:::/    /  \:::\   \:::\   \/____/  \/____/ |::| /:::/    /  \:::\    \   /:::/    / 
                       /:::/    /    \:::\   \:::\    \              |::|/:::/    /    \:::\    \ /:::/    /  
                      /:::/    /      \:::\   \:::\____\             |::::::/    /      \:::\    /:::/    /   
                     /:::/    /        \:::\   \::/    /             |:::::/    /        \:::\__/:::/    /    
                    /:::/    /          \:::\   \/____/              |::::/    /          \::::::::/    /     
                   /:::/    /            \:::\    \                  /:::/    /            \::::::/    /      
                  /:::/    /              \:::\____\                /:::/    /              \::::/    /       
                  \::/    /                \::/    /                \::/    /                \::/____/        
                   \/____/                  \/____/                  \/____/                  ~~              
                                                                                                     )" << endl;

        cout << R"(                     ___                        _              _         _ 
                    | _ \_ _ ___ ______  __ _  | |_____ _  _  | |_ ___  (_)
                    |  _/ '_/ -_|_-<_-< / _` | | / / -_) || | |  _/ _ \  _ 
                    |_| |_| \___/__/__/ \__,_| |_\_\___|\_, |  \__\___/ (_)
                                                        |__/               )" << "\n";
        cout << "1 - Generate empty SVG\n" << "2 - Generate extented SVG\n" << "3 - Checkers Game\n" << "4 - Noughts and crosses\n" << "X - Exit\n" << "H - Help\n " << endl;


        cin >> key;

        switch (key)
        {
        case 'H':

            cout << R"(Explaination Noughts and Crosses Game:

            In this stage, the user can play a Noughts and Crosses game.

            The game is played on a 3 / 3 board.

            Two players take turns placing their marks :

            -Player 1 uses O

            -Player 2 uses X

            Player O begins the game.

            To place a mark, the user enters a board coordinate :

            Columns are labeled A, B, C

            Rows are labeled 1, 2, 3

            Example input : A1, B2, C3

            If the selected field is already occupied or the input is invalid, the program asks the user to try again.

            The board is displayed after each move.

            The game ends when the board is full or the time for player ends up, each player has 30s.

            )";


            break;

        case 'X':
            return 0;
            break;

        case '1':
            GenerateSVG();
            break;

        case '2':
            GenerateSVGExtension();
            break;

        case '3':

            break;

        case '4':


            cout << "press P if you want to play with PC, or press F if you want to play with friend: ";
            cin >> key;

            switch (key)
            {
            case 'P':
                PlayWithPC(board);
                break;

            case 'F':
                NoughtsAndCrosses(board);
                break;
            }
            break;
        }
    } while (key != 'X');

    return 0;
}

int main() {

    srand(time(0));//potrzebne do funkcji randomanymove

    // Menu
    menu();

    return 0;
}
