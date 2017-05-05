/* 
 * File:   GesturesList.cpp
 * Author: Nicholas Hadjiminas
 * 
 * Created on 17 Ιούνιος 2013, 1:06 μμ
 */

#include "GesturesList.h"


GesturesList::GesturesList() {
}

void GesturesList::Clear() {
    this->Gestures.clear();
}

bool GesturesList::Add(Gesture& myGesture) {
    for (list<Gesture>::const_iterator iterator = Gestures.begin(), end = Gestures.end(); iterator != end; ++iterator) {
        if (((Gesture) * iterator).ID == myGesture.ID) return false;
    }
     Gestures.push_front(myGesture);
     return true;
}

bool GesturesList::RemoveGestureById(string& myGestureId) {

    for (list<Gesture>::iterator iterator = Gestures.begin(), end = Gestures.end(); iterator != end;) {
        if (((Gesture) * iterator).ID == myGestureId) {
            iterator = Gestures.erase(iterator);
            return true;
        } else ++iterator;
    }
    return false;
}

Gesture *GesturesList::GetGestureById(string& myGestureId) {
    for (list<Gesture>::iterator iterator = Gestures.begin(), end = Gestures.end(); iterator != end; ++iterator) {
        if (((Gesture) * iterator).ID == myGestureId) return &(*iterator);
    }
    return NULL;
}

bool GesturesList::Contains(Gesture* myGesture) {
    for (list<Gesture>::iterator iterator = Gestures.begin(), end = Gestures.end(); iterator != end; ++iterator) {
        if ( &(* iterator)== myGesture) return true;
    }
    return false;
}

list<Gesture>::iterator GesturesList::begin(void){
    return Gestures.begin();
}

list<Gesture>::iterator GesturesList::end(void){
    return Gestures.end();
}

unsigned GesturesList::Length(void){
    return Gestures.size();
}

GesturesList::~GesturesList() {
}

