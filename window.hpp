#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <string>
#include <iostream>
#include <sstream>
#include <deque>
class Window {
public:
  inline Window():_cx(0),_cy(0){_buf.push_back("");};
  inline Window(const std::string &full_fname,
         std::stringstream &strstream):
    _cx(0),_cy(0) {
    _full_file_name=full_fname;
    while(!strstream.eof()) {
      _buf.push_back("");
      getline(strstream,_buf.back());
    }
  }
  bool move_cursor(std::uint32_t dx,std::uint32_t dy);
  bool move_cursor_to(std::uint32_t x,std::uint32_t y);
  bool write_to_cursor(const char ch);
  inline std::uint32_t x() {
    return _cx;
  }
  inline std::uint32_t y() {
    return _cy;
  }
  inline const std::string &full_file_name() {return _full_file_name;}
  inline const std::deque<std::string> &buf() {return _buf;}
protected:
  std::deque<std::string> _buf;
  std::string _full_file_name;
  std::uint32_t _cx,_cy;
private:
};
#endif
