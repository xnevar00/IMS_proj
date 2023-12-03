#ifndef LIFT_HPP
#define LIFT_HPP
#include "simlib.h"

#define SEATS_CHAIRLIFT 4
#define SEATS_TBAR      2

#define LIFTA_ENDINTERSECTIONID 7
#define LIFTB_ENDINTERSECTIONID 4
#define LIFTC_ENDINTERSECTIONID 11
#define LIFTD_ENDINTERSECTIONID 6
#define LIFTE_ENDINTERSECTIONID 5
#define LIFTF_ENDINTERSECTIONID 12

// global objects:
extern Facility liftF;
extern Queue liftB_queue;
extern Queue liftA_queue;
extern Queue liftC_queue;
extern Queue liftD_queue;
extern Queue liftE_queue;
extern Histogram table;


class Board: public Process {
public:
    void Behaviour();
protected:
    void process_chairlift(int waitTime, Queue *queue);
    void process_tbar(int waitTime, Queue *queue);
};

class BoardingLiftB: public Board {
public:
    void Behavior();
private:
    double Arrival;
};

class BoardingLiftA: public Board {

public:
    void Behavior();
private:
    double Arrival;
};

class BoardingLiftC: public Board {
    public:
    void Behavior();
private:
    double Arrival;
};

class BoardingLiftD: public Board {
public:
    void Behavior();
private:
    double Arrival;
};

class BoardingLiftE: public Board {
public:
    void Behavior();
private:
    double Arrival;
};
#endif