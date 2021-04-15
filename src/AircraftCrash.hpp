#pragma once


#include "waypoint.hpp"
#include "geometry.hpp"


#include <stdexcept>
#include <string_view>

class AircraftCrash: public std::runtime_error
{
public:
    AircraftCrash(const std::string& flight_number_, 
    const Point3D& pos_,  const Point3D& speed_, const std::string& error_message)
    : std::runtime_error{build_error_msg(flight_number_, pos_, speed_, error_message)}{}

private:
    static std::string build_error_msg(const std::string& flight_number_, 
    const Point3D& pos_,  const Point3D& speed_, const std::string& error_message)
    {

        std::string msg;
        msg+= "Error : Aircraft "+flight_number_+" crashed at coordinates ("+std::to_string(pos_.x()) +","+std::to_string(pos_.y())+","+std::to_string(pos_.z())+") ";
        msg+= "Info : Speed of Aircraft ("+std::to_string(speed_.length())+") ";
        msg+= "Error message : "+error_message;


        return msg;
    }
};