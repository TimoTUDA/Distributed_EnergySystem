//
// Created by Philipp on 7.12.22.
//

#ifndef ZENTRALE_UDPCALLBACK_H
#define ZENTRALE_UDPCALLBACK_H

using namespace std;

/**
 * UDP contextController for incoming udp messages
 */
 class UDPCallback {
 public:
     virtual void processMessageUdp (string ip, std::string) = 0;

 };


#endif //ZENTRALE_UDPCALLBACK_H
