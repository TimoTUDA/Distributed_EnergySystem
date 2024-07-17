//
// Created by Timo on 15.12.2022
//

#ifndef ZENTRALE_UDPCALLBACK_H
#define ZENTRALE_UDPCALLBACK_H

using namespace std;

/**
 * Kommunikation contextController for incoming udp messages
 */
class UDPCallback {
public:
    virtual void processMessage (string ip, std::string) = 0;

};


#endif //ZENTRALE_UDPCALLBACK_H
