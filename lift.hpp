#ifndef LIFT_HPP
#define LIFT_HPP
#include "simlib.h"

// global objects:

extern Facility amalka;
extern Queue marcelka_queue;
extern Queue uslona_queue;
extern Histogram table;

class NastupMarcelka: public Process {

public:
    void Behavior();
private:
    double Arrival;
    Entity *lyzari_na_lanovce[4];
    std::string vypis;
};

class NastupUSlona: public Process {

public:
    void Behavior();
private:
    double Arrival;
    Entity *lyzari_na_lanovce[4];
    std::string vypis;
};
#endif