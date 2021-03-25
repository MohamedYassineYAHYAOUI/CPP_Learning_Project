#include "aircraft_manager.hpp"

#include <utility>

void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}

bool AircraftManager::update()
{

    aircrafts.erase(std::remove_if(aircrafts.begin(), aircrafts.end(), [](auto& aircraft){return !aircraft->update();}), 
    aircrafts.end());

    /*for (auto aircraft_it = aircrafts.begin(); aircraft_it != aircrafts.end();)
    {
        // On doit déréférencer 2x pour obtenir une référence sur l'Aircraft : une fois pour déréférencer
        // l'itérateur, et une deuxième fois pour déréférencer le unique_ptr.
        auto& aircraft = **aircraft_it;
        
       
        
        if (aircraft.update())
        {
            ++aircraft_it;
        }
        else
        {
            aircraft_it = aircrafts.erase(aircraft_it);
        }
    }
    */
    return true;
}


void AircraftManager::number_aircraft_by_index(const std::string& airline){
    const auto cnt = std::count_if(aircrafts.begin(), aircrafts.end(),
    [airline](const auto& aircraft){return aircraft->get_flight_num().substr(0,2).compare(airline) == 0;});
    std::cout << "number of " << airline << ": "<< cnt << std::endl;
}


