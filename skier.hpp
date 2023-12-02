#ifndef SKIER_HPP
#define SKIER_HPP

#include <string>
#include <cstring>
#include "lift.hpp"

#define PST_AMALKA 0.05
#define PST_MARCELKA 0.95

class Skier : public Process { 
  double arrival;
  std::string output;
  void Behavior();
  void GoToAmalka();
  void GoToMarcelka();
  void GoToUSlona();
};
#endif