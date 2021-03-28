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

public:
    void add(std::unique_ptr<Aircraft> aircraft);

    bool update() override;

    void number_aircraft_by_index(const std::string& airline);

    friend class Airport;
};
