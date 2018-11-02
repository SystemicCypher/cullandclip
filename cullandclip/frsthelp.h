#include "vecpt.h"



namespace frustrum{
//  Checks, given a normal vector and a point to check, whether the point is above, on, or below the plane
    bool plane_check(Vecpt normal, Vecpt check){
        float dp = normal.dot(check);
        return (dp >= 0) ? true : false;
    }

//  Given a point and a vector, using t, this function returns any point on the line
    Vecpt point_on_line(Vecpt point, Vecpt vector, float t){
        if(point.is_point() && vector.is_vector()) return ((vector * t) + point);
        return Vecpt(0, POINT);
    }

//  Finds the intersection point between a line and a plane
    Vecpt intersection_point(Vecpt normal, Vecpt A, Vecpt B){
        if(normal.is_vector() && A.is_point() && B.is_point()){
            
        }
    }
}