#include "Camera.h"

Camera::Camera(){}

Camera::Camera(int objID, Vecpt eye, float w, float h, int minSubPt, int dmax) :
        Object(objID, Kind::CAMERA, eye){
            _width = w;
            _height = h;
            _dMax = dmax;
            _minSubPt = minSubPt;
        }

float Camera::get_width(){
    return _width;
}

float Camera::get_height(){
    return _height;
}

int Camera::get_minSubPt(){
    return _minSubPt;
}

int Camera::get_dMax(){
    return _dMax;
}