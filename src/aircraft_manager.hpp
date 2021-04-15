#pragma once

#include "GL/dynamic_object.hpp"
#include "aircraft.hpp"

#include <memory>
#include <vector>
#include <algorithm>

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;

    void print_aircrafts();

    int get_required_fuel();

    int _crash_conter = 0;

public:
    
    AircraftManager()=default;

    void add(std::unique_ptr<Aircraft> aircraft);

    bool update() override;

    void number_aircraft_by_index(const std::string& airline);

    void number_of_crashed_airplanes();

    friend class Airport;
};
