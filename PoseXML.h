/* 
 * File:   PoseXML.h
 * Author: Nicholas Hadjiminas
 *
 * Created on July 26, 2013, 11:28 AM
 */

#ifndef POSEXML_H
#define	POSEXML_H

#include <stdio.h>
#include <fstream>

#include "RunTime.h"
#include "pugixml.hpp"
#include "GeneralHelper.h"
#include "Encrypt.h"

class PoseXML {
public:
    PoseXML();
    bool SavePosesList(PosesList & Poses, const string & file , const string & key);
    bool LoadPosesList(PosesList & Poses, const string & file , const string & key);
    virtual ~PoseXML();
private:

};

#endif	/* POSEXML_H */

