//
// Created by Timo on 05.12.2022
//

#include "../../header/Zentrale/Zentrale.h"

int Zentrale::count = 0;

Zentrale::Zentrale(const string &ip, const string &name) {
    this->ip = ip;
    this->id = count;
    this->name = name;
    ++count;
}

Zentrale::~Zentrale() {

}

const string &Zentrale::getIp() const {
    return ip;
}
