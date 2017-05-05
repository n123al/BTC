/* 
 * File:   Pose.h
 * Author: Nicholas Hadjiminas
 *
 * Created on 11 Ιανουάριος 2013, 1:00 μμ
 */

#ifndef POSE_H
#define	POSE_H
#include <iostream>
#include <map>

#include "MyHelper.h"
#include "skeleton.h"
#include "RecognitionElement.h"
#include "vmath.h"

using namespace std;

class MyAngle
{
    public:
        double angle;
       // bool active = true;
        bool active;
        Vector3f direction;
        //double accuracy = 0.2;
        double accuracy;
};
    
class  Pose: public RecognitionElement{  
public:
   
    Pose();
    Pose& operator= (const Pose & other);
    void LoadRelations(bool * Relations, double * Accuracy);
    void LoadJoins(skeleton& myskeleton);
    virtual ~Pose();
    map<MyHelper::AnglesID, MyAngle> PoseAngles;
};

#endif	/* POSE_H */

