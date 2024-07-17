//
// Created by Timo on 18.12.2022
//

#ifndef LOADBALANCER_UDPSENDER_H
#define LOADBALANCER_UDPSENDER_H

#include <string>
#include "UDPCallback.h"

class UDPSender : public UDPCallback{
public:

    void processMessage(std::string s) override;

};


#endif //LOADBALANCER_UDPSENDER_H
