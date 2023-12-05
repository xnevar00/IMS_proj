////////////////////////////////////////////////////////////////////////////
//                          IMS project
//                            main.cpp
//    Lukas Vecerka (xvecer30), Veronika Nevarilova (xnevar00)
//                            12/2023
//

#include "skier.hpp"
#include <random>


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

    Print((std::to_string(event_times[0]) + "\n").c_str());
    Print((std::to_string(event_times[1]) + "\n").c_str());
    Print((std::to_string(event_times[2]) + "\n").c_str());
    Print((std::to_string(event_times[3]) + "\n").c_str());
    Print((std::to_string(event_times[4]) + "\n").c_str());

  }

  void Behavior() {
    static int index = 0;
    (new Skier)->Activate();
    Print("vytvarim lyzare cislo %d\n", index);
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
    Activate(Time+15);
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



int main() {
  Print(" model2 - SIMLIB/C++ example\n");
  SetOutput("model2.out");
  
  Init(0,450*60);

  Intersections& intersections = Intersections::getInstance();
  intersections.initIntersections();
  SkierGenerator *skierGen = new SkierGenerator();
  skierGen->generateEventTimes(5000, 9000, 3000);

  skierGen->Activate();
  (new ChairLiftsGenerator)->Activate();
  (new TBarsGenerator)->Activate();
  (new TBarsGenerator2)->Activate();

  Run(); 

  Marcelka.Output();
  Hribek.Output();
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
  liftF.Output();
  table.Output();
  SIMLIB_statistics.Output();
  return 0;
}