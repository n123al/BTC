/* 
 * File:   GesturesList.h
 * Author: Nicholas Hadjiminas
 *
 * Created on 17 Ιούνιος 2013, 1:06 μμ
 */

#ifndef GESTURESLIST_H
#define	GESTURESLIST_H

#include <iostream>
#include <list>

#include "Gesture.h"



using namespace std;

class GesturesList {
public:
    GesturesList();
    void Clear();
    bool Add(Gesture& myGesture);
    bool RemoveGestureById(string& myGestureId);
    Gesture *GetGestureById(string& GestureId);
    bool Contains(Gesture* myGesture);
    list<Gesture>::iterator begin(void);
    list<Gesture>::iterator end(void);
    unsigned Length(void);
    virtual ~GesturesList();
private:
    list <Gesture> Gestures;

};

#endif	/* GESTURESLIST_H */

