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

#define DIFFICULTY_RED 1.0
#define DIFFICULTY_BLUE 0.7
#define DIFFICULTY_BLACK 0.4

struct Slope {
  int slopeId;
  double difficulty;
  int possible_lifts;
  int possible_ways;
  int special_entertainment;
  int time_to_cross;
  std::vector<int> way_to_leaving_points_ids;
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
  int weather;
  double waiting_time;
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

    bool slopeLeadsToLeavingPoint(int slopeId, int leavingPointId);

};



class Intersections {
private:
    std::map<int, Intersection> intersections;
    Intersections() {}

public:

    static Intersections& getInstance();

    void addIntersection(const Intersection& intersection);

    void initIntersections();

    const std::map<int, Intersection>& getIntersections();

    const Intersection getIntersectionById(int id);

};
#endif