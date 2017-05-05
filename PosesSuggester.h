/* 
 * File:   PosesSuggester.h
 * Author: Nicholas Hadjiminas
 *
 * Created on 21 Ιούνιος 2013, 9:31 πμ
 */

#ifndef POSESSUGGESTER_H
#define	POSESSUGGESTER_H

#include "Pose.h"
#include "skeleton.h"
#include "MyHelper.h"

class PosesSuggester {
public:
    int PoseAnglesChanges[MyHelper::AnglesCount];
    PosesSuggester();
    int * CompareNewPose(skeleton& CurenSkeleton,int SkeletonId);
    void Reset();
    void NewBasePose(Pose& orig);
    virtual ~PosesSuggester();
private:
    Pose BasePose;

};

#endif	/* POSESSUGGESTER_H */

