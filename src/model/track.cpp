#include "track.h"

Track::Track(string name)
{
    this->name = name;
}

Track::setDescription(string desc) {
    this->_description = desc;
}

Track::setName(string name) {
    this->_name = name;
}
