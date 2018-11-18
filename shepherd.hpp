#ifndef SHEPHERD_HPP
#define SHEPHERD_HPP
#include <iostream>
#include <deque>
#include <string>
#include "window.hpp"
#include "file_manager.hpp"
#include "printer.hpp"

#define FILEMANAGER_MODE 0
#define WINDOW_MODE 1
class Shepherd {
public:
  Shepherd():_power(1),_cur_win(-1),_cx(0),_cy(0),_mode(0) {
    create_win("/home/emacs/Git/Projects/texteditor/test");
    create_win("/home/emacs/Git/ConFiles/emacs/custom.el");
  }
  ~Shepherd() {
    for(auto i=_win_list.begin();i!=_win_list.end();i++) {
      delete *i;
    }
  }
  bool change_win(std::uint32_t win);

  inline void create_win() {
    _cur_win++;
    _win_list.insert(_win_list.begin()+_cur_win,
                    new Window());
  }
  void create_win(const std::string &file_name);

  inline void delete_curwin() {
    delete _win_list[_cur_win];
    _win_list.erase(_win_list.begin()+_cur_win);
  }
  void delete_without_curwin();

  inline void save_cur_buf() {
    if(!fm.write_file
       (_win_list[_cur_win]->full_file_name(),
        _win_list[_cur_win]->buf())) {
      std::cerr << "save_cur_buf() error\n";
      exit(1);
    }
  }
  void print();
  void print(const std::string &str);
  bool move_cursor(std::uint32_t dx,std::uint32_t dy);
  bool move_cursor_to(std::uint32_t x,std::uint32_t y);
  void change_mode(std::uint32_t m);
  void handle_key(const int ch);
  inline bool power() {
    return _power;
  }

protected:
  bool _power;
  std::deque<Window*> _win_list;
  std::uint32_t _cur_win,_cx,_cy;
  FileManager fm;
  Printer printer;
  std::uint32_t _mode;
private:
};
#endif
