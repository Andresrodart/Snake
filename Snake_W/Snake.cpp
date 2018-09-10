#include <curses.h>
//#include <conio.h>
#include <stdlib.h> 
#include <string.h>
#include <string>
#include <wchar.h>

using namespace std;
bool gameOver;
const int width = 80;
const int height = 20;
int x, y, fruitX, fruitY, score;
int * tailX, * tailY;
int nTail;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirecton dir;
const char * endGame = "Game Over Press R To Restar or X to Exit";
const char * winGame = "Congratulations you are awesome\n Press R To restar or X to Exit";
const wchar_t* line = L"\u2550", *ULcorner = L"\u2554",* pile = L"\u2551",* URcorner = L"\u2557", *LLcorner = L"\u255A",*LRcorner = L"\u255D", *Snake = L"\u25A0";
const wchar_t* Score = L"\u2551 Score:"; 
const wchar_t* Instructions = L"\u2551 Use A, S, D, W to move"; 

void centerMessage(const char * thisMess); //print a message inside a box
void Setup(); 
void Draw();
void Input();
void Logic();

int main()
{
    //Just some code for changinfg font size with windows.h
    /*CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 15;                   // Width of each character in the font
    cfi.dwFontSize.Y = 13;                  // Height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = 400;
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    */
    initscr();//init the curse screen
    cbreak();//cbreak mode, characters typed by the user are immediately available to the program and erase/kill character processing is not performed. 
    noecho();//When typing no get type on the screen
    //keypad(stdscr, TRUE); //If want to use special keys such as arrows
    nodelay(stdscr, TRUE);//When try to recive char program wont freeze 

    tailX = (int *) calloc((width*height), sizeof(int));
    tailY = (int *) calloc((width*height), sizeof(int));

    Setup();

    while (true)
    {
        if (!gameOver)
            Draw();
        Input();
        Logic();
           
        if (nTail == (width*height))
            gameOver = true;
        if (gameOver == true && nTail == (width*height)){
            clear();//Clear the screen
            centerMessage(winGame);
            move(LINES - 1, COLS - 1);//Move cursor to the bottom
        }else if(gameOver == true){
            clear();           
            centerMessage(endGame);
            move(LINES - 1, COLS - 1); 
        }
        napms(140); 
    }
    endwin();
    return 0;
}

void centerMessage(const char * thisMess){

    int boxSize = strlen(thisMess) + 4;

    mvaddwstr((LINES-5)/2, ((COLS-1)-boxSize)/2,ULcorner);
    for (int i = 0; i < boxSize - 1 ; i++)
        addwstr(line);
    addwstr(URcorner);         
    
    printw("\n");
    
    mvaddwstr((LINES - 3)/2, ((COLS-1)-boxSize)/2, pile);
    mvaddwstr((LINES - 3)/2, ((COLS-1)+boxSize)/2, pile);
    
    printw("\n");
    
    mvaddwstr((LINES -1)/2, ((COLS-1) - boxSize)/2, pile);
    mvaddstr((LINES - 1)/2, ((COLS-1) - strlen(thisMess))/2, thisMess);
    mvaddwstr((LINES -1)/2, ((COLS-1) + boxSize)/2, pile);

    printw("\n");
    
    mvaddwstr((LINES + 1)/2, ((COLS-1)-boxSize)/2, pile);
    mvaddwstr((LINES + 1)/2, ((COLS-1)+boxSize)/2, pile);
    
    mvaddwstr((LINES + 3)/2, ((COLS-1)-boxSize)/2, LLcorner);
    for (int i = 0; i < boxSize - 1 ; i++)
        addwstr(line);
    addwstr(LRcorner);
}

void Setup()
{
    
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    memset(tailX, 0, sizeof(tailX)); // for automatically-allocated arrays
    memset(tailY, 0, sizeof(tailY)); // for automatically-allocated arrays
    nTail = 0;
}

void Draw(){

    clear();
    addwstr(ULcorner);
    for (int i = 0; i < width; i++)
         addwstr(line);
    addwstr(URcorner);         
    
    printw("\n");
 
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                addwstr(pile);
            if (i == y && j == x)
                addwstr(Snake);
            else if (i == fruitY && j == fruitX)
                addwstr(L"\u00A4");
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        addwstr(Snake);
                        print = true;
                    }
                    if (i == fruitY && j == fruitX && tailX[k] != j && tailY[k] != i)
                    addwstr(L"\u00A4");
                }

                if (!print)
                    printw(" ");
            }
                 
 
            if (j == width - 1)
                addwstr(pile);
        }
        printw("\n");

    }
    addwstr(LLcorner);
    for (int i = 0; i < width; i++)
        addwstr(line);
    addwstr(LRcorner);


    printw("\n");       

    for (size_t j = 0; j < 2; j++)
    {
        addwstr(ULcorner);
        for (int i = 0; i < (int) (width - 2) /2 ; i++)
            addwstr(line);
        addwstr(URcorner);  
    }

    printw("\n");
    
    for (size_t j = 0; j < 2; j++)
    {
        addwstr(pile);
        for (int i = 0; i < (int) (width - 2)/2 ; i++)
            printw(" ");
        addwstr(pile);
    }
    
    printw("\n");
    
    addwstr(Score);printw("%i", score);
    for (int i = 0; i < (int) ((width - 2)/2 - wcslen(Score) - to_string(score).length()+ 1) ; i++)
        printw(" ");
    addwstr(pile);

    addwstr(Instructions);
    for (int i = 0; i < (int) ((width - 2)/2 - wcslen(Instructions) + 1) ; i++)
        printw(" ");
    addwstr(pile);
    
    printw("\n");
    
    for (size_t j = 0; j < 2; j++)
    {
        addwstr(pile);
        for (int i = 0; i < (int) (width - 2)/2 ; i++)
            printw(" ");
        addwstr(pile);
    }
    
    printw("\n");

    for (size_t j = 0; j < 2; j++)
    {
        addwstr(LLcorner);
        for (int i = 0; i < (int) (width - 2)/2 ; i++)
            addwstr(line);
        addwstr(LRcorner);
    }
}

void Logic(){

    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++){

        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir){
        
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }
    //if (x > width || x < 0 || y > height || y < 0)
    //  gameOver = true;
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;
 
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
 
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

void Input(){
    char x = getch();
    if (x == '\033') { // if the first value is esc
        getch(); // skip the [
        switch(getch()) { // the real value
            case 'A':
                dir = (dir==DOWN)? DOWN:UP;
                break;
            case 'B':
                dir = (dir==UP)? UP:DOWN;
                break;
            case 'C':
                dir = (dir==LEFT)? LEFT:RIGHT;
                break;
            case 'D':
                dir = (dir==RIGHT)? RIGHT:LEFT;
                break;
        }
    }else{
        switch (x)
        {
            case 'a':
                dir = (dir==RIGHT)? RIGHT:LEFT;
                break;
            case 'd':
                dir = (dir==LEFT)? LEFT:RIGHT;
                break;
            case 'w':
                dir = (dir==DOWN)? DOWN:UP;
                break;
            case 's':
                dir = (dir==UP)? UP:DOWN;
                break;
            case 'x':
                if (gameOver == true)
                    exit(0);
                else
                    gameOver = true;
                break;
            case 'r':
                gameOver = false;
                Setup();
                break;
        }
    }
}