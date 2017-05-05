/* 
 * File:   RecognitionElement.h
 * Author: Nicholas Hadjiminas
 *
 * Created on 11 Ιανουάριος 2013, 12:24 μμ
 */

#ifndef RECOGNITIONELEMENT_H
#define	RECOGNITIONELEMENT_H
#include <iostream>

#include "Timer.h"

using namespace std;
class RecognitionElement {

public:
RecognitionElement(string &Id, string &Value, Timer &Time);
string ID;
string value;
Timer time;

protected:
RecognitionElement();

};

#endif	/* RECOGNITIONELEMENT_H */

