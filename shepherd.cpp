#include "shepherd.hpp"
#include <fstream>
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
delete_curwin() {
  delete _win_list[_cur_win];
  if(_win_list.size()>1) {
      if(_cur_win==0) {
          _win_list.pop_front();
      }
      else if(_cur_win>0) {
          _win_list.erase(_win_list.begin()+_cur_win);
          _cur_win--;
      }
  }
  else if(_win_list.size()==1){
      _win_list.pop_back();
      create_win();
  }
}

void Shepherd::
create_win(const std::string &full_file_name) {
  if(!fm.read_file(full_file_name)) {
    return;
  }
  _win_list.push_back(new Window(fm.full_file_name(),fm.stream()));
  _cur_win=_win_list.size()-1;
  fm.clear();
}

void Shepherd::
change_mode(std::uint32_t m) {
  if(m<2) {
    if(m==SHEPHERD_W_MODE&&!_win_list.size()) {
      return;
    }
    _mode=m;
  }
}
