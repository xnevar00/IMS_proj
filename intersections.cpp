#include "intersections.hpp"

void Intersection::addLift(const Lift& lift) {
        lifts.push_back(lift);
}

void Intersection::addSlope(const Slope& slope) {
        slopes.push_back(slope);
}

Intersections& Intersections::getInstance() {
        static Intersections instance;
        return instance;
}

void Intersections::addIntersection(const Intersection& intersection) {
        intersections.push_back(intersection);
}

void Intersections::initIntersections() {
        Intersection newIntersect(1);

        newIntersect.addLift({'B', LiftType::CHAIRLIFT, 8, 1, 0, 0.0});
        newIntersect.addLift({'D', LiftType::TBAR, 2, 0, 0, 0.0});
        addIntersection(newIntersect);

        newIntersect = Intersection(2);
        newIntersect.addLift({'F', LiftType::POMA, 2, 0, 0, 0.0});
        addIntersection(newIntersect);

        newIntersect = Intersection(3);
        newIntersect.addSlope({1, DIFFICULTY_BLUE, 1, 1, 0});
        newIntersect.addSlope({4, DIFFICULTY_RED, 2, 1, 0});
        addIntersection(newIntersect);

        newIntersect = Intersection(4);
        newIntersect.addLift({'E', LiftType::TBAR, 0, 0, 0, 0.0});
        newIntersect.addSlope({3, DIFFICULTY_RED, 3, 2, 0});
        newIntersect.addSlope({5, DIFFICULTY_BLACK, 4, 2, 0});
        newIntersect.addSlope({7, DIFFICULTY_BLUE, 4, 4, 3});
        addIntersection(newIntersect);

        newIntersect = Intersection(5);
        newIntersect.addSlope({15, DIFFICULTY_RED, 6, 8, 3});
        addIntersection(newIntersect);

        newIntersect = Intersection(6);
        newIntersect.addSlope({6, DIFFICULTY_RED, 2, 1, 0});
        newIntersect.addSlope({9, DIFFICULTY_BLUE, 2, 1, 0});
        addIntersection(newIntersect);

        newIntersect = Intersection(7);
        newIntersect.addSlope({8, DIFFICULTY_BLUE, 4, 2, 0});
        newIntersect.addSlope({10, DIFFICULTY_BLUE, 2, 2, 3});
        addIntersection(newIntersect);

        newIntersect = Intersection(8);
        newIntersect.addSlope({11, DIFFICULTY_RED, 2, 1, 3});
        newIntersect.addSlope({12, DIFFICULTY_BLUE, 2, 1, 3});
        addIntersection(newIntersect);

        newIntersect = Intersection(9);
        newIntersect.addSlope({14, DIFFICULTY_BLUE, 2, 1, 3});
        addIntersection(newIntersect);

        newIntersect = Intersection(10);
        newIntersect.addLift({'A', LiftType::CHAIRLIFT, 4, 0, 0, 0.0});
        newIntersect.addLift({'C', LiftType::TBAR, 1, 0, 0, 0.0});
        addIntersection(newIntersect);

        newIntersect = Intersection(11);
        newIntersect.addSlope({13, DIFFICULTY_BLUE, 2, 1, 3});
        addIntersection(newIntersect);

        newIntersect = Intersection(12);
        newIntersect.addSlope({2, DIFFICULTY_BLUE, 3, 2, 0});
        addIntersection(newIntersect);
}

const std::vector<Intersection>& Intersections::getIntersections() {
        return intersections;
}
