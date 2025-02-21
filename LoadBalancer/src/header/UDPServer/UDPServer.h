//
// Created by Timo on 18.12.2022
//

#ifndef ZENTRALE_UDPSERVER_H
#define ZENTRALE_UDPSERVER_H

#define MESSAGE_SIZE 1500

#include <string>
#include <iostream>
#include <thread>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>

#include "UDPCallback.h"

using namespace std;

/**
 * UDPServer implementation for incoming udp connections.
 */
class UDPServer {
private:
    void run();
    UDPCallback* callback {};

    int socket_fd {-1};
    bool simulatePacketLoss = false;

    // Thread state
    bool stopped {false};

public:
    UDPServer();
    virtual ~UDPServer();

    void setCallback(UDPCallback* callback);
    void init(int port);

    void setPacketLoss(bool value);

    // Thread functions
    void operator()();
    void stop();
};


#endif //ZENTRALE_UDPSERVER_H
