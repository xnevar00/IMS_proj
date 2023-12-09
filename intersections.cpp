////////////////////////////////////////////////////////////////////////////
//                          IMS project
//                       intersections.cpp
//    Lukas Vecerka (xvecer30), Veronika Nevarilova (xnevar00)
//                            12/2023
//

#include "intersections.hpp"

bool is_attraction = false;

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

        int attr_num = is_attraction ? 3 : 0;
        Intersection newIntersect = Intersection();

        newIntersect.intersectionId = 1;
        newIntersect.addLift({'B', LiftType::CHAIRLIFT, 8, 1, {1, 5}});
        newIntersect.addLift({'D', LiftType::TBAR, 2, 0, {1, 5}});
        newIntersect.addRestaurant(&Marcelka);
        newIntersect.addRestaurant(&Podbelka);
        addIntersection(newIntersect);


        newIntersect = Intersection();
        newIntersect.intersectionId = 2;
        newIntersect.addLift({'E', LiftType::POMA, 0, 0, {1, 5}});
        newIntersect.addSlope({1, DIFFICULTY_RED, 3, 2, 0, 241+10+10, {1}, 8});
        newIntersect.addSlope({2, DIFFICULTY_BLACK, 4, 2, attr_num, 75+10, {1, 5}, 8});
        newIntersect.addSlope({5, DIFFICULTY_BLUE, 4, 4, 3+attr_num, 155+10, {1, 5}, 8});
        newIntersect.addRestaurant(&Skalka);
        newIntersect.addRestaurant(&Slamenka);
        addIntersection(newIntersect);

        newIntersect = Intersection();
        newIntersect.intersectionId = 3;
        newIntersect.addSlope({4, DIFFICULTY_RED, 6, 8, 3+attr_num, 85+10, {1, 5}, 8});
        addIntersection(newIntersect);

        newIntersect = Intersection();
        newIntersect.intersectionId = 4;
        newIntersect.addSlope({3, DIFFICULTY_RED, 2, 1, attr_num, 80+10, {1}, 8});
        newIntersect.addSlope({7, DIFFICULTY_BLUE, 2, 1, 0, 254+10, {5}, 4});
        addIntersection(newIntersect);

        newIntersect = Intersection();
        newIntersect.intersectionId = 5;
        newIntersect.addLift({'A', LiftType::CHAIRLIFT, 4, 0, {1, 5}});
        newIntersect.addLift({'C', LiftType::TBAR, 1, 0, {5}});
        newIntersect.addRestaurant(&Terezka);
        newIntersect.addRestaurant(&USlona);
        newIntersect.addRestaurant(&KulatePeklo);
        addIntersection(newIntersect);

        newIntersect = Intersection();
        newIntersect.intersectionId = 6;
        newIntersect.addSlope({6, DIFFICULTY_BLUE, 4, 2, attr_num, 150, {1,5}, 8});
        newIntersect.addSlope({8, DIFFICULTY_BLUE, 2, 2, 3, 9, {5}, 4});
        addIntersection(newIntersect);

        newIntersect = Intersection();
        newIntersect.intersectionId = 7;
        newIntersect.addSlope({11, DIFFICULTY_RED, 2, 1, 3, 78, {5}, 4});
        newIntersect.addSlope({9, DIFFICULTY_BLUE, 2, 1, 3, 93, {5}, 4});
        addIntersection(newIntersect);

        newIntersect = Intersection();
        newIntersect.intersectionId = 8;
        newIntersect.addSlope({10, DIFFICULTY_BLUE, 2, 1, 3, 84+10, {5}, 4});
        addIntersection(newIntersect);

        newIntersect = Intersection();
        newIntersect.intersectionId = 9;
        newIntersect.addSlope({12, DIFFICULTY_BLUE, 2, 1, 3, 4+10, {5}, 4});
        addIntersection(newIntersect);
}

const std::map<int, Intersection>& Intersections::getIntersections() {
        return intersections;
}

const Intersection Intersections::getIntersectionById(int id){
        return intersections[id];
}

bool Intersection::WayLeadsToLeavingPoint(int wayId, int leavingPointId)
{
        for (const Slope& slope : slopes) {
                if (slope.slopeId == wayId) {
                        for (int id : slope.way_to_leaving_points_ids) {
                                if (id == leavingPointId) {
                                return true;
                                }
                        }
                }
        }
        for (const Lift& lift : lifts) {
                if (lift.liftId == wayId) {
                        for (int id : lift.way_to_leaving_points_ids) {
                                if (id == leavingPointId) {
                                        return true;
                                }
                        }
                }
        }
        return false;
}


