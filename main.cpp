////////////////////////////////////////////////////////////////////////////
//                          IMS project
//                            main.cpp
//    Lukas Vecerka (xvecer30), Veronika Nevarilova (xnevar00)
//                            12/2023
//

#include "skier.hpp"

class LyzarGenerator : public Event {
  void Behavior() {
    (new Skier)->Activate();
    Activate(Time+15);
  }
};

class ChairLiftsGenerator : public Event {
  void Behavior() {
    (new BoardingLiftA)->Activate();
    (new BoardingLiftB)->Activate();
    Activate(Time+120);
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

  (new LyzarGenerator)->Activate();
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