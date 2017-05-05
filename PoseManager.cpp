/* 
 * File:   PoseManager.cpp
 * Author: Nicholas Hadjiminas
 * 
 * Created on 18 Ιούνιος 2013, 11:24 πμ
 */

#include "PoseManager.h"
#include <fstream>


PoseManager::PoseManager() {
}
template <typename T> string tostr(const T& t) {
    ostringstream os;
    os << t;
    return os.str();
}

 bool PoseManager::ComparePoses(Pose& StorePose, Pose& CurrentPose)
        {
            bool match = false;
            double variation;
            //na fio 
           // return true;
            for (int i = 0; i < (int)MyHelper::AnglesCount; i++)
            {
                if (StorePose.PoseAngles[static_cast<MyHelper::AnglesID> (i)].active)
                {
                    //Coverts the variation percentage to degrees   
                    variation = (StorePose.PoseAngles[static_cast<MyHelper::AnglesID>(i)].accuracy / 100) * (M_PI / 2);
 
                    //Compare an angle
                    if (((StorePose.PoseAngles[static_cast<MyHelper::AnglesID>(i)].angle >= CurrentPose.PoseAngles[static_cast<MyHelper::AnglesID>(i)].angle) && (StorePose.PoseAngles[static_cast<MyHelper::AnglesID>(i)].angle <= CurrentPose.PoseAngles[static_cast<MyHelper::AnglesID>(i)].angle + (variation))) || ((StorePose.PoseAngles[static_cast<MyHelper::AnglesID>(i)].angle <= CurrentPose.PoseAngles[static_cast<MyHelper::AnglesID>(i)].angle) && (StorePose.PoseAngles[static_cast<MyHelper::AnglesID>(i)].angle >= CurrentPose.PoseAngles[static_cast<MyHelper::AnglesID>(i)].angle - (variation))))
                    {
                        if (fabs(StorePose.PoseAngles[static_cast<MyHelper::AnglesID>(i)].angle) > variation)
                        {
                        ofstream myfile;
                        string s = tostr<float> (StorePose.PoseAngles[static_cast<MyHelper::AnglesID>(i)].angle);
                        string ss = tostr<float> (CurrentPose.PoseAngles[static_cast<MyHelper::AnglesID>(i)].angle);
                        string sss = tostr<double> (variation);
                            //Compare the direction of the angle
                           float d = StorePose.PoseAngles[static_cast<MyHelper::AnglesID>(i)].direction.dotProduct(CurrentPose.PoseAngles[static_cast<MyHelper::AnglesID>(i)].direction);
                            if (d >= 0) match = true;
                            else return false;
                        }
                        else match = true;
                    }
                    else return false;
                }
            }
            return match;
        }

PoseManager::~PoseManager() {
}

