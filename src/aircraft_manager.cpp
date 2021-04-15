#include "aircraft_manager.hpp"

#include <utility>

void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}


void AircraftManager::print_aircrafts()
{
    std::for_each(aircrafts.begin(), aircrafts.end(), 
    [](auto& a1){std::cout << a1->get_flight_num() << " has terminal " << a1->has_terminal()<< " / Fuel : " << a1->get_fuel() << std::endl;});
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

    print_aircrafts();

    
    aircrafts.erase(std::remove_if(aircrafts.begin(), aircrafts.end(), [this](auto& aircraft){
            try{
                return !aircraft->update();
            }catch(AircraftCrash& e){
                this->_crash_conter++;
                std::cerr << e.what() <<std::endl;
                return true;
            }
        }), aircrafts.end());

    return true;
}


void AircraftManager::number_of_crashed_airplanes(){
    std::cout << "Number of aircraft that crashed: "<<_crash_conter << std::endl;
}


void AircraftManager::number_aircraft_by_index(const std::string& airline){
    const auto cnt = std::count_if(aircrafts.begin(), aircrafts.end(),
    [airline](const auto& aircraft){return aircraft->get_flight_num().substr(0,2).compare(airline) == 0;});
    std::cout << "number of " << airline << ": "<< cnt << std::endl;
}


int AircraftManager::get_required_fuel(){
    int sum =0;

    std::cout << "size " << aircrafts.size() << std::endl;

    std::for_each(aircrafts.begin(),aircrafts.end(),[&sum](auto& a){

        if(a->is_low_on_fuel() && a-> aircraft_in_terminal()){
            sum+= (3000 - a->get_fuel());
        }
    });
    
    return sum;
}

