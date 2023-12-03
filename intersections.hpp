#include <string>
#include <cstring>
#include <vector>
#include "skier.hpp"

class Intersection {

public:
    int intersectionId;
    std::vector<Lift> lifts;
    std::vector<Slope> slopes;

    Intersection(int id) : intersectionId(id) {}

    void addLift(const Lift& lift);

    void addSlope(const Slope& slope);
};



class Intersections {
private:
    std::vector<Intersection> intersections;
    Intersections() {}

public:

    static Intersections& getInstance();

    void addIntersection(const Intersection& intersection);

    void initIntersections();

    const std::vector<Intersection>& getIntersections();
};