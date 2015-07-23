#ifndef TRACK_H
#define TRACK_H

#include "string.h"

class Track
{
public:
    Track(string name);

    setName(string name);
    setDescription(string desc);

private:

    string _name;
    string _description;


};

#endif // TRACK_H
