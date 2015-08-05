#ifndef IJSONSERIALIZABLE
#define IJSONSERIALIZABLE

#include "json.h"

class IJsonSerializable {

public:
    virtual void serialise(Json::Value &root) = 0;
    virtual void deserialise(Json::Value &root) = 0;

};

#endif // IJSONSERIALIZABLE

