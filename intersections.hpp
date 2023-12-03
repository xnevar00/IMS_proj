#include <string>
#include <cstring>
#include <vector>
#include <map>

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
};


class Intersection {

public:
    int intersectionId;
    std::vector<Lift> lifts;
    std::vector<Slope> slopes;

    void addLift(const Lift& lift);

    void addSlope(const Slope& slope);
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