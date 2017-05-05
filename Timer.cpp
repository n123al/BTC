/* 
 * File:   Timer.cpp
 * Author: Nicholas Hadjiminas
 * 
 * Created on 29 Ιανουάριος 2013, 8:59 πμ
 */
#include "Timer.h"

Timer::Timer(){
    StartDateTime = 0;
    valid = false;
}
void Timer::Start(){
       StartDateTime = time(0);
       valid = true;
}

bool Timer::IsValid(){
        return valid;
}

double Timer::GetDuration(){
            if (!valid) return -1.0f;
            float Duration = difftime (time(0),StartDateTime);
            return Duration;
}
void Timer::Reset(){
 StartDateTime = 0;
}
Timer::~Timer() {
}

