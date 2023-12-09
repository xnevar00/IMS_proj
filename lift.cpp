////////////////////////////////////////////////////////////////////////////
//                          IMS project
//                           lift.cpp
//    Lukas Vecerka (xvecer30), Veronika Nevarilova (xnevar00)
//                            12/2023
//

#include "lift.hpp"

Queue liftB_queue("Lift B Queue");
Queue liftA_queue("Lift A Queue");
Queue liftC_queue("Lift C Queue");
Queue liftD_queue("Lift D Queue");
Queue liftE_queue("Lift E Queue");
Histogram skiers("Skiers time in system histogram",0,10*60, CLOSING_TIME/(10*60));
Histogram liftA_queue_hist("Lift A Queue Histogram",0,10*60, CLOSING_TIME/(10*60));
Histogram liftB_queue_hist("Lift B Queue Histogram",0,10*60, CLOSING_TIME/(10*60));
int liftA_capacity = 4;
int liftB_capacity = 4;
double speed = 1.0;

void BoardingLiftB::Behavior(){
    process_chairlift(430/speed, &liftB_queue, liftB_capacity);
};

void BoardingLiftA::Behavior(){
    process_chairlift(440/speed, &liftA_queue, liftA_capacity);
};

void BoardingLiftC::Behavior(){
    process_tbar(200, &liftC_queue);
};

void BoardingLiftD::Behavior(){
    process_tbar(200, &liftD_queue);
};

void BoardingLiftE::Behavior(){
    process_tbar(80, &liftE_queue);
};

void Board::process_chairlift(int time, Queue *queue, int capacity){
    int skiers_count;
    std::string log;
    Entity *skiers_on_chairlift[capacity];
    if (queue->Length() > 50)
    {
      skiers_count = capacity;
    } else {
      skiers_count = (int)Uniform(1,capacity+1);
    }
    if (queue->empty()){
      skiers_count = 0;
    } else if (queue->Length() < skiers_count){
      skiers_count = queue->Length();
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
      skiers_count = 0;
    } else if (queue->Length() < skiers_count){
      skiers_count = queue->Length();
    }

    for (int i = 0; i < skiers_count; i++){
      skiers_on_chairlift[i] = queue->GetFirst();
    }
    Wait(time);
    for (int i = 0; i < skiers_count; i++){
      skiers_on_chairlift[i]->Activate();
    }
}