////////////////////////////////////////////////////////////////////////////
//                          IMS project
//                            skier.hpp
//    Lukas Vecerka (xvecer30), Veronika Nevarilova (xnevar00)
//                            12/2023
//

#ifndef SKIER_HPP
#define SKIER_HPP

#include <string>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include "lift.hpp"
#include "intersections.hpp"
#include "restaurant.hpp"

#define PST_MARCELKA 0.7
#define PST_USLONA 0.3

#define PST_ADULT 0.785
#define PST_CHILDREN 0.215

#define LEVEL_BEGINNER 0.15
#define LEVEL_INTERMEDIATE 0.55
#define LEVEL_ADVANCED 0.3

#define PRICE_ADULT 1140
#define PRICE_CHILDREN 745

extern Stat slope1Stat;
extern Stat slope2Stat;
extern Stat slope3Stat;
extern Stat slope4Stat;
extern Stat slope5Stat;
extern Stat slope6Stat;
extern Stat slope7Stat;
extern Stat slope8Stat;
extern Stat slope9Stat;
extern Stat slope10Stat;
extern Stat slope11Stat;
extern Stat slope12Stat;
extern Stat slopeRideTime;
extern Stat liftRideTime;
extern Stat slopeRideDuration;
extern Stat liftRideDuration;
extern Stat revenue;

struct Weights {
  double lift_comfort = 0.15;
  double lift_possible_ways = 0.28;
  double lift_lift_count = 0.07;

  double slope_difficulty = 0.15;
  double slope_possible_lifts = 0.10;
  double slope_possible_ways = 0.20;
  double slope_special_entertainment = 0.05;
  double slope_max_possible_ways_from_lift = 0.5; 
};

struct IntersectionProbs {
    std::vector<std::pair<int, double>> probs;
};

class Skier : public Process { 
public:

  bool hunger = false;
  Event *skier_hunger;
  bool leaving = false;
  Event *skier_leaving;
  double arrival;
  int entry_point_id;
  bool leaving_complete = false;
  std::string output;
  Weights skier_weights;
  Intersection currentIntersection;
  int currentChoice;
  std::map<int, IntersectionProbs> intersectionsProbs;
  double skier_speed_coefficient = 1.0;
  double slope_ride_dur;
  double lift_ride_dur;

  void Behavior();
  IntersectionProbs FilterOptions(IntersectionProbs probs);
  IntersectionProbs UpdateWeightsBasedOnQueues(IntersectionProbs probs);
  void makeDecision();
  void GoToAmalka();
  void GoToMarcelka();
  void GoToUSlona();
  void SetSlopeWeights(double slope_difficulty, double slope_possible_lifts, double slope_possible_ways, double slope_special_entertainment, double max_possible_ways_from_lift);
  void SetSkierLevel();
  void computeIntersectionProbabilities(std::vector<Lift> lifts, std::vector<Slope> slopes, std::vector<std::pair<int, double>> *cumulativeDist);
  void ChooseLiftB();
  void ChooseLiftD();
  void CalculateIntersectionsProbs();
  void Move();
  void RideSlope(int slopeId);
  void RideLift(Queue *queue);
  void RideLiftF();
};

class Hunger : public Event {
  Skier *ptr;
  public:
    Hunger(Skier *p) : ptr(p) {
      Activate(Time+Normal(100*60, 20*60));
    }
    void Behavior();
};

class Leaving : public Event {
  Skier *ptr;
  public:
    Leaving(Skier *p) : ptr(p) {
      int time_to_leave = CLOSING_TIME - 40*60 - round(Exponential(40*60));

      // if the time to leave is less than the current time, leave immediately
      if (time_to_leave < Time || time_to_leave < 0)
      {
        time_to_leave = 1;
      } else
      {
        time_to_leave = time_to_leave - Time;
      }
      Activate(Time + time_to_leave);
    }
    void Behavior();
};

#endif