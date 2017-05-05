/* 
 * File:   BTCHelper.cpp
 * Author: Nicholas Hadjiminas
 * 
 * Created on 19 Ιούνιος 2013, 9:27 πμ
 */

#include "BTCHelper.h"

BTCHelper::BTCHelper() {
}

BTCHelper::~BTCHelper() {
}

void BTCHelper::Release() {
    this->~BTCHelper();
}

bool BTCHelper::AddPose(skeleton& mySkeleton, string& PoseId, string& value, bool Relations[MyHelper::AnglesCount], double Accuracy[MyHelper::AnglesCount]) {
    Pose myPose;
    myPose.ID = PoseId;
    myPose.value = value;
    myPose.LoadRelations(Relations, Accuracy);
    myPose.LoadJoins(mySkeleton);
    return myRunTime.posesList.Add(myPose);
}

bool BTCHelper::UpdatePose(string& PoseId, string& value, bool Relations[MyHelper::AnglesCount], double Accuracy[MyHelper::AnglesCount]) {
    Pose * myPose = myRunTime.posesList.GetPoseById(PoseId) ;
    if (myPose !=NULL){
    myPose->ID = PoseId;
    myPose->value = value;
    myPose->LoadRelations(Relations, Accuracy);
    }
    else return false;
    return true;
}

PosesList & BTCHelper::GetPoseList() {
    return myRunTime.posesList;
}

GesturesList & BTCHelper::GetGesturesList() {
    return myRunTime.gesturesList;
}

bool BTCHelper::AddGesture(Gesture& myGesture) {
    return myRunTime.gesturesList.Add(myGesture);
}

Gesture* BTCHelper::GetGesture(string& GestureID) {
    return myRunTime.gesturesList.GetGestureById(GestureID);
}

Pose* BTCHelper::GetPose(string& PoseID) {
    return myRunTime.posesList.GetPoseById(PoseID);
}

list<KinectEvent> * BTCHelper::NewVoice(string &myVoice, int SkeletonId){
    myRunTime.LoadVoices(myVoice,SkeletonId);
    Results[0] = myRunTime.EventRecgonized();
    Results[1] = myRunTime.EventStopRecgonized();
    return Results;
}

list<KinectEvent> * BTCHelper::NewSkeleton(skeleton& mySkeleton, int SkeletonId) {
    myRunTime.LoadSkeletonData(mySkeleton ,SkeletonId);
    Results[0] = myRunTime.EventRecgonized();
    Results[1] = myRunTime.EventStopRecgonized();
    return Results;
}

bool BTCHelper::RemovePoseById(string& myPoseId) {
    return myRunTime.posesList.RemovePoseById(myPoseId);
}

bool BTCHelper::RemoveGestureById(string& myGestureId) {
    return myRunTime.gesturesList.RemoveGestureById(myGestureId);
}
bool BTCHelper::SaveGesturesList(const string &file, const string & key ) {
    GXML.SaveGesturesList(myRunTime.gesturesList,file,key);
}

bool BTCHelper::SavePosesList(const string &file, const string & key) {
    PXML.SavePosesList(myRunTime.posesList,file ,key);
}
bool BTCHelper::LoadPosesList(const string & file, bool newList, const string & key) {
     if(newList) myRunTime.posesList.Clear();
    PXML.LoadPosesList(myRunTime.posesList,file,key);
}

bool BTCHelper::LoadGesturesList(const string & file, bool newList, const string & key) {
    if(newList) myRunTime.gesturesList.Clear();
    GXML.LoadGesturesList(myRunTime.gesturesList,file,key);
}


