//
// Created by Timo on 22.12.2022
//

#ifndef ENERGIEVERSORGER_ERZEUGER_H
#define ENERGIEVERSORGER_ERZEUGER_H

#include "Komponente.h"

class Erzeuger : public Komponente {
public:
    Erzeuger(std::string type, std::string name, int id);
    ~Erzeuger();

    virtual std::string getType() override;
};


#endif //ENERGIEVERSORGER_ERZEUGER_H
