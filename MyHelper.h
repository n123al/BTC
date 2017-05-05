/* 
 * File:   MyHelper.h
 * Author: Nicholas Hadjiminas
 *
 * Created on 18 Ιανουάριος 2013, 10:04 πμ
 */

#ifndef MYHELPER_H
#define	MYHELPER_H

#include "vmath.h"

class MyHelper {
public:
    enum AnglesID {
        ChestFrontSlope = 0,
        ForearmShouldersLeft = 1,
        ArmForearmLeft = 2,
        ArmChestLeft = 3,
        ChestRotation = 4,
        ChestSideSlope = 5,
        ThingAbdomenLeft = 6,
        ThighLegLeft = 7,
        ThighRotationLeft = 8,
        ArmShoulderLeft = 9,
        LegAbdomenLeft = 10,
        ForearmShouldersRight = 11,
        ArmForearmRight = 12,
        ArmChestRight = 13,
        ArmShoulderRight = 14,
        ThingAbdomenRight = 15,
        ThighLegRight = 16,
        ThighRotationRight = 17,
        LegAbdomenRight = 18,
        AnglesCount = 19,
    };

    enum JointID {
        HipCenter = 0,
        Spine = 1,
        ShoulderCenter = 2,
        Head = 3,
        ShoulderLeft = 4,
        ElbowLeft = 5,
        WristLeft = 6,
        HandLeft = 7,
        ShoulderRight = 8,
        ElbowRight = 9,
        WristRight = 10,
        HandRight = 11,
        HipLeft = 12,
        KneeLeft = 13,
        AnkleLeft = 14,
        FootLeft = 15,
        HipRight = 16,
        KneeRight = 17,
        AnkleRight = 18,
        FootRight = 19,
        JointCount = 20,
    };

    template <typename T> T static CLAMP(const T& value, const T& low, const T& high);

    /// <summary>
    /// Calculates the angle between two vectors 
    /// </summary>
    /// <param name="StartVector1"></param>
    /// <param name="EndVector1"></param>
    /// <param name="StartVector2"></param>
    /// <param name="EndVector2"></param>
    /// <returns></returns>
    static double VectorAngle(Vector3f& StartVector1, Vector3f& EndVector1, Vector3f& StartVector2, Vector3f& EndVector2);

    /// <summary>
    /// Calculates the normal of the surface created by the two vectors 
    /// </summary>
    /// <param name="StartVector1"></param>
    /// <param name="EndVector1"></param>
    /// <param name="StartVector2"></param>
    /// <param name="EndVector2"></param>
    /// <returns></returns>
    static Vector3f VectorsNormal(Vector3f& StartVector1, Vector3f& EndVector1, Vector3f& StartVector2, Vector3f& EndVector2);
    };

#endif	/* MYHELPER_H */

