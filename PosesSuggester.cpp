/* 
 * File:   PosesSuggester.cpp
 * Author: Nicholas Hadjiminas
 * 
 * Created on 21 Ιούνιος 2013, 9:31 πμ
 */

#include "PosesSuggester.h"

PosesSuggester::PosesSuggester() {
    Reset();
}

void PosesSuggester::NewBasePose(Pose& orig) {
 BasePose = orig;
}

int * PosesSuggester::CompareNewPose(skeleton& CurenSkeleton,int SkeletonId){
    Pose Tpose;
    Tpose.LoadJoins(CurenSkeleton);
    double variation;
    for (int i = 0; i < (int)MyHelper::AnglesCount; i++)
            {
                if (BasePose.PoseAngles[static_cast<MyHelper::AnglesID> (i)].active)
                {
                    //Coverts the variation percentage to degrees   
                    variation = (BasePose.PoseAngles[static_cast<MyHelper::AnglesID>(i)].accuracy / 100) * (M_PI / 2);
                    //Compare an angle
                    if (((BasePose.PoseAngles[static_cast<MyHelper::AnglesID>(i)].angle >= Tpose.PoseAngles[static_cast<MyHelper::AnglesID>(i)].angle) && (BasePose.PoseAngles[static_cast<MyHelper::AnglesID>(i)].angle <= Tpose.PoseAngles[static_cast<MyHelper::AnglesID>(i)].angle + (variation))) || ((BasePose.PoseAngles[static_cast<MyHelper::AnglesID>(i)].angle <= Tpose.PoseAngles[static_cast<MyHelper::AnglesID>(i)].angle) && (BasePose.PoseAngles[static_cast<MyHelper::AnglesID>(i)].angle >= Tpose.PoseAngles[static_cast<MyHelper::AnglesID>(i)].angle - (variation))))
                    {
                        if (fabs(BasePose.PoseAngles[static_cast<MyHelper::AnglesID>(i)].angle) > variation)
                        {
                            //Compare the direction of the angle
                           float d = BasePose.PoseAngles[static_cast<MyHelper::AnglesID>(i)].direction.dotProduct(Tpose.PoseAngles[static_cast<MyHelper::AnglesID>(i)].direction);
                            if (d >= 0) PoseAnglesChanges[i]++;
                        }
                    }
                    else
                   {   
                        // count changes
                        PoseAnglesChanges[i]++;
                    }
                }
            }
            return PoseAnglesChanges;
            
    
}

void PosesSuggester::Reset(){
    for(int i=0;i<MyHelper::AnglesCount;i++){
    PoseAnglesChanges[i]=0;
    }
}

PosesSuggester::~PosesSuggester() {
}

