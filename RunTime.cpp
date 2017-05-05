/* 
 * File:   RunTime.cpp
 * Author: Nicholas Hadjiminas
 * 
 * Created on 18 Ιούνιος 2013, 11:50 πμ
 */

#include "RunTime.h"
#include "Person.h"

RunTime::RunTime() {
}

void RunTime::LoadSkeletonData(skeleton& mySkeleton , int SkeletonId){
    bool found = false; 
    
   for (list<Person>::iterator iterator = Persons.begin(), end = Persons.end(); iterator != end; ++iterator) {
        Person &cperson = *iterator;
        if(cperson.GetSkeletonID() == SkeletonId) {
            found = true;
            cperson.NewSkeleton(mySkeleton, this->posesList , this->gesturesList );
        }
        else if(!cperson.IsValid()) Persons.erase(iterator);
  }
    if (!found){
       Person person;
       person.SetSkeleton(mySkeleton);
       person.NewSkeleton(mySkeleton, this->posesList , this->gesturesList );
       Persons.push_back(person); 
    }
    
}

void RunTime::LoadVoices(string &Voice, int SkeletonId){
    for (list<Person>::iterator iterator = Persons.begin(), end = Persons.end(); iterator != end; ++iterator) {
        Person &cperson = *iterator;
        if(cperson.GetSkeletonID() == SkeletonId) {
            cperson.NewVoice(Voice,SkeletonId);
        }
        else if(!cperson.IsValid()) Persons.erase(iterator);
    }
}

static bool pairCompare(const pair<int,float> &firstElem, const pair<int,float>& secondElem) {
  return firstElem.second < secondElem.second;
}

void RunTime::LoadVoices(string &Voice,double SourceAngle){
    list<pair<int,float> >SkeletonsDistance;
    int SkeletonId=-1;
    
     for (list<Person>::iterator iterator = Persons.begin(), end = Persons.end(); iterator != end; ++iterator) {
        Person &cperson = *iterator;
        SkeletonsDistance.push_front(pair<int,float> (cperson.GetSkeletonID(),DistanceOfAngle(SourceAngle,cperson.GetJointPosition(MyHelper::Head))));
     }
    SkeletonsDistance.sort(pairCompare);
    pair<int,float> &tp = SkeletonsDistance.front();
    if(tp.second < 0.5f) SkeletonId= tp.first;
    if(SkeletonId >-1)LoadVoices(Voice,SkeletonId);
}


 double RunTime::DistanceOfAngle(double Angle, const Vector3f &Position){
     float x,y,distance,hd;
     hd= sqrt((Position.z*Position.z)+(Position.x*Position.x));
     y =cos(DEG2RAD(Angle))* hd;
     x =(Angle/abs(Angle))*sin(DEG2RAD(Angle))* hd;
     distance = sqrt(((x-Position.x)*(x-Position.x))+((y-Position.z)*(x-Position.z)));
     return distance;
 }

//Announce event recognition 
list<KinectEvent> RunTime::EventRecgonized(void) { 
    list<KinectEvent> curentEvents;
    for (list<Person>::iterator iterator = Persons.begin(), end = Persons.end(); iterator != end; ++iterator) {
        Person &cperson = *iterator;
        for(list<KinectEvent>::iterator Eiterator = cperson.CurentEvents.begin(), end = cperson.CurentEvents.end(); Eiterator != end; ++Eiterator)
            curentEvents.push_back((KinectEvent)*Eiterator);
        cperson.CurentEvents.clear();
    }
    return curentEvents;
}

//Announce event expiration  
list<KinectEvent> RunTime::EventStopRecgonized(void) {
    list<KinectEvent> curentEndEvents;
    for (list<Person>::iterator iterator = Persons.begin(), end = Persons.end(); iterator != end; ++iterator) {
        Person &cperson = *iterator;
        for(list<KinectEvent>::iterator Eiterator = cperson.CurentEndEvents.begin(), end = cperson.CurentEndEvents.end(); Eiterator != end; ++Eiterator)
            curentEndEvents.push_back((KinectEvent)*Eiterator);
        cperson.CurentEndEvents.clear();
    }
    return curentEndEvents;
}

RunTime::~RunTime() {
}

