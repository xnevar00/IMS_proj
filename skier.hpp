#ifndef SKIER_HPP
#define SKIER_HPP

#include <string>
#include <cstring>
#include <vector>
#include "lift.hpp"

#define PST_AMALKA 0.05
#define PST_MARCELKA 0.5
#define PST_USLONA 0.45
#define MAX_SLOPES_AT_INTERSECTION 3
#define MAX_LIFTS_AT_INTERSECTION 2

#define DIFFICULTY_RED 1.0
#define DIFFICULTY_BLUE 0.7
#define DIFFICULTY_BLACK 0.4

struct Slope {
  int slopeId;
  double difficulty;
  int possible_lifts;
  int possible_ways;
  int special_entertainment;
};

struct Weights {
  double comfort;
  double slopes;
  double lifts;
  double weather;
  double waiting_time;
};

enum LiftType {
  TBAR = 1,
  CHAIRLIFT = 2,
  POMA = 1
};

struct Lift {
  char liftId;
  int comfort;
  int slopes;
  int lifts;
  int weather;
  double waiting_time;
};

class Skier : public Process { 
  double arrival;
  std::string output;
  Weights skier_weights;
  int currentIntersection;

  void Behavior();
  void GoToAmalka();
  void GoToMarcelka();
  void GoToUSlona();

  void ChooseLiftB();
  void ChooseLiftD();
};
#endif