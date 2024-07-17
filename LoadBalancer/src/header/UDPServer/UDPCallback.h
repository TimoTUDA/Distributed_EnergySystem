//
// Created by Timo on 18.12.2022
//

#ifndef ZENTRALE_UDPCALLBACK_H
#define ZENTRALE_UDPCALLBACK_H

using namespace std;

/**
 * UDP contextController for incoming udp messages
 */
 class UDPCallback {
 public:
     virtual void processMessage (std::string s) = 0;

 };


#endif //ZENTRALE_UDPCALLBACK_H
