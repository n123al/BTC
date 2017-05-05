/* 
 * File:   Timer.h
 * Author: Nicholas Hadjiminas
 *
 * Created on 29 Ιανουάριος 2013, 8:59 πμ
 */

#ifndef TIMER_H
#define	TIMER_H
#include <ctime>
class Timer {
public:
    Timer();
    void Start();
    bool IsValid() ;
    double GetDuration();
    void Reset();
    virtual ~Timer();
private:
        time_t  StartDateTime;
        bool valid;

};

#endif	/* TIMER_H */

