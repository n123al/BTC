/* 
 * File:   PosesList.cpp
 * Author: Nicholas Hadjiminas
 * 
 * Created on 18 Ιούνιος 2013, 10:15 πμ
 */

#include "PosesList.h"

PosesList::PosesList() {
}

void PosesList::Clear() {
    this->Poses.clear();
}

bool PosesList::Add(Pose& myPose) {
    for (list<Pose>::const_iterator iterator = Poses.begin(), end = Poses.end(); iterator != end; ++iterator) {
        if (((Pose) * iterator).ID == myPose.ID) return false;
    }
    Poses.push_front(myPose);
    return true;
}

bool PosesList::RemovePoseById(string& myPoseId) {

    for (list<Pose>::iterator iterator = Poses.begin(), end = Poses.end(); iterator != end;) {
        if (((Pose) * iterator).ID == myPoseId) {
            iterator = Poses.erase(iterator);
            return true;
        } else ++iterator;
    }
    return false;
}

Pose *PosesList::GetPoseById(string& myPoseId) {
    for (list<Pose>::iterator iterator = Poses.begin(), end = Poses.end(); iterator != end; ++iterator) {
        if (((Pose) * iterator).ID == myPoseId) return &(*iterator);
    }
    return NULL;
}

bool PosesList::Contains(Pose* myPose) {
    for (list<Pose>::iterator iterator = Poses.begin(), end = Poses.end(); iterator != end; ++iterator) {
        if (&(* iterator) == myPose) return true;
    }
    return false;
}

bool PosesList::RemovePose(Pose* myPose) {

    for (list<Pose>::iterator iterator = Poses.begin(), end = Poses.end(); iterator != end;) {
        if (&(* iterator) == myPose) {
            iterator = Poses.erase(iterator);
            return true;
        } else ++iterator;
    }
    return false;
}

list<Pose>::iterator PosesList::begin(void) {
    return Poses.begin();
}

list<Pose>::iterator PosesList::end(void) {
    return Poses.end();
}

unsigned PosesList::Length(void) {
    return Poses.size();
}

PosesList::~PosesList() {
}

