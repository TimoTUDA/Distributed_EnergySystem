//
// Created by Timo on 22.12.2022
//

#include "../../header/Komponenten/Erzeuger.h"

Erzeuger::Erzeuger(std::string type, std::string name, int id) {
    this->name = name;
    this->type = type;
    this->id = id;
}

Erzeuger::~Erzeuger() {

}

std::string Erzeuger::getType() {
    return type;
}