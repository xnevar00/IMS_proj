////////////////////////////////////////////////////////////////////////////
//                          IMS project
//                           lift.hpp
//    Lukas Vecerka (xvecer30), Veronika Nevarilova (xnevar00)
//                            12/2023
//

#ifndef LIFT_HPP
#define LIFT_HPP
#include "simlib.h"

#define SEATS_TBAR      2
#define CLOSING_TIME 450*60

#define LIFTA_ENDINTERSECTIONID 7
#define LIFTB_ENDINTERSECTIONID 4
#define LIFTC_ENDINTERSECTIONID 11
#define LIFTD_ENDINTERSECTIONID 6
#define LIFTE_ENDINTERSECTIONID 5

// global objects:
extern Queue liftB_queue;
extern Queue liftA_queue;
extern Queue liftC_queue;
extern Queue liftD_queue;
extern Queue liftE_queue;
extern Histogram skiers;
extern Histogram liftA_queue_hist;
extern Histogram liftB_queue_hist;
extern int liftA_capacity;
extern int liftB_capacity;
extern double speed;

class Board: public Process {
public:
    void Behaviour();
protected:
    void process_chairlift(int waitTime, Queue *queue, int capacity);
    void process_tbar(int waitTime, Queue *queue);
};

class BoardingLiftB: public Board {
public:
    void Behavior();
};

class BoardingLiftA: public Board {

public:
    void Behavior();
};

class BoardingLiftC: public Board {
    public:
    void Behavior();
};

class BoardingLiftD: public Board {
public:
    void Behavior();
};

class BoardingLiftE: public Board {
public:
    void Behavior();
};
#endif