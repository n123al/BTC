 /* 
 * File:   BTCHelper.h
 * Author: Nicholas Hadjiminas
 *
 * Created on 19 Ιούνιος 2013, 9:27 πμ
 */

#ifndef BTCHELPER_H
#define	BTCHELPER_H

#include "skeleton.h"
#include "iostream"
#include "RunTime.h"
#include "PosesSuggester.h"
#include "GestureXML.h"
#include "PoseXML.h"
#include <list>

class mGesture {
public:
    const char* ID;
    const char* value;
    const char* StartPose;
    bool* FoundStart;
    const char* EndPose;
    double* EndPoseHold;
    bool* FoundEnd;
    const char* Voice;
    bool* FoundVoice;
    float* MaxDuration;
};
class mPose{
public:
        const char* ID;
        const char* value;
        bool** Relations;
        double** Accuracy;
        mPose(){
        Relations = new bool*[MyHelper::AnglesCount];
        Accuracy = new double*[MyHelper::AnglesCount];
        }
        ~mPose(){
        if(Relations!=NULL)delete[] Relations;
        if(Accuracy!=NULL)delete[] Accuracy;
        }
};

class BTCHelper {
public:
    BTCHelper();
    //template <typename T> string tostr(const T& t);
    list<KinectEvent> * NewSkeleton(skeleton& mySkeleton ,int SkeletonId);
    list<KinectEvent> * NewVoice(string &myVoice, int SkeletonId);
    bool AddPose(skeleton& mySkeleton,string& PoseId,string& value, bool Relations[MyHelper::AnglesCount], double Accuracy[MyHelper::AnglesCount]);
    bool UpdatePose(string& PoseId,string& value, bool Relations[MyHelper::AnglesCount], double Accuracy[MyHelper::AnglesCount]);
    bool AddGesture(Gesture& myGesture);
    Gesture* GetGesture(string& GestureID);
    Pose* GetPose(string& PoseID);
    PosesList & GetPoseList();
    GesturesList & GetGesturesList();
    bool SaveGesturesList(const string & file, const string & key);
    bool SavePosesList(const string & file , const string & key);
    bool LoadPosesList(const string & file, bool newList, const string & key);
    bool LoadGesturesList(const string & file, bool newList, const string & key);
    bool RemovePoseById(string& myPoseId);
    bool RemoveGestureById(string& myGestureId);
    void Release();
   
    virtual ~BTCHelper();
private:  
    GestureXML GXML;
    PoseXML PXML;
    list<KinectEvent> Results[2];
    RunTime myRunTime;
    PosesSuggester PS;

};


#endif	/* BTCHELPER_H */

