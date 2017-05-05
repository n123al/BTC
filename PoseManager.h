/* 
 * File:   PoseManager.h
 * Author: Nicholas Hadjiminas
 *
 * Created on 18 Ιούνιος 2013, 11:24 πμ
 */

#ifndef POSEMANAGER_H
#define	POSEMANAGER_H

#include "MyHelper.h"
#include "vmath.h"
#include "Pose.h"


class PoseManager {
public:
    PoseManager();
    bool ComparePoses(Pose& StorePose, Pose& CurrentPose);
   
    virtual ~PoseManager();
private:

};

#endif	/* POSEMANAGER_H */

