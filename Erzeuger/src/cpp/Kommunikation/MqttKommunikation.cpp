//
// Created by Timo on 22.12.2022
//

#include "../../header/Kommunikation/MqttKommunikation.h"

MqttKommunikation::MqttKommunikation(string brokerIP, string brokerChannel, string name) {
    findOutLocalIp();
    this->name = name;
    this->brokerChannel = brokerChannel;
    const string zentralenAddress = "tcp://" + brokerIP + ":1883";
    connectToMqttBroker(3,zentralenAddress,name);
}


MqttKommunikation::~MqttKommunikation() = default;


void MqttKommunikation::sendData(string message) {
    string channel = brokerChannel + "/data/" + name;
    try {
        auto mqttMsg = mqtt::make_message(channel, message,2, false);
        this->mqttClient->publish(mqttMsg);
    } catch (exception &e){
       cout << "Failed to send a message via MQTT." << endl << e.what() << endl;
    }
}


const string &MqttKommunikation::getIp() const {
    return ip;
}


void MqttKommunikation::findOutLocalIp() {
    try {
        const char* dnsServer = "8.8.8.8";
        int dns_port = 53;

        struct sockaddr_in serv;
        int sock = socket(AF_INET, SOCK_DGRAM, 0);

        //Socket could not be created
        if (sock < 0) {
            std::cout << "Socket error" << std::endl;
        }

        memset(&serv, 0, sizeof(serv));
        serv.sin_family = AF_INET;
        serv.sin_addr.s_addr = inet_addr(dnsServer);
        serv.sin_port = htons(dns_port);

        int err = connect(sock, (const struct sockaddr *) &serv, sizeof(serv));
        if (err < 0) {
            std::cout << "Error number: " << errno
                      << ". Error message: " << strerror(errno) << std::endl;
        }

        struct sockaddr_in name;
        socklen_t namelen = sizeof(name);
        err = getsockname(sock, (struct sockaddr *) &name, &namelen);

        char buffer[80];
        const char *p = inet_ntop(AF_INET, &name.sin_addr, buffer, 80);
        if (p != NULL) {
            this->ip = buffer;
        } else {
            std::cout << "Error number: " << errno
                      << ". Error message: " << strerror(errno) << std::endl;
        }

        close(sock);
    } catch (exception &e) {
        cout << "Failed to find out my own IP:(";
    }
}

void MqttKommunikation::connectToMqttBroker(int waitTime, string address, string name) {
    try {
        sleep(3);
        this->mqttClient = new mqtt::client(address, name);
        auto connOpts = mqtt::connect_options_builder()
                .automatic_reconnect(true)
                .clean_session(false)
                .finalize();
        this->mqttClient->connect(connOpts);

    } catch (exception &e) {
        cout << "Failed to connect to the Zentrale via MQTT." << endl << e.what() << endl;
        if (waitTime > 30) {
            exit(-1);
        }
        waitTime *= 2;
        cout << "Retry mqtt connection in " << waitTime << " seconds." << endl;
        connectToMqttBroker(waitTime,address,name);
    }
}
