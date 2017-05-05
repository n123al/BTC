/* 
 * File:   Person.h
 * Author: Nicholas Hadjiminas
 *
 * Created on October 25, 2013, 1:50 PM
 */

#ifndef PERSON_H
#define	PERSON_H

#include "PosesList.h"
#include "GesturesList.h"
#include "PoseManager.h"
#include "Events.h"
#include "Timer.h"
#include "MyHelper.h"
#include <algorithm> 

class Person {
public:
    list<KinectEvent> CurentEvents;
    list<KinectEvent> CurentEndEvents;

    Person();
    bool IsValid();
    int GetSkeletonID();
    const Vector3f &GetJointPosition(MyHelper::JointID joint);
    void SetSkeleton(skeleton& mySkeleton);
    void NewVoice(string &voice,int skeltonId);
    void NewSkeleton(skeleton& mySkeleton, PosesList& posesList ,GesturesList& gesturesList);
    virtual ~Person();   
    
private:   
    Timer time;
    skeleton Pskeleton;
    PoseManager pm;
    PosesList recognisedPoses;
    GesturesList ActiveGestureslist;
    Pose CurentPose;
};

#endif	/* PERSON_H */

