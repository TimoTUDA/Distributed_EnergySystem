//
// Created by Philipp on 14.12.22.
//

#ifndef ZENTRALE_MQTTINTERFACEZENTRALE_H
#define ZENTRALE_MQTTINTERFACEZENTRALE_H


/**
 *
 */
class MqttInterfaceZentrale {
public:
    virtual void sendWithMqtt(string channel, string message) = 0;
    virtual void sendToOtherZentralen(string message) = 0;
};

#endif //ZENTRALE_MQTTINTERFACEZENTRALE_H
