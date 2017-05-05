/* 
 * File:   RunTime.h
 * Author: Nicholas Hadjiminas
 *
 * Created on 18 Ιούνιος 2013, 11:50 πμ
 */

#ifndef RUNTIME_H
#define	RUNTIME_H

#include "PosesList.h"
#include "GesturesList.h"
#include "PoseManager.h"
#include "Events.h"
#include "Person.h"
#include <algorithm> 
#include <iostream>  




class RunTime {
public:
    RunTime();
    void LoadVoices(string &Voice,int SkeletonId);
    void LoadVoices(string &Voice,double SourceAngle);
    void LoadSkeletonData(skeleton& mySkeleton ,int SkeletonId);
    list<KinectEvent> EventRecgonized(void);
    list<KinectEvent> EventStopRecgonized(void);
    PosesList posesList;
    GesturesList gesturesList;
    virtual ~RunTime();
    
private:
   double DistanceOfAngle(double Angle, const Vector3f &Position);
   list<KinectEvent> CurentEvents;
   list<KinectEvent> CurentEndEvents;
  /*   PoseManager pm;
    PosesList recognisedPoses;
    GesturesList ActiveGestureslist;
    Pose CurentPose;*/
    list<Person> Persons;
    //typedef pair<int,float> myPair;
    
};
#endif	/* RUNTIME_H */

