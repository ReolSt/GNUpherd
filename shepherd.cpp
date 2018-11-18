#include "shepherd.hpp"
#include <fstream>
#include <ncursesw/ncurses.h>
bool Shepherd::
change_win(std::uint32_t win) {
  if(win>=_win_list.size()) {
    return false;
  }
  _cur_win=win;
  _cx=_win_list[_cur_win]->x();
  _cy=_win_list[_cur_win]->y();
  return true;
}

void Shepherd::
create_win(const std::string &full_file_name) {
  if(!fm.read_file(full_file_name)) {
    return;
  }
  _cur_win++;
  _win_list.insert(_win_list.begin()+_cur_win,
                  new Window(fm.full_file_name(),fm.stream()));
  fm.clear();
}

void Shepherd::
delete_without_curwin() {
  for(auto i=_win_list.begin();i!=_win_list.end();i++) {
    if(i-_win_list.begin()!=_cur_win) {
      delete *i;
    }
  }
  Window *cw=*(_win_list.begin()+_cur_win);
  _win_list.clear();
  _win_list.push_back(cw);
}

void Shepherd::
print() {
  printer.tune();
  switch(_mode) {
  case FILEMANAGER_MODE:
    printer.print(fm.list_directory());
    break;
  case WINDOW_MODE:
    printer.print(_win_list[_cur_win]->buf());
    break;
  }
}

void Shepherd::
print(const std::string &str) {
  printer.print(str);
}

void Shepherd::
change_mode(std::uint32_t m) {
  if(m<2) {
    if(m==WINDOW_MODE&&!_win_list.size()) {
      return;
    }
    _mode=m;
  }
}

bool Shepherd::
move_cursor(std::uint32_t dx,std::uint32_t dy) {
  if(_mode==FILEMANAGER_MODE||
     _win_list[_cur_win]->move_cursor(dx, dy)) {
    _cx+=dx;
    _cy+=dy;
    printer.set_cursor(_cx, _cy);
    return true;
  }
  else {
    return false;
  }
}

bool Shepherd::
move_cursor_to(std::uint32_t x,std::uint32_t y) {
  if(_mode==FILEMANAGER_MODE||
     _win_list[_cur_win]->move_cursor_to(x,y)) {
    _cx=x;
    _cy=y;
    printer.set_cursor(_cx, _cy);
    return true;
  }
  else {
    return false;
  }
}

#define SHEPHERD_KEY_ESC 27
#define CTRL_PRESSED(c) ((c) & 0x1f)
void Shepherd::
handle_key(const int ch) {
  if(_mode==FILEMANAGER_MODE) {
    switch(ch) {
    case KEY_F(12):
    case CTRL_PRESSED('c'):
      _power=0;
      break;
    case KEY_F(1):
      change_mode(WINDOW_MODE);
      break;
    case KEY_UP:
      move_cursor(0, -1);
      break;
    case KEY_DOWN:
      move_cursor(0, 1);
      break;
    case KEY_LEFT:
      move_cursor(-1, 0);
      break;
    case KEY_RIGHT:
      move_cursor(1, 0);
      break;
    }
  }
  else if(_mode==WINDOW_MODE) {
    switch(ch) {
    case KEY_F(12):
    case CTRL_PRESSED('c'):
      _power=0;
      break;
    case KEY_F(1):
      change_mode(FILEMANAGER_MODE);
      break;
    case CTRL_PRESSED('s'):
      save_cur_buf();
      break;
    case CTRL_PRESSED('q'):
      change_win(_cur_win-1);
      break;
    case CTRL_PRESSED('e'):
      change_win(_cur_win+1);
    }
  }
}
