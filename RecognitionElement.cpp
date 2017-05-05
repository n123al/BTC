/* 
 * File:   RecognitionElement.cpp
 * Author: Nicholas Hadjiminas
 * 
 * Created on 11 Ιανουάριος 2013, 12:24 μμ
 */

#include "RecognitionElement.h"
RecognitionElement::RecognitionElement(){}

RecognitionElement::RecognitionElement(string &Id, string &Value, Timer &Time){
 this->ID= Id;
 this->value = Value;
 this->time = Time;
}