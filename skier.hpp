#ifndef SKIER_HPP
#define SKIER_HPP

#include <string>
#include <cstring>
#include <vector>
#include "lift.hpp"
#include "intersections.hpp"

#define PST_AMALKA 0.05
#define PST_MARCELKA 0.5
#define PST_USLONA 0.45

class Skier : public Process { 
  struct Weights {
    double lift_comfort = 0.2;
    double lift_possible_ways = 0.45;
    double lift_lift_count = 0.15;
    double lift_weather = -0.5;
    double lift_queue = -0.15;

    double slope_difficulty =0.25;
    double slope_possible_lifts = 0.15;
    double slope_possible_ways = 0.45;
    double slope_special_entertainment = 0.15;
  };

  struct IntersectionProbs {
    std::vector<std::pair<int, double>> probs;
  };

  double arrival;
  std::string output;
  Weights skier_weights;
  Intersection currentIntersection;
  int currentChoice;
  std::map<int, IntersectionProbs> intersectionsProbs;
  double skier_speed_coefficient = 1.0;

  void Behavior();
  void makeDecision();
  void GoToAmalka();
  void GoToMarcelka();
  void GoToUSlona();

  void computeIntersectionProbabilities(std::vector<Lift> lifts, std::vector<Slope> slopes, std::vector<std::pair<int, double>> *cumulativeDist);
  void ChooseLiftB();
  void ChooseLiftD();
  void CalculateIntersectionsProbs();
  void Move();
  void RideSlope(int time);
  void RideLift(Queue *queue);
  void RideLiftF();
};
#endif