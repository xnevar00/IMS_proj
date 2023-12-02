#include "lift.hpp"

Facility  amalka("Amalka");
Queue marcelka_queue("MarcelkaQueue");
Queue uslona_queue("U Slona Queue");
Histogram table("Table",0,25,20);

void NastupMarcelka::Behavior(){
    Arrival = Time;
    int pocet_lyzaru;
    if (marcelka_queue.Length() > 50)
    {
      pocet_lyzaru = 4;
    } else {
      pocet_lyzaru = (int)Uniform(1,5);
    }
    if (marcelka_queue.empty()){
      vypis = "Ve fronte je 0 lyzaru, lanovka odjizdi prazdna\n";
      pocet_lyzaru = 0;
      Print(vypis.c_str());
    } else if (marcelka_queue.Length() < pocet_lyzaru){
      vypis = "Nastupuje " + std::to_string(marcelka_queue.Length()) + " lyzaru\n";
      Print(vypis.c_str());
      pocet_lyzaru = marcelka_queue.Length();
    } else {
      vypis = "Nastupuje " + std::to_string(pocet_lyzaru) + " lyzaru\n";
      Print(vypis.c_str());
    }

    for (int i = 0; i < pocet_lyzaru; i++){
      lyzari_na_lanovce[i] = marcelka_queue.GetFirst();
    }
    Wait(278);
    for (int i = 0; i < pocet_lyzaru; i++){
      lyzari_na_lanovce[i]->Activate();
    }
    table(Time-Arrival);
};

void NastupUSlona::Behavior(){
    Arrival = Time;
    int pocet_lyzaru;
    if (uslona_queue.Length() > 50)
    {
      pocet_lyzaru = 4;
    } else {
      pocet_lyzaru = (int)Uniform(1,5);
    }
    if (uslona_queue.empty()){
      vypis = "Ve fronte je 0 lyzaru, lanovka odjizdi prazdna\n";
      pocet_lyzaru = 0;
      Print(vypis.c_str());
    } else if (uslona_queue.Length() < pocet_lyzaru){
      vypis = "Nastupuje " + std::to_string(uslona_queue.Length()) + " lyzaru\n";
      Print(vypis.c_str());
      pocet_lyzaru = uslona_queue.Length();
    } else {
      vypis = "Nastupuje " + std::to_string(pocet_lyzaru) + " lyzaru\n";
      Print(vypis.c_str());
    }

    for (int i = 0; i < pocet_lyzaru; i++){
      lyzari_na_lanovce[i] = uslona_queue.GetFirst();
    }
    Wait(450);
    for (int i = 0; i < pocet_lyzaru; i++){
      lyzari_na_lanovce[i]->Activate();
    }
    table(Time-Arrival);
};