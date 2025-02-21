//
// Created by Timo on 12.12.2022
//

#include "../../header/Komponente/Wind.h"


/**
 *
 */
Wind::Wind(int id, string name, int size) {
    this->id = id;
    this->name = name;
    this->size = size;
    this->completeGeneration = 0;
    this->status = true;
    this->type = "Wind";
}



/**
 *
 */
Wind::~Wind() = default;



/**
 *
 */
double Wind::getLastHourGeneration() {
    double generation = (rand() % 450) * size; // avg 225 kw/h generation, to meet the avg % by 450
    completeGeneration += generation;
    return generation;
}
