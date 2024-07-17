//
// Created by Timo on 11.12.22.
//

#include "../../header/Komponenten/Erzeuger.h"

Erzeuger::Erzeuger(std::string type, std::string name, int id, bool status) {
    this->name = name;
    this->type = type;
    this->id = id;
    this->status = status;
}

Erzeuger::~Erzeuger() {

}

std::string Erzeuger::getType() {
    return type;
}

bool Erzeuger::isStatus() const {
    return status;
}

void Erzeuger::setStatus(bool status) {
    Erzeuger::status = status;
}
