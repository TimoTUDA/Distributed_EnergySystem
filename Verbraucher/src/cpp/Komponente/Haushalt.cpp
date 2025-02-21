//
// Created by philipp on 5.12.22.
//

#include "../../header/Komponente/Haushalt.h"


/**
 *
 */
Haushalt::Haushalt(int id, string name) {
    this->id = id;
    this->type = "Haushalt";
    this->completeConsumption = 0.0;
    this->weekday = Weekday::Monday;
    this->time = 0;
    this->name = name;
}



/**
 *
 */
Haushalt::~Haushalt() = default;



/**
 *
 */
double Haushalt::getLastHourConsumption() {
    int randomNum = rand() % 100 + 1;
    double consumption = 0.0;
    if (this->weekday == Weekday::Saturday || this->weekday == Weekday::Sunday){
        if (time >= 9 || time <= 1){
            consumption = 2.0 / 100 * randomNum;
        }else{
            consumption = 0.8 / 100 * randomNum;
        }
    }else{
        if (time >= 16){
            consumption = 2.0 / 100 * randomNum;
        }else {
            consumption = 0.8 / 100 * randomNum;
        }
    }

    //next hour
    if (time < 24)
        ++time;
    else{
        //next day
        time = 0;
        switch (weekday) {
            case Weekday::Monday:
                weekday = Weekday::Tuesday;
                break;
            case Weekday::Tuesday:
                weekday = Weekday::Wednesday;
                break;
            case Weekday::Wednesday:
                weekday = Weekday::Thursday;
                break;
            case Weekday::Thursday:
                weekday = Weekday::Friday;
                break;
            case Weekday::Friday:
                weekday = Weekday::Saturday;
                break;
            case Weekday::Saturday:
                weekday = Weekday::Sunday;
                break;
            case Weekday::Sunday:
                weekday = Weekday::Monday;
                break;
        }
    }

    completeConsumption += consumption;
    return consumption;
}



/**
 *
 */
string Haushalt::getType(){
    return type;
}



/**
 *
 */
double Haushalt::getCompleteConsumption() const{
    return Verbraucher::getCompleteConsumption();
}
