#include "shepherd.hpp"
#include <chrono>
#include <thread>

#define MAX_FPS 15
#define MS_PER_FRAME 66

namespace sch = std::chrono;

const sch::milliseconds MPF(MS_PER_FRAME);

int
main() {
  sch::system_clock::time_point start_time,end_time;
  sch::milliseconds elapsed_time;
  Shepherd shepherd;
  while(shepherd.power()) {
    start_time=sch::system_clock::now();
    shepherd.print();
    shepherd.handle_key(getch());
    end_time=sch::system_clock::now();
    elapsed_time=sch::duration_cast<sch::milliseconds>(end_time-start_time);
    if(MPF.count()>elapsed_time.count()) {
      std::this_thread::sleep_for(MPF-elapsed_time);
    }
  }
}
