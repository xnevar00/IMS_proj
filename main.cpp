////////////////////////////////////////////////////////////////////////////
//                          IMS project
//    Lukas Vecerka (xvecer30), Veronika Nevarilova (xnevar00)
//                            12/2023
//

#include "skier.hpp"
#include "intersections.hpp"

class LyzarGenerator : public Event {
  void Behavior() {
    (new Skier)->Activate();
    Activate(Time+1);
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

int main() {
  Print(" model2 - SIMLIB/C++ example\n");
  SetOutput("model2.out");
  
  Init(0,2000);

  Intersections& intersections = Intersections::getInstance();
  intersections.initIntersections();

  (new LyzarGenerator)->Activate();
  (new ChairLiftsGenerator)->Activate();
  (new TBarsGenerator)->Activate();
  (new TBarsGenerator2)->Activate();

  Run(); 

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