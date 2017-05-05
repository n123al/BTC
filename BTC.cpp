/* 
 * File:   BTC.cpp
 * Author: Nicholas Hadjiminas
 *
 * Created on 27 Ιούνιος 2013, 8:11 πμ
 */

#include <cstdlib>
#include "BTCHelper.h"
#include "GestureXML.h"
#include "GeneralHelper.h"
#include <fstream>

using namespace std;
static BTCHelper* BTCH = new BTCHelper();
//keep records of object dynamically allocated
KinectEvent*** results;
mGesture* OutGesture;
mPose* OutPose;
const char ** poseList;
const char ** gestureList;


int main(int argc, char** argv) {
    if (BTCH == NULL) BTCH = new BTCHelper();
    return 0;
}

void FreeTables() {
    if (results != NULL) {
        if (results[0] != NULL) {
            delete[] results[0];
            results[0] = NULL;
        }
        if (results[1] != NULL) {
            delete[] results[1];
            results[1] = NULL;
        }
        delete[] results;
        results = NULL;
    }
    if (poseList != NULL) {
        delete[] poseList;
        poseList = NULL;
    }
    if (gestureList != NULL) {
        delete[] gestureList;
        gestureList = NULL;
    }

}


extern "C" __declspec(dllexport) bool AddGesture(mGesture* myGesture , bool replace) {
    if (BTCH == NULL) return false;
    Gesture tmp;
    tmp.ID = (*myGesture).ID;
    tmp.value = (*myGesture).value;
    tmp.StartPose = (*myGesture).StartPose;
    tmp.FoundStart = *(*myGesture).FoundStart;
    tmp.EndPose = (*myGesture).EndPose;
    tmp.EndPoseHold = *(*myGesture).EndPoseHold;
    tmp.FoundEnd = *(*myGesture).FoundEnd;
    tmp.Voice = (*myGesture).Voice;
    tmp.FoundVoice = *(*myGesture).FoundVoice;
    tmp.MaxDuration = *(*myGesture).MaxDuration;
    
    if(replace)BTCH->RemoveGestureById(tmp.ID);
    // return myGesture->FoundVoice;
    return BTCH->AddGesture(tmp);
}

extern "C" __declspec(dllexport) bool DeleteGesture(const char* GestureID){
 if (BTCH == NULL) return false;
 string GestureId = GestureID;
 return BTCH->RemoveGestureById(GestureId);
}

extern "C" __declspec(dllexport) KinectEvent*** NewVoice(int* NewEvents, int* EndedEvents, const char* Voice,int skeletonID){
    int SkeletonId =skeletonID;
    string mVoice =Voice;
    int i = 0;
    
    list<KinectEvent> * resault = BTCH->NewVoice(mVoice,skeletonID);
    *NewEvents = resault[0].size();
    *EndedEvents = resault[1].size();

    FreeTables();
    //conver event list to array
    results = new KinectEvent**[2];

    // new events
    if (*NewEvents > 0) {
        KinectEvent ** newEvents = new KinectEvent*[*NewEvents];
        i = 0;
        for (list<KinectEvent>::const_iterator iterator = resault[0].begin(), end = resault[0].end(); iterator != end; ++iterator) {
            newEvents[i] = (KinectEvent*) &(* iterator);
            i = i + 1;
        }
        results[0] = newEvents;
    } else results[0] = NULL;


    // ended events
    if (*EndedEvents > 0) {
        KinectEvent ** endedEvents = new KinectEvent*[*EndedEvents];
        i = 0;
        for (list<KinectEvent>::const_iterator iterator = resault[1].begin(), end = resault[1].end(); iterator != end; ++iterator) {
            endedEvents[i] = (KinectEvent*) &(* iterator);
            i = i + 1;
        }
        results[1] = endedEvents;
    } else results[1] = NULL;
    
    return results;

}

extern "C" __declspec(dllexport) mGesture* GetGesture(const char* GestureID) {
    if (BTCH == NULL) return NULL;
    Gesture* myGesture;
    string ID = GestureID;
    myGesture = BTCH->GetGesture(ID);
    if (myGesture == NULL)return NULL;
    if (OutGesture != NULL) {
        delete OutGesture;
        OutGesture = NULL;
    }
    OutGesture = new mGesture();
    (*OutGesture).ID = (*myGesture).ID.c_str();
    (*OutGesture).value = (*myGesture).value.c_str();
    (*OutGesture).StartPose = (*myGesture).StartPose.c_str();
    (*OutGesture).FoundStart = &((*myGesture).FoundStart);
    (*OutGesture).EndPose = (*myGesture).EndPose.c_str();
    (*OutGesture).EndPoseHold = &((*myGesture).EndPoseHold);
    (*OutGesture).FoundEnd = &((*myGesture).FoundEnd);
    (*OutGesture).Voice = (*myGesture).Voice.c_str();
    (*OutGesture).FoundVoice = &((*myGesture).FoundVoice);
    (*OutGesture).MaxDuration = &((*myGesture).MaxDuration);
    return OutGesture;
}

extern "C" __declspec(dllexport) const char** GetGestureList(int* NumOfGesture ) {
   GesturesList& Gestures = BTCH->GetGesturesList();
    if (gestureList != NULL) {
        delete[] gestureList;
        gestureList = NULL;
    }
   *NumOfGesture=Gestures.Length();
    gestureList = new const char*[*NumOfGesture];
    int i =0;
    for (list<Gesture>::const_iterator iterator = Gestures.begin(), end = Gestures.end(); iterator != end; ++iterator) {
      gestureList[i] = ((Gesture) * iterator).ID.c_str();
      i++;
    }
    return gestureList;
}

extern "C" __declspec(dllexport) mPose* GetPose(const char* PoseID) {
    if (BTCH == NULL) return NULL;
    Pose * myPose;
    string ID = PoseID;
    myPose = BTCH->GetPose(ID);
    if (myPose == NULL)return NULL;
    if (OutPose != NULL) {
        delete OutPose;
        OutPose = NULL;
    }
    OutPose = new mPose();
    OutPose->ID = myPose->ID.c_str();
    OutPose->value = myPose->value.c_str();
    for (int i = MyHelper::ChestFrontSlope; i < MyHelper::AnglesCount; i++) {
        OutPose->Accuracy[i] = &(myPose->PoseAngles[static_cast<MyHelper::AnglesID> (i)].accuracy);
        OutPose->Relations[i] = &(myPose->PoseAngles[static_cast<MyHelper::AnglesID> (i)].active);
    }
    return OutPose;
}

extern "C" __declspec(dllexport) KinectEvent*** NewSkeleton(int* NewEvents, int* EndedEvents, Vector3f* mskeleton[MyHelper::JointCount], int mskeletonid) {
    if (BTCH == NULL) return NULL;
    skeleton mySkeleton;
    mySkeleton.TrackingId = mskeletonid;
    int i = 0;
    //conver skeleton
    for (i = MyHelper::HipCenter; i < (int) MyHelper::JointCount; i++) {
        mySkeleton.Joints[static_cast<MyHelper::JointID> (i)] = *mskeleton[i];
    }

    //get new events
    list<KinectEvent> * resault = BTCH->NewSkeleton(mySkeleton,mskeletonid);
    *NewEvents = resault[0].size();
    *EndedEvents = resault[1].size();

    FreeTables();
    //conver event list to array
    results = new KinectEvent**[2];

    // new events
    if (*NewEvents > 0) {
        KinectEvent ** newEvents = new KinectEvent*[*NewEvents];
        i = 0;
        for (list<KinectEvent>::const_iterator iterator = resault[0].begin(), end = resault[0].end(); iterator != end; ++iterator) {
            newEvents[i] = (KinectEvent*) &(* iterator);
            i = i + 1;
        }
        results[0] = newEvents;
    } else results[0] = NULL;


    // ended events
    if (*EndedEvents > 0) {
        KinectEvent ** endedEvents = new KinectEvent*[*EndedEvents];
        i = 0;
        for (list<KinectEvent>::const_iterator iterator = resault[1].begin(), end = resault[1].end(); iterator != end; ++iterator) {
            endedEvents[i] = (KinectEvent*) &(* iterator);
            i = i + 1;
        }
        results[1] = endedEvents;
    } else results[1] = NULL;
    return results;
}

extern "C" __declspec(dllexport) bool AddPose(Vector3f* mskeleton[MyHelper::JointCount], bool Relations[MyHelper::AnglesCount], double Accuracy[MyHelper::AnglesCount], char * PoseID, char * Value, bool replace) {
    if (BTCH == NULL) return false;
    string PoseId = PoseID;
    string value = Value;
    bool result = false;
    skeleton mySkeleton;
    mySkeleton.TrackingId = 1;
    //conver skeleton
    for (int i = MyHelper::HipCenter; i < (int) MyHelper::JointCount; i++) {
        mySkeleton.Joints[static_cast<MyHelper::JointID> (i)] = *mskeleton[i];
    }
    if (replace) BTCH->RemovePoseById(PoseId);
    result = BTCH->AddPose(mySkeleton, PoseId, value, Relations, Accuracy);
    return result;
}

extern "C" __declspec(dllexport) bool DeletePose(const char* PoseID){
 if (BTCH == NULL) return false;
 string PoseId = PoseID;
 return BTCH->RemovePoseById(PoseId);
}

extern "C" __declspec(dllexport) bool UpdatePose(bool Relations[MyHelper::AnglesCount], double Accuracy[MyHelper::AnglesCount], char * PoseID, char * Value) {
    if (BTCH == NULL) return false;
    string PoseId = PoseID;
    string value = Value;
    bool result = false;
    result = BTCH->UpdatePose(PoseId, value, Relations, Accuracy);
    return result;
}

extern "C" __declspec(dllexport) const char** GetPoseList(int* NumOfPose) {
    PosesList& Poses = BTCH->GetPoseList();
    if (poseList != NULL) {
        delete[] poseList;
        poseList = NULL;
    }
    *NumOfPose =Poses.Length();
    poseList = new const char*[*NumOfPose];
    int i =0;
    for (list<Pose>::const_iterator iterator = Poses.begin(), end = Poses.end(); iterator != end; ++iterator) {
      poseList[i] = (((Pose) * iterator).ID).c_str();
      i++;
    }
    return poseList;
}

extern "C" __declspec(dllexport) bool LoadPosesList(const char* Path, bool newList,const char* Key){
    return BTCH->LoadPosesList(Path,newList,Key);
}

extern "C" __declspec(dllexport) bool SavePosesList(const char* Path,const char* Key){
    return BTCH->SavePosesList(Path, Key);
}

extern "C" __declspec(dllexport) bool LoadGesturesList(const char* Path, bool newList,const char* Key){
    return BTCH->LoadGesturesList(Path,newList, Key);
}

extern "C" __declspec(dllexport) bool SaveGesturesList(const char* Path,const char* Key){
    return BTCH->SaveGesturesList(Path, Key);
}

extern "C" __declspec(dllexport) void Release() {
    FreeTables();
    if (OutGesture != NULL) {
        delete OutGesture;
                OutGesture = NULL;
    }
    if (OutPose != NULL) {
        delete OutPose;
                OutPose = NULL;
    }
    if (BTCH == NULL) return;
            BTCH->Release();
            BTCH = NULL;
    }

