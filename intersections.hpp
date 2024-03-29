////////////////////////////////////////////////////////////////////////////
//                          IMS project
//                       intersections.hpp
//    Lukas Vecerka (xvecer30), Veronika Nevarilova (xnevar00)
//                            12/2023
//

#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include <string>
#include <cstring>
#include <vector>
#include <map>
#include "simlib.h"
#include "restaurant.hpp"

#define DIFFICULTY_RED 1.0
#define DIFFICULTY_BLUE 0.3
#define DIFFICULTY_BLACK 0.2

extern bool is_attraction;

struct Slope {
  int slopeId;
  double difficulty;
  int possible_lifts;
  int possible_ways;
  int special_entertainment;
  int time_to_cross;
  std::vector<int> way_to_leaving_points_ids;
  int max_possible_ways_from_lift;
};

enum LiftType {
  TBAR = 1,
  CHAIRLIFT = 2,
  POMA = 1
};

struct Lift {
  int liftId;
  int comfort;
  int possible_ways;
  int lifts;
  std::vector<int> way_to_leaving_points_ids;
};


class Intersection {

public:
    int intersectionId;
    std::vector<Lift> lifts;
    std::vector<Slope> slopes;
    std::vector<Store *> restaurants;

    void addLift(const Lift& lift);

    void addSlope(const Slope& slope);

    void addRestaurant(const Store* restaurant);

    int GetTimeToCrossById(int id);

    bool WayLeadsToLeavingPoint(int slopeId, int leavingPointId);

};



class Intersections {
private:
    std::map<int, Intersection> intersections;
    Intersections() {}

public:

    static Intersections& getInstance();
    std::map<int, double> queueWeights;

    void addIntersection(const Intersection& intersection);

    void initIntersections();

    const std::map<int, Intersection>& getIntersections();

    const Intersection getIntersectionById(int id);

};
#endif