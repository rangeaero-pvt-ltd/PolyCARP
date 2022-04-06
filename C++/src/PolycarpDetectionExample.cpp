#include "Position.h"
#include "SimplePoly.h"
#include "Projection.h"
#include "PolycarpContain.h"
#include "MovingPolygon3D.h"
#include "PolycarpDetection.h"

#include <fmt/core.h>
#include <fmt/color.h>
/* Detection of Statically shaped polygons */



using namespace larcfm;

int main(){
    //Position of ownship at time t0
    Position ownship_position = Position::makeLatLonAlt(13.137701,"deg",77.503878,"deg",0,"m");
    Velocity ownship_velocityENU = Velocity::makeVxyz(4.0,4.0,"mps",2.0,"mps");
    

    
    //Create polygon to be detected and avoided
    double floor = 10;
    double ceiling = 30;
    SimplePoly polygon(floor, ceiling, "m");
    polygon.addVertex(Position::makeLatLonAlt(13.137470,"deg",77.503771,"deg",5,"m"));
     polygon.addVertex(Position::makeLatLonAlt(13.137703,"deg",77.503886,"deg",5,"m"));
    polygon.addVertex(Position::makeLatLonAlt(13.137948,"deg",77.503670,"deg",5,"m"));
     polygon.addVertex(Position::makeLatLonAlt(13.137695,"deg",77.503537,"deg",5,"m"));
    fmt::print("Generated polygon in geodectic plane\n");

    
    
    //Convert LatLonAlt to ENU frame
    EuclideanProjection projectionENU = Projection::createProjection(polygon.getVertex(0));
    Poly3D polygonENU = polygon.poly3D(projectionENU);
    fmt::print("Projected polygon to ENU frame\n");
   
    
    
    //Not clear about which method to use project or project2
    Vect3 ownship_position_enu = projectionENU.project(ownship_position);
    fmt::print("Projected ownship position to ENU frame\n");    

    
    
    fmt::print("Check niceness of polygon\n");
    //Buffer: Not clear about the role it has in checking whether polygon nice or not.
    double buffer = 0.1;
    //Check if the polygon in ENU frame is proper. Conditions for proper is defined in
    //function PolyCarpContain::nice_polygon_2D
    bool isNicepolygon = PolycarpContain::nice_polygon_2D(polygonENU.poly2D().getVertices(), buffer);
    fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold,"Role of buff in PolyCarpContain::nice_moving_polygon_2D\n"); 
    
    if(!isNicepolygon)
        fmt::print("V.Bad Polygon\n");
    else
        fmt::print("V Good Polygon\n");

    

    //Create moving polygon;Reguires velocity data;Requires tend data which should be time
    Velocity velocity_polygonENU = Velocity::makeVxyz(2.0,2.0,"mps",5.0,"mps");
    double tend = 40; //B
    MovingPolygon3D movingpolygonENU(polygonENU, velocity_polygonENU, tend);
    fmt::print("Created maving polygon with velocity(2,2,5)\n");

    
    
    //Static Collision detection
    bool will_collide =  PolycarpDetection::Static_Collision_Detector(tend, 100, polygonENU.poly2D().getVertices(), velocity_polygonENU.vect2(), 
                         ownship_position.vect2(), velocity_polygonENU.vect2(), 0.1, true );

    if (will_collide)
        fmt::print("The point will collide with polygon");
    else   
        fmt::print("Will not collide\n");

    return 0;
}