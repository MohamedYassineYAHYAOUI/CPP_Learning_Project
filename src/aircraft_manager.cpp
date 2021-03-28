#include "aircraft_manager.hpp"

#include <utility>

void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}


void AircraftManager::print_aircrafts()
{
    std::for_each(aircrafts.begin(), aircrafts.end(), 
    [](auto& a1){std::cout << a1->get_flight_num() << " has terminal " << a1->has_terminal() << " / Fuel : " << a1->get_fuel() << std::endl;});

}


bool AircraftManager::update()
{


    std::sort(aircrafts.begin(), aircrafts.end(), [](auto& a1, auto& a2){
        if((a1->has_terminal() && a2->has_terminal()) || (!a1->has_terminal() && !a2->has_terminal())){
            return a1->get_fuel() > a2->get_fuel(); 
        }else if (a1->has_terminal() && !a2->has_terminal())
        {
            return true;
        }else
        {
            return false;
        }
        });

    //print_aircrafts();
    //std::cout << "required fuel " << get_required_fuel() << std::endl;
    
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


int AircraftManager::get_required_fuel(){
   
    /*return std::accumulate(aircrafts.begin(), aircrafts.end(), 0,
    [](int sum, auto& aircraft){
        assert(aircraft != nullptr);
        if(aircraft->is_low_on_fuel() && aircraft->aircraft_in_terminal())
        {
            sum += (3000 - aircraft->get_fuel());
        }
        return sum;
    });*/


    int sum =0;
    for (auto aircraft_it = aircrafts.begin(); aircraft_it != aircrafts.end();)
    {
        // On doit déréférencer 2x pour obtenir une référence sur l'Aircraft : une fois pour déréférencer
        // l'itérateur, et une deuxième fois pour déréférencer le unique_ptr.
        auto& aircraft = **aircraft_it;
        if(aircraft.is_low_on_fuel() && aircraft.aircraft_in_terminal()){  
            sum+= (3000 - aircraft.get_fuel());
        }
        ++aircraft_it;
    }
    return sum;
}

