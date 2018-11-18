#include "printer.hpp"

void Printer::
print(const std::string &str) {
  printw(str.c_str());
}

void Printer::
print(const std::deque<std::string> &buf) {
  for(auto i=buf.begin();i!=buf.end();i++) {
    move(i-buf.begin(),0);
    printw(i->c_str());
  }
}

void Printer::
set_cursor(std::uint32_t x, std::uint32_t y) {
  move(y,x);
}

void Printer::
tune() {
  clear();
  refresh();
}
