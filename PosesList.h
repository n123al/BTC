/* 
 * File:   PosesList.h
 * Author: Nicholas Hadjiminas
 *
 * Created on 18 Ιούνιος 2013, 10:15 πμ
 */

#ifndef POSESLIST_H
#define	POSESLIST_H

#include <iostream>
#include <list>

#include "Pose.h"

class PosesList {
public:
    PosesList();
    void Clear();
    bool Add(Pose& myPose);
    bool RemovePoseById(string& myPoseId);
    bool RemovePose(Pose* myPose);
    list<Pose>::iterator begin(void);
    list<Pose>::iterator end(void);
    Pose *GetPoseById(string& myPoseId);
    unsigned Length(void);
    bool Contains(Pose* myPose);
    virtual ~PosesList();
//private:
    list <Pose> Poses;


};

#endif	/* POSESLIST_H */

