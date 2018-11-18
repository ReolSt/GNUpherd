#ifndef PRINTER_HPP
#define PRINTER_HPP
#include <ncursesw/ncurses.h>
#include <string>
#include <deque>
class Printer {
public:
  inline Printer() {
    setlocale(LC_CTYPE,"ko_KR.utf-8");
    initscr();
    start_color();
    nonl();
    raw();
    noecho();
    keypad(stdscr,TRUE);
    curs_set(2);
  }
  inline ~Printer() {
    endwin();
  }
  void print(const std::string &str);
  void print(const std::deque<std::string> &buf);
  void set_cursor(std::uint32_t x,std::uint32_t y);
  void tune();
protected:
private:

};
#endif
