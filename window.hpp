#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <string>
#include <iostream>
#include <sstream>
#include <deque>
class Window {
public:
  inline Window():_cx(0),_cy(0){};
  inline Window(const std::string &full_fname,
         std::stringstream &strstream):
    _cx(0),_cy(0) {
    _full_file_name=full_fname;
    std::string tmp;
    while(!strstream.eof()) {
      getline(strstream,tmp);
      _buf.append(tmp);
    }
  }
  inline std::uint32_t x() {return _cx;}
  inline std::uint32_t y() {return _cy;}
  inline const std::string &full_file_name() {return _full_file_name;}
  inline const std::string &buf() {return _buf;}
  inline void change_buf(const std::string str) {_buf=str;}
  inline void set_full_file_name(const std::string fname) {
      _full_file_name=fname;
  }
protected:
  std::string _buf;
  std::string _full_file_name;
  std::int32_t _cx,_cy;
private:
};
#endif
