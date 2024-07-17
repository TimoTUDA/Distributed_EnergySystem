//
// Created by Timo on 22.12.2022
//

#include "../../header/Komponenten/Komponente.h"

Komponente::Komponente() {

}

Komponente::~Komponente() {

}

const map<time_t, double> &Komponente::getValues() const {
    return values;
}

void Komponente::addNewValue(time_t timestamp, double value) {
    mtx.lock();
    if (this->values.find(timestamp) == this->values.end())
        this->values.insert({timestamp,value});
    mtx.unlock();
}

const string &Komponente::getName() const {
    return name;
}

int Komponente::getId() const {
    return id;
}
