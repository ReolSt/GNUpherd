#include "shepherd.hpp"
#include <chrono>
#include <thread>

int
main() {
  Shepherd shepherd;
  while(shepherd.power()) {
    shepherd.print();
    shepherd.handle_key(getch());
  }
}
