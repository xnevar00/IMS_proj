#include "skier.hpp"

void Skier::Behavior()
{
    arrival = Time;

    CalculateIntersectionsProbs(); 

    // choose entrypoint
    double lift_choice = Random();
    if (lift_choice <= PST_AMALKA){
        currentIntersection = Intersections::getInstance().getIntersectionById(2);
    } else if (lift_choice > PST_AMALKA && lift_choice <= PST_AMALKA + PST_USLONA) {
        currentIntersection = Intersections::getInstance().getIntersectionById(10);
    } else {
        currentIntersection = Intersections::getInstance().getIntersectionById(1);
    }

    // start skiing
    int counter = 0;
    while(counter < 5){
        Wait(50);
        makeDecision();
        Move();
        counter++;
    }

    table(Time-arrival);
}

void Skier::computeIntersectionProbabilities(std::vector<Lift> lifts, std::vector<Slope> slopes, std::vector<std::pair<int, double>> *cumulativeDist){
    double sum = 0;
    std::map<int, double> prob_lifts;
    std::map<int, double> prob_slopes;
    for (const Lift& lift : lifts) {
        prob_lifts[lift.liftId] = lift.comfort * skier_weights.lift_comfort + lift.possible_ways * skier_weights.lift_possible_ways + lift.lifts * skier_weights.lift_lift_count + lift.weather * skier_weights.lift_weather + lift.waiting_time * skier_weights.lift_queue;
        sum += prob_lifts[lift.liftId];
    }

    for (const Slope& slope : slopes) {
        prob_slopes[slope.slopeId] = slope.difficulty * skier_weights.slope_difficulty + slope.possible_lifts * skier_weights.slope_possible_lifts + slope.possible_ways * skier_weights.slope_possible_ways + slope.special_entertainment * skier_weights.slope_special_entertainment;
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

void Skier::makeDecision(){
    IntersectionProbs probs = intersectionsProbs[currentIntersection.intersectionId];

    double rand = Random();

    for (const auto& prob: probs.probs)
    {
        if (rand <= prob.second)
        {
            currentChoice = prob.first;
            output = std::to_string(id()) + " Rozhodl jsem se pro ID " + std::to_string(currentChoice) + "\n";
            Print(output.c_str());
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
            RideSlope(10);
            currentIntersection = Intersections::getInstance().getIntersectionById(2);
            break;
        case 2:
            RideSlope(10);
            currentIntersection = Intersections::getInstance().getIntersectionById(3);
            break;
        case 3:
            RideSlope(30);
            currentIntersection = Intersections::getInstance().getIntersectionById(3);
            break;
        case 4:
            RideSlope(10);
            currentIntersection = Intersections::getInstance().getIntersectionById(1);
            break;
        case 5:
            RideSlope(30);
            currentIntersection = Intersections::getInstance().getIntersectionById(6);
            break;
        case 6:
            RideSlope(30);
            currentIntersection = Intersections::getInstance().getIntersectionById(1);
            break;
        case 7:
            RideSlope(10);
            currentIntersection = Intersections::getInstance().getIntersectionById(7);
            break;
        case 8:
            RideSlope(15);
            currentIntersection = Intersections::getInstance().getIntersectionById(6);
            break;
        case 9:
            RideSlope(20);
            currentIntersection = Intersections::getInstance().getIntersectionById(10);
            break;
        case 10:
            RideSlope(10);
            currentIntersection = Intersections::getInstance().getIntersectionById(8);
            break;
        case 11:
            RideSlope(20);
            currentIntersection = Intersections::getInstance().getIntersectionById(9);
            break;
        case 12:
            RideSlope(20);
            currentIntersection = Intersections::getInstance().getIntersectionById(9);
            break;
        case 13:
            RideSlope(10);
            currentIntersection = Intersections::getInstance().getIntersectionById(9);
            break;
        case 14:
            RideSlope(15);
            currentIntersection = Intersections::getInstance().getIntersectionById(10);
            break;
        case 15:
            RideSlope(15);
            currentIntersection = Intersections::getInstance().getIntersectionById(4);
            break;
        case 'A':
            RideLift(&liftA_queue);
            currentIntersection = Intersections::getInstance().getIntersectionById(7);
            break;
        case 'B':
            RideLift(&liftB_queue);
            currentIntersection = Intersections::getInstance().getIntersectionById(4);
            break;
        case 'C':
            RideLift(&liftC_queue);
            currentIntersection = Intersections::getInstance().getIntersectionById(11);
            break;
        case 'D':
            RideLift(&liftD_queue);
            currentIntersection = Intersections::getInstance().getIntersectionById(6);
            break;
        case 'E':
            RideLift(&liftE_queue);
            currentIntersection = Intersections::getInstance().getIntersectionById(5);
            break;
        case 'F':
            RideLiftF();
            currentIntersection = Intersections::getInstance().getIntersectionById(12);
            break;
        default:
            break;
    }
}

void Skier::RideLiftF()
{
    Seize(liftF);
    output = std::to_string(id()) + " Snazim se dostat na Amalku\n";
    Print(output.c_str());
      
    bool fail = true;
    while(fail){
        if (Random() >= 0.2){
          fail = false;
          output = std::to_string(id()) + " Povedlo se mi dostat na Amalku\n";
          Print(output.c_str());
        } else {                          // failed to get on the lift
          output = std::to_string(id()) + " Jsem blb a spadl jsem, zkousim to znovu\n";
          Print(output.c_str());
        }
        Wait(6);
    }
    Release(liftF); 
    Wait(48);
    output = std::to_string(id()) + " Dojel jsem nahoru na Amalce\n";
    Print(output.c_str());
}

void Skier::RideSlope(int time)
{
    Wait(time*skier_speed_coefficient);
    output = std::to_string(id()) + " Sjezd\n";
    Print(output.c_str());
}

void Skier::RideLift(Queue *queue)
{
    queue->Insert(this);
    Passivate();
    output = std::to_string(id()) + " Vyjel jsem!\n";
    Print(output.c_str());

}