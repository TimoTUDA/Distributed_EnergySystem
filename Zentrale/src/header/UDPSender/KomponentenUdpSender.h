//
// Created by Philipp on 7.12.22.
//

#ifndef ZENTRALE_KOMPONENTENUDPSENDER_H
#define ZENTRALE_KOMPONENTENUDPSENDER_H

#include <string>
#include "UDPSender.h"
#include "../Komponenten/Komponente.h"


using namespace std;

/**
 *
 */
class KomponentenUdpSender : public UDPSender {
    int port { 5001 };

public:
    KomponentenUdpSender();
    KomponentenUdpSender(int port);

    void send(Komponente* komponente, string msg);

    std::thread komponentenThreadSend(Komponente* k, string msg);
};


#endif //ZENTRALE_KOMPONENTENUDPSENDER_H
