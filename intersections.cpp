////////////////////////////////////////////////////////////////////////////
//                          IMS project
//                       intersections.cpp
//    Lukas Vecerka (xvecer30), Veronika Nevarilova (xnevar00)
//                            12/2023
//

#include "intersections.hpp"
#include "restaurant.hpp"


void Intersection::addLift(const Lift& lift) {
        lifts.push_back(lift);
}

void Intersection::addSlope(const Slope& slope) {
        slopes.push_back(slope);
}

void Intersection::addRestaurant(const Store* restaurant)
{
        restaurants.push_back(const_cast<Store*>(restaurant));
}

int Intersection::GetTimeToCrossById(int id)
{
    for (const Slope& slope : slopes) {
        if (slope.slopeId == id) {
            return slope.time_to_cross;
        }
    }
    return 0;
}

Intersections& Intersections::getInstance() {
        static Intersections instance;
        return instance;
}

void Intersections::addIntersection(const Intersection& intersection) {
        intersections[intersection.intersectionId] = intersection;
}

void Intersections::initIntersections() {
        Intersection newIntersect = Intersection();

        newIntersect.intersectionId = 1;
        newIntersect.addLift({'B', LiftType::CHAIRLIFT, 8, 1, 0, 0.0});
        newIntersect.addLift({'D', LiftType::TBAR, 2, 0, 0, 0.0});
        newIntersect.addRestaurant(&Marcelka);
        newIntersect.addRestaurant(&Hribek);
        newIntersect.addRestaurant(&Podbelka);
        addIntersection(newIntersect);

        newIntersect = Intersection();
        newIntersect.intersectionId = 2;
        newIntersect.addLift({'F', LiftType::POMA, 2, 0, 0, 0.0});
        addIntersection(newIntersect);

        newIntersect = Intersection();
        newIntersect.intersectionId = 3;
        newIntersect.addSlope({1, DIFFICULTY_BLUE, 1, 1, 0, 13});
        newIntersect.addSlope({4, DIFFICULTY_RED, 2, 1, 0, 13});
        addIntersection(newIntersect);

        newIntersect = Intersection();
        newIntersect.intersectionId = 4;
        newIntersect.addLift({'E', LiftType::TBAR, 0, 0, 0, 0.0});
        newIntersect.addSlope({3, DIFFICULTY_RED, 3, 2, 0, 210});
        newIntersect.addSlope({5, DIFFICULTY_BLACK, 4, 2, 0, 70});
        newIntersect.addSlope({7, DIFFICULTY_BLUE, 4, 4, 3, 140});
        newIntersect.addRestaurant(&Skalka);
        newIntersect.addRestaurant(&Slamenka);
        addIntersection(newIntersect);

        newIntersect = Intersection();
        newIntersect.intersectionId = 5;
        newIntersect.addSlope({15, DIFFICULTY_RED, 6, 8, 3, 80});
        addIntersection(newIntersect);

        newIntersect = Intersection();
        newIntersect.intersectionId = 6;
        newIntersect.addSlope({6, DIFFICULTY_RED, 2, 1, 0, 75});
        newIntersect.addSlope({9, DIFFICULTY_BLUE, 2, 1, 0, 225});
        addIntersection(newIntersect);

        newIntersect = Intersection();
        newIntersect.intersectionId = 7;
        newIntersect.addSlope({8, DIFFICULTY_BLUE, 4, 2, 0, 135});
        newIntersect.addSlope({10, DIFFICULTY_BLUE, 2, 2, 3, 12});
        addIntersection(newIntersect);

        newIntersect = Intersection();
        newIntersect.intersectionId = 8;
        newIntersect.addSlope({11, DIFFICULTY_RED, 2, 1, 3, 75});
        newIntersect.addSlope({12, DIFFICULTY_BLUE, 2, 1, 3, 85});
        addIntersection(newIntersect);

        newIntersect = Intersection();
        newIntersect.intersectionId = 9;
        newIntersect.addSlope({14, DIFFICULTY_BLUE, 2, 1, 3, 80});
        addIntersection(newIntersect);

        newIntersect = Intersection();
        newIntersect.intersectionId = 10;
        newIntersect.addLift({'A', LiftType::CHAIRLIFT, 4, 0, 0, 0.0});
        newIntersect.addLift({'C', LiftType::TBAR, 1, 0, 0, 0.0});
        newIntersect.addRestaurant(&Terezka);
        newIntersect.addRestaurant(&USlona);
        newIntersect.addRestaurant(&KulatePeklo);
        addIntersection(newIntersect);

        newIntersect = Intersection();
        newIntersect.intersectionId = 11;
        newIntersect.addSlope({13, DIFFICULTY_BLUE, 2, 1, 3, 7});
        addIntersection(newIntersect);

        newIntersect = Intersection();
        newIntersect.intersectionId = 12;
        newIntersect.addSlope({2, DIFFICULTY_BLUE, 3, 2, 0, 13});
        addIntersection(newIntersect);
}

const std::map<int, Intersection>& Intersections::getIntersections() {
        return intersections;
}

const Intersection Intersections::getIntersectionById(int id){
        return intersections[id];
}


