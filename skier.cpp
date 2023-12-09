////////////////////////////////////////////////////////////////////////////
//                          IMS project
//                            skier.cpp
//    Lukas Vecerka (xvecer30), Veronika Nevarilova (xnevar00)
//                            12/2023
//

#include "skier.hpp"

Stat slope1Stat("Slope 1 Statistics");
Stat slope2Stat("Slope 2 Statistics");
Stat slope3Stat("Slope 3 Statistics");
Stat slope4Stat("Slope 4 Statistics");
Stat slope5Stat("Slope 5 Statistics");
Stat slope6Stat("Slope 6 Statistics");
Stat slope7Stat("Slope 7 Statistics");
Stat slope8Stat("Slope 8 Statistics");
Stat slope9Stat("Slope 9 Statistics");
Stat slope10Stat("Slope 10 Statistics");
Stat slope11Stat("Slope 11 Statistics");
Stat slope12Stat("Slope 12 Statistics");
Stat slopeRideTime("Slope ride time statistics");
Stat liftRideTime("Lift ride time statistics");
Stat slopeRideDuration("Slope ride duration statistics");
Stat liftRideDuration("Lift ride duration statistics");
Stat revenue("Revenue");

void Hunger::Behavior()
{
    double willEat = Random();
    if (willEat <= 0.5)
    {
        ptr->hunger = true;
    } else
    {
        ptr->hunger = false;
    }
}

void Leaving::Behavior()
{
    ptr->leaving = true;
}
void Skier::Behavior()
{
    arrival = Time;
    lift_ride_dur = 0;
    slope_ride_dur = 0;
    skier_hunger = new Hunger(this);
    skier_leaving = new Leaving(this);

    SetSkierLevel();
    CalculateIntersectionsProbs(); 

    // choose entrypoint
    double lift_choice = Random();

    if (lift_choice < PST_USLONA) {
        currentIntersection = Intersections::getInstance().getIntersectionById(5);
        entry_point_id = 5;
    } else {
        currentIntersection = Intersections::getInstance().getIntersectionById(1);
        entry_point_id = 1;
    }

    double age_choice = Random();
    int ticket_price = age_choice < PST_CHILDREN ? PRICE_CHILDREN : PRICE_ADULT;
    revenue(ticket_price);
    // start skiing
    while(!leaving_complete){

        if (hunger)
        {
            if (skier_hunger != nullptr)
            {
                delete skier_hunger;
                skier_hunger = nullptr;
            }
            // get all the restaurants at current intersection
            std::vector<Store *> restaurants = currentIntersection.restaurants;
            if (restaurants.size() != 0)
            {
                // remove full restaurants
                restaurants.erase(std::remove_if(restaurants.begin(), restaurants.end(),
                [](const Store* store) { return store->Full(); }), restaurants.end());

                if (restaurants.size() != 0)
                {
                    // choose random free restaurant
                    int rand = Random() * restaurants.size();
                    Store *restaurant = restaurants[rand];
                    restaurant->Enter(this, 1);
                    double waiting_time = Normal(90*60, 15*60);

                    Wait(Normal(90*60, 15*60));
                    restaurant->Leave(1);
                    hunger = false;
                }
            }
        }
        makeDecision();
        Move();
        if (leaving && currentIntersection.intersectionId == entry_point_id)
        {
            leaving_complete = true;
        }
    }
    if (skier_hunger != nullptr)
    {
        delete skier_hunger;
        skier_hunger = nullptr;
    }
    liftRideDuration(lift_ride_dur);
    slopeRideDuration(slope_ride_dur);
    skiers(Time-arrival);
}

void Skier::SetSlopeWeights(double slope_difficulty, double slope_possible_lifts, double slope_possible_ways, double slope_special_entertainment, double max_possible_ways_from_lift)
{
    skier_weights.slope_difficulty = slope_difficulty;
    skier_weights.slope_possible_lifts = slope_possible_lifts;
    skier_weights.slope_possible_ways = slope_possible_ways;
    skier_weights.slope_special_entertainment = slope_special_entertainment;
    skier_weights.slope_max_possible_ways_from_lift = max_possible_ways_from_lift;
}

void Skier::SetSkierLevel()
{
    double skier_level = Random();
    if (skier_level < LEVEL_BEGINNER)
    {
        skier_speed_coefficient = 0.67;
        SetSlopeWeights(0.5, 0.1, 0.2, 0.0, 0.2);

    } else if (skier_level < LEVEL_BEGINNER + LEVEL_INTERMEDIATE)
    {
        skier_speed_coefficient = 1.0;
        SetSlopeWeights(0.2, 0.1, 0.2, 0.05, 0.45);

    } else {    //level advanced
        skier_speed_coefficient = 1.4;
        SetSlopeWeights(0.3, 0.1, 0.1, 0.15, 0.35);
    }
}

void Skier::computeIntersectionProbabilities(std::vector<Lift> lifts, std::vector<Slope> slopes, std::vector<std::pair<int, double>> *cumulativeDist){
    double sum = 0;
    std::map<int, double> prob_lifts;
    std::map<int, double> prob_slopes;
    for (const Lift& lift : lifts) {
        prob_lifts[lift.liftId] = 0.7 + lift.comfort * skier_weights.lift_comfort + lift.possible_ways * skier_weights.lift_possible_ways/3 + lift.lifts * skier_weights.lift_lift_count;
        sum += prob_lifts[lift.liftId];
    }

    for (const Slope& slope : slopes) {
        prob_slopes[slope.slopeId] = slope.difficulty * skier_weights.slope_difficulty 
                                    + slope.possible_lifts * skier_weights.slope_possible_lifts 
                                    + slope.possible_ways * skier_weights.slope_possible_ways 
                                    + slope.special_entertainment * skier_weights.slope_special_entertainment 
                                    + slope.max_possible_ways_from_lift * skier_weights.slope_max_possible_ways_from_lift;
        sum += prob_slopes[slope.slopeId];
    }

    double cumulative = 0.0;
    double prob;
    for (const Lift& lift : lifts) {
        prob = prob_lifts[lift.liftId] / sum;
        cumulative += prob;
        cumulativeDist->push_back(std::make_pair(lift.liftId, cumulative));
    }

    for (const Slope& slope : slopes) {
        prob = prob_slopes[slope.slopeId] / sum;
        cumulative += prob;
        cumulativeDist->push_back(std::make_pair(slope.slopeId, cumulative));
    }
}

IntersectionProbs Skier::FilterOptions(IntersectionProbs probs)
{
    int leavingPointId = this->entry_point_id;
    double subtract_sum = 0.0;
    double sum_of_probs = 0.0;
    double prev_second = 0.0;
    IntersectionProbs filtered_probs;

    for (const auto& prob: probs.probs)
    {
        int slopeId = prob.first;
        if (!currentIntersection.WayLeadsToLeavingPoint(slopeId, leavingPointId))
        {
            subtract_sum += prob.second - prev_second;
        } else {
            filtered_probs.probs.push_back(std::make_pair(slopeId, prob.second - subtract_sum));
            sum_of_probs += prob.second - subtract_sum;
        }
        prev_second = prob.second;
    }

    // if there are no choices leading to leaving point, nothing else to do here
    if (filtered_probs.probs.size() == 0)
    {
        return filtered_probs;
    }
    // normalizing the distribution
    double k = 1.0 / filtered_probs.probs.back().second;
    for (auto& prob : filtered_probs.probs) {
        prob.second *= k;
    }

    return filtered_probs;
}

void Skier::makeDecision(){
    IntersectionProbs probs = intersectionsProbs[currentIntersection.intersectionId];

    if (leaving)
    {
        probs = FilterOptions(probs);
        if (probs.probs.size() == 0)
        {
            probs = intersectionsProbs[currentIntersection.intersectionId];
        }
    }

    double rand = Random();

    for (const auto& prob: probs.probs)
    {
        if (rand <= prob.second)
        {
            currentChoice = prob.first;
            return;
        }
    }
}

void Skier::CalculateIntersectionsProbs()
{
    std::map<int, Intersection> intersections = Intersections::getInstance().getIntersections();
    for (const auto& intersection : intersections) {
        double cumulative = 0.0;
        std::vector<std::pair<int, double>> cumulativeDist;

        computeIntersectionProbabilities(intersection.second.lifts, intersection.second.slopes, &cumulativeDist);

        intersectionsProbs[intersection.first] = {cumulativeDist};
    }
}

void Skier::Move()
{
    switch(currentChoice)
    {
        case 1:
            slope1Stat(1);
            RideSlope(1);
            currentIntersection = Intersections::getInstance().getIntersectionById(1);
            break;
        case 2:
            slope2Stat(1);
            RideSlope(2);
            currentIntersection = Intersections::getInstance().getIntersectionById(4);
            break;
        case 3:
            slope3Stat(1);
            RideSlope(3);
            currentIntersection = Intersections::getInstance().getIntersectionById(1);
            break;
        case 4:
            slope4Stat(1);
            RideSlope(4);
            currentIntersection = Intersections::getInstance().getIntersectionById(2);
            break;
        case 5:
            slope5Stat(1);
            RideSlope(5);
            currentIntersection = Intersections::getInstance().getIntersectionById(6);
            break;
        case 6:
            slope6Stat(1);
            RideSlope(6);
            currentIntersection = Intersections::getInstance().getIntersectionById(4);
            break;
        case 7:
            slope7Stat(1);
            RideSlope(7);
            currentIntersection = Intersections::getInstance().getIntersectionById(5);
            break;
        case 8:
            slope8Stat(1);
            RideSlope(8);
            currentIntersection = Intersections::getInstance().getIntersectionById(7);
            break;
        case 9:
            slope9Stat(1);
            RideSlope(9);
            currentIntersection = Intersections::getInstance().getIntersectionById(8);
            break;
        case 10:
            slope10Stat(1);
            RideSlope(10);
            currentIntersection = Intersections::getInstance().getIntersectionById(5);
            break;
        case 11:
            slope11Stat(1);
            RideSlope(11);
            currentIntersection = Intersections::getInstance().getIntersectionById(8);
            break;
        case 12:
            slope12Stat(1);
            RideSlope(12);
            currentIntersection = Intersections::getInstance().getIntersectionById(8);
            break;
        case 'A':
            liftA_queue_hist(Time);
            RideLift(&liftA_queue);
            currentIntersection = Intersections::getInstance().getIntersectionById(6);
            break;
        case 'B':
            liftB_queue_hist(Time);
            RideLift(&liftB_queue);
            currentIntersection = Intersections::getInstance().getIntersectionById(2);
            break;
        case 'C':
            RideLift(&liftC_queue);
            currentIntersection = Intersections::getInstance().getIntersectionById(9);
            break;
        case 'D':
            RideLift(&liftD_queue);
            currentIntersection = Intersections::getInstance().getIntersectionById(4);
            break;
        case 'E':
            RideLift(&liftE_queue);
            currentIntersection = Intersections::getInstance().getIntersectionById(3);
            break;
        default:
            break;
    }
}

void Skier::RideSlope(int slopeId)
{
    double slope_start = Time;
    int time = currentIntersection.GetTimeToCrossById(slopeId);
    Wait(round(time/skier_speed_coefficient));
    slope_ride_dur += Time - slope_start;
    slopeRideTime(Time - slope_start);
}

void Skier::RideLift(Queue *queue)
{
    double lift_start = Time;
    queue->Insert(this);
    Passivate();
    lift_ride_dur += Time - lift_start;
    liftRideTime(Time - lift_start);
}