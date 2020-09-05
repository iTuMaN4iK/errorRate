#include "errorRate.hpp"
#include <iostream>
#include <algorithm>

void printGreeting() {
  std::cout << "************************************************************************************" << std::endl;
  std::cout << "*                           Available commands:                                    *" << std::endl;
  std::cout << "* Set [time] [frame] [lost frames] - Add data on the current number of transmitted *\n"
               "* and lost frames with an indication current time in seconds.                      *"
            << std::endl;
  std::cout << "* Get [duration]- Request the current error rate for the current time in seconds with an     *\n"
               "* indication the duration of the time window in seconds.                           *"
            << std::endl;
  std::cout << "************************************************************************************" << std::endl;
  std::cout << "Run:" << std::endl;
}

int main() {
  printGreeting();
  ErrorRate er;
  std::string command{};
  std::cin >> command;
  while (command.compare("exit")) {
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);
    if (command.compare("set") == 0) {
      Frames f;
      uint64_t time{};
      std::cin >> time >> f;
      er.setCurrent(time, f);
    } else if (command.compare("get") == 0) {
      uint64_t duration{};
      std::cin >> duration;
      std::cout << er.getErrorRate(duration) << std::endl;
    } else {
      std::cout << "Error: unknown command" << std::endl;
    }
    std::cin >> command;
  }
  return 0;
}