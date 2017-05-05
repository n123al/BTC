/* 
 * File:   skeleton.h
 * Author: Nicholas Hadjiminas
 *
 * Created on 13 Φεβρουάριος 2013, 1:09 μμ
 */

#ifndef SKELETON_H
#define	SKELETON_H

#include <map>

#include "MyHelper.h"
#include "vmath.h"

using namespace std;


class skeleton {
public:
    skeleton();
    skeleton(const skeleton& orig);
    
    int TrackingId;
    map<MyHelper::JointID,Vector3f> Joints;
private:

};

#endif	/* SKELETON_H */

