/* 
 * File:   Gesture.cpp
 * Author: Nicholas Hadjiminas
 * 
 * Created on 17 Ιούνιος 2013, 12:48 μμ
 */

#include "Gesture.h"

Gesture::Gesture() {
    FoundStart = false;
    EndPoseHold = 0.0;
    FoundEnd = false;
    Voice = "NVE";
    FoundVoice = true;
    MaxDuration = 0.0f;
}

Gesture& Gesture::operator=(const Gesture & other) {
    if (this != &other) // protect against invalid self-assignment
    {
        FoundStart = other.FoundStart;
        EndPoseHold = other.EndPoseHold;
        FoundEnd = other.FoundEnd;
        Voice = other.Voice;
        FoundVoice = other.FoundVoice;
        MaxDuration = other.MaxDuration;
        StartPose = other.StartPose;
        EndPose=other.EndPose; 
    }
    // by convention, always return *this
    return *this;
}

bool Gesture::Valid() {
    if ((MaxDuration == 0.0f)) return true;
    float t;
    t = time.GetDuration();
    if (time.GetDuration() > MaxDuration) return false;
    else return true;
}

void Gesture::StartGuesture() {
    time.Start();
}

void Gesture::ResetGuseture() {
    FoundEnd = false;
    FoundStart = false;
    if (Voice != "NVE")FoundVoice = false;
    time.Reset();
}

Gesture::~Gesture() {
}

