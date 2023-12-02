#include "skier.hpp"

void Skier::Behavior()
{
    arrival = Time; 

    double lift_choice = Random();
    if (lift_choice < PST_AMALKA){
        GoToAmalka();
    } else if (lift_choice < 0.5) {
        GoToUSlona();
    } else {
        GoToMarcelka();
    }

    table(Time-arrival);
}

void Skier::GoToAmalka()
{
    output = std::to_string(id()) + " Jdu na Amalku\n";
    Print(output.c_str());

    Seize(amalka);
    output = std::to_string(id()) + " Snazim se dostat na Amalku\n";
    Print(output.c_str());
      
    bool fail = true;
    while(fail){
        if (Random() >= 0.2){
          fail = false;
          output = std::to_string(id()) + " Povedlo se mi dostat na Amalku\n";
          Print(output.c_str());
        } else {                          // failed to get on the lift
          output = std::to_string(id()) + " Jsem blb a spadl jsem, zkousim to znovu\n";
          Print(output.c_str());
        }
        Wait(6);
    }
    Release(amalka); 
    Wait(48);
    output = std::to_string(id()) + " Dojel jsem nahoru na Amalce\n";
    Print(output.c_str());
}

void Skier::GoToMarcelka()
{
    output = std::to_string(id()) + " Jdu na Marcelku\n";
    Print(output.c_str());
    marcelka_queue.Insert(this);
    Passivate();
    output = std::to_string(id()) + " Vyjel jsem na Marcelku\n";
    Print(output.c_str());
}

void Skier::GoToUSlona()
{
    output = std::to_string(id()) + " Jdu na U Slona\n";
    Print(output.c_str());
    uslona_queue.Insert(this);
    Passivate();
    output = std::to_string(id()) + " Vyjel jsem na USlona\n";
    Print(output.c_str());
}