////////////////////////////////////////////////////////////////////////////
//                          IMS project
//    Lukas Vecerka (xvecer30), Veronika Nevarilova (xnevar00)
//                            12/2023
//

#include "skier.hpp"

class LyzarGenerator : public Event {
  void Behavior() {
    (new Skier)->Activate();
    Activate(Time+1);
  }
};

class NastupGenerator : public Event {
  void Behavior() {
    (new NastupMarcelka)->Activate();
    (new NastupUSlona)->Activate();
    Activate(Time+10);
  }
};

int main() {
  Print(" model2 - SIMLIB/C++ example\n");
  SetOutput("model2.out");
  Init(0,2000);
  (new LyzarGenerator)->Activate();
  (new NastupGenerator)->Activate();
  Run();
  amalka.Output();
  marcelka_queue.Output();
  uslona_queue.Output();
  table.Output();
  SIMLIB_statistics.Output();
  return 0;
}