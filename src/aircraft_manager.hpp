#pragma once

#include <vector>
#include "aircraft.hpp"

class AircraftManager
{
private:
    const std::vector<std::unique_ptr<Aircraft>> _aircrafts ;


public: 
    AircraftManager();
    virtual ~AircraftManager()
    {
        _aircrafts.erase(std::find(_aircrafts.begin(), _aircrafts.end(), this));
    }

};