//
// Created by Timo on 05.12.2022
//

#ifndef LOADBALANCER_ZENTRALE_H
#define LOADBALANCER_ZENTRALE_H

#include "string"
#include "vector"

using std::vector;
using std::string;

class Zentrale {
private:

    string ip;
    int id;
    string name;
    static int count;


public:
    Zentrale(const string &ip, const string &name);
    virtual ~Zentrale();

    const string &getIp() const;

};


#endif //LOADBALANCER_ZENTRALE_H
