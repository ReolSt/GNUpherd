#ifndef SHEPHERD_HPP
#define SHEPHERD_HPP
#include <iostream>
#include <deque>
#include <string>
#include "window.hpp"
#include "file_manager.hpp"

#define SHEPHERD_FM_MODE 0
#define SHEPHERD_W_MODE 1
class Shepherd {
public:
  Shepherd():
    _cur_win(0),_cx(0),_cy(0),_mode(0) {
      fm.list_directory();
      create_win();
  }
  ~Shepherd() {
    for(auto i=_win_list.begin();i!=_win_list.end();i++) {
      delete *i;
    }
  }
  bool change_win(std::uint32_t win);
  inline void create_win() {
    _win_list.push_back(new Window());
    _cur_win=_win_list.size()-1;
  }
  void create_win(const std::string &file_name);
  void delete_curwin();
  inline void set_window(const std::string &str) {
      _win_list[_cur_win]->change_buf(str);
  }
  inline void write_cur_window() {
    if(!fm.write_file
       (_win_list[_cur_win]->full_file_name(),
        _win_list[_cur_win]->buf())) {
      std::cerr << "write_cur_buf() error\n";
    }
  }
  void change_mode(std::uint32_t m);
  void handle_key(const int ch);
  inline std::uint32_t win() {
      return _cur_win;
  }
  inline std::uint32_t number_of_win() {return _win_list.size();}
  inline const std::string& buf() {
      switch(_mode) {
      case SHEPHERD_FM_MODE:
          fm.list_directory();
          return fm.command_output();
      default:
          return _win_list[_cur_win]->buf();
      }
  }
  inline std::uint32_t mode() {return _mode;}
  inline const std::string &file_path() {
      if(_mode==SHEPHERD_FM_MODE) {
          return fm.path();
      }
      else {
          return _win_list[_cur_win]->full_file_name();
      }
  }
  inline void change_file_path(const std::string& fpath) {
      if(_mode==SHEPHERD_FM_MODE) {
          fm.change_directory_full(fpath);
      }
      else {
          _win_list[_cur_win]->set_full_file_name(fpath);
      }
  }
  FileManager fm;
protected:
  std::deque<Window*> _win_list;
  std::int32_t _cur_win,_cx,_cy;
  std::uint32_t _mode;
private:
};
#endif
