//
// Created by Timo on 12.12.2022
//

#ifndef ERZEUGER_KOHLE_H
#define ERZEUGER_KOHLE_H


#include "Erzeuger.h"

using namespace std;

/**
 *
 */
class Kohle : public  Erzeuger {
private:
    double maximumGeneration;

public:
    Kohle(int id, string name, double maximumGeneration);
    virtual ~Kohle();

    double getLastHourGeneration() override;
};


#endif //ERZEUGER_KOHLE_H
