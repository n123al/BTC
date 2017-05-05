/* 
 * File:   Events.h
 * Author: Nicholas Hadjiminas
 *
 * Created on October 25, 2013, 1:53 PM
 */

#ifndef EVENTS_H
#define	EVENTS_H

class Events {
public:

    enum KEvents {
        pose = 0,
        gesture = 1,
        spech = 2,
    };
};

class KinectEvent {
public:
    Events::KEvents Type;
    std::string Value;
    std::string ID;
    int SkeletonId;
};


#endif	/* EVENTS_H */

