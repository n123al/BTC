/* 
 * File:   skeleton.cpp
 * Author: Nicholas Hadjiminas
 * 
 * Created on 13 Φεβρουάριος 2013, 1:09 μμ
 */

#include "skeleton.h"


skeleton::skeleton() {
    for(int i= MyHelper::HipCenter ;i<(int)MyHelper::JointCount;i++)this->Joints[static_cast<MyHelper::JointID>(i)] ;
}

skeleton::skeleton(const skeleton& orig) {
    map<MyHelper::JointID,Vector3f>::const_iterator it;
    for(int i= MyHelper::HipCenter ;i<(int)MyHelper::JointCount;i++){
        it = orig.Joints.find(static_cast<MyHelper::JointID>(i));
        if(it != orig.Joints.end())
        this->Joints[static_cast<MyHelper::JointID>(i)] = it->second;
    }
}


