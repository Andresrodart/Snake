#include <cstdio>
#include <clocale>
#include <ctime>
#include <cwchar>
 
int main()
{
    // the C locale will be UTF-8 enabled English;
    // decimal dot will be German
    // date and time formatting will be Japanese
    std::setlocale(LC_ALL, "en_US.UTF-8");
    std::setlocale(LC_NUMERIC, "de_DE.UTF-8");
    std::setlocale(LC_TIME, "ja_JP.UTF-8");
 
    wchar_t str[100];
    std::time_t t = std::time(NULL);
    std::wcsftime(str, 100, L"%A %c", std::localtime(&t));
    std::wprintf(L"Number: %.2f\nDate: %Ls\n \u2550", 3.14, str);
}
/*#include <ncursesw/curses.h>
#include <locale.h>
int main(int argc, char *argv[])
{
  setlocale(LC_ALL,"en_US.UTF-8");
  initscr();
  curs_set(0); //remove cursor
  addstr("\u2550"); //Print out the unicode character
  int x, y;
  getmaxyx(stdscr, y, x);
  printw("ioctl: x = %i y = %i", x,y);
  refresh(); //update screen
  getch();  //wait for input
  endwin();
  return 0;
}

#include <ncurses.h>
#include <sys/ioctl.h>
#include <unistd.h> 

int main()
{
    struct winsize size;
    ioctl(STDOUT_FILENO,TIOCGWINSZ,&size);
    int x = size.ws_col, y = size.ws_row;
    int x_, y_;
    initscr();
    cbreak();
    noecho();
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    getmaxyx(stdscr, y_, x_);
    printw("ioctl: x = %i y = %i \nncurse: x = %i y = %i", x,y,x_,y_);
    getch()

}*/