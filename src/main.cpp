#include "tower_sim.hpp"
//#include "point.hpp"


void test_generic_points(){
    Point<3, float> p1;
    Point<3, float> p2;
    Point2D p4 {0,0} ; 
    //auto p3 = p1+p2;

    p1 += p2;
    p1 *= 3;
}


int main(int argc, char** argv)
{
    TowerSimulation simulation { argc, argv };

    test_generic_points();
    
    simulation.launch();

    return 0;
}