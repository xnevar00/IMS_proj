////////////////////////////////////////////////////////////////////////////
//                          IMS project
//                            main.cpp
//    Lukas Vecerka (xvecer30), Veronika Nevarilova (xnevar00)
//                            12/2023
//

#include "skier.hpp"
#include <unistd.h>
#include <random>

int people_count = 0;



class SkierGenerator : public Event {
  public:
  std::vector<double> event_times;

  void generateEventTimes(int numEvents, double mean, double stddev) {
    std::vector<double> events;

    double event_value = 0.0;
    for (int i = 0; i < numEvents; i++) {
        event_value = Normal(mean, stddev);
        events.push_back(event_value);
    }

    std::sort(events.begin(), events.end());

    for (int i = 1; i < numEvents; ++i) {
        double time = events[i] - events[i - 1];
        event_times.push_back(time);
    }
  }

  void Behavior() {
    static int index = 0;
    (new Skier)->Activate();
    //Print("vytvarim lyzare cislo %d\n", index);
    if (index < event_times.size())
    {
        Activate(Time+event_times[index++]);
    }
  }
};

class ChairLiftsGenerator : public Event {
  void Behavior() {
    (new BoardingLiftA)->Activate();
    (new BoardingLiftB)->Activate();
    Activate(Time+10);
  }
};

class TBarsGenerator : public Event {
  void Behavior() {
    (new BoardingLiftC)->Activate();
    (new BoardingLiftD)->Activate();
    Activate(Time+6);
  }
};

class TBarsGenerator2 : public Event {
  void Behavior() {
    (new BoardingLiftE)->Activate();
    Activate(Time+8);
  }
};

int ParseArguments(int argc, char* argv[]) {
  int opt;
  bool p_count = false;
    while ((opt = getopt(argc, argv, "p:a:b:s:fh")) != -1) {
        switch (opt) {
            case 'p':
                people_count = atoi(optarg);
                p_count = true;
                break;
            case 'a':
                liftA_capacity = atoi(optarg);
                break;
            case 'b':
                liftB_capacity = atoi(optarg);
                break;
            case 's':
                char *ptr;
                speed = strtod(optarg, &ptr);
                break;
            case 'f':
                is_attraction = true;
                break;
            case 'h':
                Print("Usage: %s -p people_count [-a liftA_capacity] [-b liftB_capacity]\n", argv[0]);
                return 1;
            case '?':
                return 1;
        }
    }
    if (!p_count) {
        Print("You must specify number of people with -p option\n");
        return 1;
    }
    return 0;
}

void printStats(){
  Marcelka.Output();
  Podbelka.Output();
  Skalka.Output();
  Slamenka.Output();
  Terezka.Output();
  USlona.Output();
  KulatePeklo.Output();
  liftA_queue.Output();
  liftB_queue.Output();
  liftC_queue.Output();
  liftD_queue.Output();
  liftE_queue.Output();
  slope1Stat.Output();
  slope2Stat.Output();
  slope3Stat.Output();
  slope4Stat.Output();
  slope5Stat.Output();
  slope6Stat.Output();
  slope7Stat.Output();
  slope8Stat.Output();
  slope9Stat.Output();
  slope10Stat.Output();
  slope11Stat.Output();
  slope12Stat.Output();
  slopeRideTime.Output();
  liftRideTime.Output();
  slopeRideDuration.Output();
  liftRideDuration.Output();
  skiers.Output();
  liftA_queue_hist.Output();
  liftB_queue_hist.Output();
  SIMLIB_statistics.Output();
  long slope_sum = slope1Stat.Number() + slope2Stat.Number() + slope3Stat.Number() + slope4Stat.Number() + slope5Stat.Number() + slope6Stat.Number()
                  + slope7Stat.Number() + slope8Stat.Number() + slope9Stat.Number() + slope10Stat.Number() + slope11Stat.Number() + slope12Stat.Number();

  Print("Slope ride count: %d\n", slope_sum);
  Print("Ski day revenue: %d \n", (long)revenue.Sum());
}


int main(int argc, char* argv[]) {
  int parsing_ok = ParseArguments(argc, argv);
  if (parsing_ok != 0) {
    return parsing_ok;
  }

  Print("Simulation of Ski Resort Dolni Morava - SIMLIB/C++\n");
  SetOutput("ski_resort_model.out");
  
  Init(0,CLOSING_TIME);

  Intersections& intersections = Intersections::getInstance();
  intersections.initIntersections();
  SkierGenerator *skierGen = new SkierGenerator();
  skierGen->generateEventTimes(people_count, 12000, 4000);

  skierGen->Activate();
  (new ChairLiftsGenerator)->Activate();
  (new TBarsGenerator)->Activate();
  (new TBarsGenerator2)->Activate();

  Run(); 

  printStats();
  return 0;
}