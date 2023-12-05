////////////////////////////////////////////////////////////////////////////
//                          IMS project
//                           lift.cpp
//    Lukas Vecerka (xvecer30), Veronika Nevarilova (xnevar00)
//                            12/2023
//

#include "lift.hpp"

Facility  liftF("Lift F");
Queue liftB_queue("Lift B Queue");
Queue liftA_queue("Lift A Queue");
Queue liftC_queue("Lift C Queue");
Queue liftD_queue("Lift D Queue");
Queue liftE_queue("Lift E Queue");
Histogram table("Table",0,25,20);

void BoardingLiftB::Behavior(){
    Arrival = Time;
    process_chairlift(278, &liftB_queue);
    table(Time-Arrival);
};

void BoardingLiftA::Behavior(){
    Arrival = Time;
    process_chairlift(450, &liftA_queue);
    table(Time-Arrival);
};

void BoardingLiftC::Behavior(){
    Arrival = Time;
    process_tbar(240, &liftC_queue);
    table(Time-Arrival);
};

void BoardingLiftD::Behavior(){
    Arrival = Time;
    process_tbar(240, &liftD_queue);
    table(Time-Arrival);
};

void BoardingLiftE::Behavior(){
    Arrival = Time;
    process_tbar(315, &liftE_queue);
    table(Time-Arrival);
};

void Board::process_chairlift(int time, Queue *queue){
    int skiers_count;
    std::string log;
    Entity *skiers_on_chairlift[SEATS_CHAIRLIFT];
    if (queue->Length() > 50)
    {
      skiers_count = 4;
    } else {
      skiers_count = (int)Uniform(1,5);
    }
    if (queue->empty()){
      log = "Ve fronte je 0 lyzaru, lanovka odjizdi prazdna\n";
      skiers_count = 0;
      Print(log.c_str());
    } else if (queue->Length() < skiers_count){
      log = "Nastupuje " + std::to_string(queue->Length()) + " lyzaru\n";
      Print(log.c_str());
      skiers_count = queue->Length();
    } else {
      log = "Nastupuje " + std::to_string(skiers_count) + " lyzaru\n";
      Print(log.c_str());
    }

    for (int i = 0; i < skiers_count; i++){
      skiers_on_chairlift[i] = queue->GetFirst();
    }
    Wait(time);
    for (int i = 0; i < skiers_count; i++){
      skiers_on_chairlift[i]->Activate();
    }
}

void  Board::process_tbar(int time, Queue *queue){
    int skiers_count;
    std::string log;
    Entity *skiers_on_chairlift[SEATS_TBAR];
    if (queue->Length() > 50)
    {
      skiers_count = 2;
    } else {
      skiers_count = (int)Uniform(1,3);
    }
    if (queue->empty()){
      log = "Ve fronte je 0 lyzaru, lanovka odjizdi prazdna\n";
      skiers_count = 0;
      Print(log.c_str());
    } else if (queue->Length() < skiers_count){
      log = "Nastupuje " + std::to_string(queue->Length()) + " lyzaru\n";
      Print(log.c_str());
      skiers_count = queue->Length();
    } else {
      log = "Nastupuje " + std::to_string(skiers_count) + " lyzaru\n";
      Print(log.c_str());
    }

    for (int i = 0; i < skiers_count; i++){
      skiers_on_chairlift[i] = queue->GetFirst();
    }
    Wait(time);
    for (int i = 0; i < skiers_count; i++){
      skiers_on_chairlift[i]->Activate();
    }
}