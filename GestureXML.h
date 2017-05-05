/* 
 * File:   GestureXML.h
 * Author: Nicholas Hadjiminas
 *
 * Created on July 25, 2013, 11:11 AM
 */

#ifndef GESTUREXML_H
#define	GESTUREXML_H

#include <fstream>
#include <stdio.h>

#include "RunTime.h"
#include "pugixml.hpp"
#include "GeneralHelper.h"
#include "Encrypt.h"

class GestureXML {
public:
    GestureXML();
    bool SaveGesturesList(GesturesList & Gestures,  const string & file , const string & key );
    bool LoadGesturesList(GesturesList & Gestures,  const string & file , const string & key );
    virtual ~GestureXML();
private:

};

#endif	/* GESTUREXML_H */

