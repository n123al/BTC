/* 
 * File:   Gesture.h
 * Author: Nicholas Hadjiminas
 *
 * Created on 17 Ιούνιος 2013, 12:48 μμ
 */

#ifndef GESTURE_H
#define	GESTURE_H

#include "RecognitionElement.h"

class Gesture : public RecognitionElement {
public:
    string StartPose;
    bool FoundStart ;
    string EndPose;
    double EndPoseHold ;
    bool FoundEnd ;
    string Voice ;
    bool FoundVoice ;
    float MaxDuration ;
    
    Gesture();
    Gesture& operator= (const Gesture & other);
    bool Valid();
    void StartGuesture();
    void ResetGuseture();
    virtual ~Gesture();
private:

};

#endif	/* GESTURE_H */

