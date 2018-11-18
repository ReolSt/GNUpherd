#include "window.hpp"

bool Window::
move_cursor(std::uint32_t dx,std::uint32_t dy) {
  if(_cy+dy<_buf.size()&&_cx+dx<_buf[_cy].size()) {
    _cx+=dx;
    _cy+=dy;
    return true;
  }
  else {return false;}
}

bool Window::
move_cursor_to(std::uint32_t x,std::uint32_t y) {
  if(_cy<_buf.size()&&_cx<_buf[_cy].size()) {
    _cx=x;
    _cy=y;
    return true;
  }
  else {return false;}
}

bool Window::
write_to_cursor(const char ch) {
  if(ch=='\n') {
    if(_cx==0) {
      _buf.insert(_buf.begin()+_cy,"");
    }
    else if(_cx==_buf[_cy].size()-1) {
      _buf.insert(_buf.begin()+_cy+1,"");
    }
    else {
      std::string newline = _buf[_cy].substr(_cx);
      _buf.insert(_buf.begin()+_cy+1,newline);
      _buf[_cy] = _buf[_cy].substr(0,_cx);
    }
    return true;
  }
  _buf[_cy].insert(_buf[_cy].begin()+_cx,ch);
  return true;
}
