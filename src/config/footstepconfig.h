#ifndef FOOTSTEPCONFIG_H
#define FOOTSTEPCONFIG_H

#include "lib/json.h"

#include <QString>

class FootstepConfig
{

public:
    enum CoordinateTypes { Decimal = 1, Degrees };

public:
    FootstepConfig();
    FootstepConfig(Json::Value root);

    QString profileDirectory() const;
    void setProfileDirectory(QString &profileDirectory);

    CoordinateTypes coordinateType() const;
    void setCoordinateType(CoordinateTypes coordType);

private:

    /**
     * @brief Sets the configuration values from the Json::Value root objet.
     * @param root
     */
    void setConfigValues(Json::Value root);

    QString _profileDirectory;
    CoordinateTypes _coordinateType;

};

#endif // FOOTSTEPCONFIG_H
