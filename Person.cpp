/* 
 * File:   Person.cpp
 * Author: Nicholas Hadjiminas
 * 
 * Created on October 25, 2013, 1:50 PM
 */

#include "Person.h"

void Person::NewSkeleton(skeleton& mySkeleton, PosesList& posesList, GesturesList& gesturesList) {
    PosesList TempPoses;
    //report error
    if (Pskeleton.TrackingId != mySkeleton.TrackingId)return;

    //copy skeleton
    for (int i = MyHelper::HipCenter; i < (int) MyHelper::JointCount; i++)Pskeleton.Joints[static_cast<MyHelper::JointID> (i)] = mySkeleton.Joints[static_cast<MyHelper::JointID> (i)];

    CurentPose.LoadJoins(this->Pskeleton);
    CurentEndEvents.clear();
    CurentEvents.clear();
    TempPoses = recognisedPoses;
    recognisedPoses.Clear();

    //check for pose recognition 
    for (list<Pose>::iterator iterator = posesList.begin(), end = posesList.end(); iterator != end; ++iterator) {
        Pose& pose = *iterator;
        if (pm.ComparePoses(pose, CurentPose)) {
            recognisedPoses.Add(pose);
            //Announce the pose that Been Recognized
            KinectEvent tempevent;
            tempevent.Type = Events::pose;
            tempevent.Value = pose.value;
            tempevent.ID = pose.ID;
            tempevent.SkeletonId = Pskeleton.TrackingId;
            CurentEvents.push_front(tempevent);
            if ((TempPoses.GetPoseById(pose.ID)) != NULL) {
                TempPoses.RemovePoseById(pose.ID);
            } else {
                pose.time.Start();
            }
        }
    }
    //Announce the pose that stop Been Recognized
    if (TempPoses.Length() > 0) {
        for (list<Pose>::iterator iterator = TempPoses.begin(), end = TempPoses.end(); iterator != end; ++iterator) {
            Pose& pose = *iterator;
            KinectEvent tempevent;
            tempevent.Type = Events::pose;
            tempevent.Value = pose.value;
            tempevent.ID = pose.ID;
            tempevent.SkeletonId = Pskeleton.TrackingId;
            CurentEndEvents.push_front(tempevent);
        }
    }

    // If We recognize some poses
    if (recognisedPoses.Length() > 0) {
        //Check if any of the poses starts any gesture
        for (list<Gesture>::iterator iterator = gesturesList.begin(), end = gesturesList.end(); iterator != end; ++iterator) {
            Gesture& gesture = *iterator;
            for (list<Pose>::iterator iterator = recognisedPoses.begin(), end = recognisedPoses.end(); iterator != end; ++iterator) {
                Pose& pose = *iterator;
                if (pose.ID == gesture.StartPose) {
                    gesture.FoundStart = true;
                    gesture.StartGuesture();
                    ActiveGestureslist.Add(gesture);

                }
            }
        }

        //Check if any of the poses ends any gesture
        for (list<Gesture>::iterator iterator = ActiveGestureslist.begin(), end = ActiveGestureslist.end(); iterator != end; ++iterator) {
            Gesture& gesture = *iterator;
            if (gesture.Valid()) {
                for (list<Pose>::iterator iterator = recognisedPoses.begin(), end = recognisedPoses.end(); iterator != end; ++iterator) {
                    Pose& pose = *iterator;
                    if ((pose.ID == gesture.EndPose) &&(pose.time.GetDuration() > gesture.EndPoseHold)) {
                        gesture.FoundEnd = true;
                        if (gesture.FoundEnd && gesture.FoundStart && gesture.FoundVoice) {
                            // Add the event
                            KinectEvent tempevent;
                            tempevent.Type = Events::gesture;
                            tempevent.Value = gesture.value;
                            tempevent.ID = gesture.ID;
                            tempevent.SkeletonId = Pskeleton.TrackingId;
                            CurentEvents.push_front(tempevent);
                            ActiveGestureslist.RemoveGestureById(gesture.ID);
                        }
                    }
                }

            } else {
                // Add the event
                KinectEvent tempevent;
                tempevent.Type = Events::gesture;
                tempevent.Value = gesture.value;
                tempevent.ID = gesture.ID;
                tempevent.SkeletonId = Pskeleton.TrackingId;
                CurentEndEvents.push_front(tempevent);
                gesture.ResetGuseture();
                ActiveGestureslist.RemoveGestureById(gesture.ID);
            }
        }
    } else {

        for (list<Gesture>::iterator iterator = ActiveGestureslist.begin(), end = ActiveGestureslist.end(); iterator != end; ++iterator) {
            Gesture& gesture = *iterator;
            if (!gesture.Valid()) {
                // Add the event
                KinectEvent tempevent;
                tempevent.Type = Events::gesture;
                tempevent.Value = gesture.value;
                tempevent.ID = gesture.ID;
                tempevent.SkeletonId = Pskeleton.TrackingId;
                CurentEndEvents.push_front(tempevent);
                gesture.ResetGuseture();
                ActiveGestureslist.RemoveGestureById(gesture.ID);
            }

        }
        this->time.Reset();
    }
}

void Person::NewVoice(string &voice, int skeltonId) {
     if (Pskeleton.TrackingId != skeltonId)return;
    for (list<Gesture>::iterator iterator = ActiveGestureslist.begin(), end = ActiveGestureslist.end(); iterator != end; ++iterator) {
        Gesture& gesture = *iterator;
        if (gesture.Valid()) {
            // throw error 
            if( gesture.Voice.empty() || voice.empty() ) return;
            transform(gesture.Voice.begin(), gesture.Voice.end(), gesture.Voice.begin(), std::ptr_fun<int, int>(std::tolower));
            transform(voice.begin(), voice.end(), voice.begin(), std::ptr_fun<int, int>(std::tolower));
                if (gesture.Voice.compare(voice)==0)  {
                        gesture.FoundVoice = true;
                        if (gesture.FoundEnd && gesture.FoundStart && gesture.FoundVoice) {
                            // Add the event
                            KinectEvent tempevent;
                            tempevent.Type = Events::gesture;
                            tempevent.Value = gesture.value;
                            tempevent.ID = gesture.ID;
                            tempevent.SkeletonId = Pskeleton.TrackingId;
                            CurentEvents.push_front(tempevent);
                            ActiveGestureslist.RemoveGestureById(gesture.ID);
                        }
                    }
        } else {
            // Add the event
            KinectEvent tempevent;
            tempevent.Type = Events::gesture;
            tempevent.Value = gesture.value;
            tempevent.ID = gesture.ID;
            tempevent.SkeletonId = Pskeleton.TrackingId;
            CurentEndEvents.push_front(tempevent);
            gesture.ResetGuseture();
            ActiveGestureslist.RemoveGestureById(gesture.ID);
        }
    }
}

const Vector3f &Person::GetJointPosition(MyHelper::JointID joint){
  return Pskeleton.Joints[joint];
}

void Person::SetSkeleton(skeleton& mySkeleton) {
    this->Pskeleton.TrackingId = mySkeleton.TrackingId;
    this->time.Start();
    for (int i = MyHelper::HipCenter; i < (int) MyHelper::JointCount; i++)Pskeleton.Joints[static_cast<MyHelper::JointID> (i)] = mySkeleton.Joints[static_cast<MyHelper::JointID> (i)];
}

bool Person::IsValid() {
    if(this->time.GetDuration()> 100.00)return false;
    else return true;
}

int Person::GetSkeletonID() {
    return this->Pskeleton.TrackingId;
}

Person::Person() {
}

Person::~Person() {
}

