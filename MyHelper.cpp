/* 
 * File:   MyHelper.cpp
 * Author: Nicholas Hadjiminas
 * 
 * Created on 18 Ιανουάριος 2013, 10:04 πμ
 */

#include "MyHelper.h"

template <typename T> T MyHelper::CLAMP(const T& value, const T& low, const T& high) {
    return value < low ? low : (value > high ? high : value);
}

double MyHelper::VectorAngle(Vector3f& StartVector1, Vector3f& EndVector1, Vector3f& StartVector2, Vector3f& EndVector2) {
    double angle;
    float Dotproduct;
    Vector3f Vector1 = EndVector1 - StartVector1;
    Vector3f Vector2 = EndVector2 - StartVector2;
    Vector1.normalize();
    Vector2.normalize();
    Dotproduct = Vector1.dotProduct(Vector2);
    angle =  acos((double)(CLAMP(Dotproduct, -1.0f, 1.0f)));
    return angle;
}

Vector3f MyHelper::VectorsNormal(Vector3f& StartVector1, Vector3f& EndVector1, Vector3f& StartVector2, Vector3f& EndVector2) {
    Vector3f Normal;
    //create the two vectors by subtracting the End Vertex values from the Start Vertex 
    Vector3f Vector1 = EndVector1 - StartVector1;
    Vector3f Vector2 = EndVector2 - StartVector2;
    Normal = Vector1.crossProduct(Vector2);
    Normal.normalize();
    return Normal;
}

