/* 
 * File:   Pose.cpp
 * Author: Nicholas Hadjiminas
 * 
 * Created on 11 Ιανουάριος 2013, 1:00 μμ
 */

#include "Pose.h"

Pose::Pose() {
    //initializ map with empty angles
    for (int i = MyHelper::ChestFrontSlope; i < MyHelper::AnglesCount; i++)PoseAngles[static_cast<MyHelper::AnglesID> (i)];
}


Pose::~Pose() {
    this->PoseAngles.clear();
}

Pose& Pose::operator= (const Pose & other){
        if (this != &other) // protect against invalid self-assignment
        {
          //  deallocate old memory
          this->PoseAngles.clear();
 
          //  assign the new memory to the object
           for (int i = MyHelper::ChestFrontSlope; i < MyHelper::AnglesCount; i++)PoseAngles[static_cast<MyHelper::AnglesID> (i)] = other.PoseAngles.at(static_cast<MyHelper::AnglesID>(i));
        }
        // by convention, always return *this
        return *this;
    }

void Pose::LoadJoins(skeleton& myskeleton ) {

    Vector3f tV;
    Vector3f tV2;
    //Left Arm and Forearm Angles  
    PoseAngles[MyHelper::ArmChestLeft].angle = MyHelper::VectorAngle(myskeleton.Joints[MyHelper::ShoulderLeft], myskeleton.Joints[MyHelper::ElbowLeft], myskeleton.Joints[MyHelper::ShoulderLeft], myskeleton.Joints[MyHelper::HipLeft]);
    PoseAngles[MyHelper::ForearmShouldersLeft].angle = MyHelper::VectorAngle(myskeleton.Joints[MyHelper::ElbowLeft], myskeleton.Joints[MyHelper::WristLeft], myskeleton.Joints[MyHelper::ShoulderLeft], myskeleton.Joints[MyHelper::ShoulderRight]);
    PoseAngles[MyHelper::ArmShoulderLeft].angle = MyHelper::VectorAngle(myskeleton.Joints[MyHelper::ShoulderLeft], myskeleton.Joints[MyHelper::ElbowLeft], myskeleton.Joints[MyHelper::ShoulderLeft], myskeleton.Joints[MyHelper::ShoulderCenter]);
    PoseAngles[MyHelper::ArmForearmLeft].angle = MyHelper::VectorAngle(myskeleton.Joints[MyHelper::ElbowLeft], myskeleton.Joints[MyHelper::ShoulderLeft], myskeleton.Joints[MyHelper::ElbowLeft], myskeleton.Joints[MyHelper::WristLeft]);
    //Right Arm and Forearm Angles  
    PoseAngles[MyHelper::ArmChestRight].angle = MyHelper::VectorAngle(myskeleton.Joints[MyHelper::ShoulderRight], myskeleton.Joints[MyHelper::ElbowRight], myskeleton.Joints[MyHelper::ShoulderRight], myskeleton.Joints[MyHelper::HipRight]);
    PoseAngles[MyHelper::ForearmShouldersRight].angle = MyHelper::VectorAngle(myskeleton.Joints[MyHelper::ElbowRight], myskeleton.Joints[MyHelper::WristRight], myskeleton.Joints[MyHelper::ShoulderRight], myskeleton.Joints[MyHelper::ShoulderLeft]);
    PoseAngles[MyHelper::ArmShoulderRight].angle = MyHelper::VectorAngle(myskeleton.Joints[MyHelper::ShoulderRight], myskeleton.Joints[MyHelper::ElbowRight], myskeleton.Joints[MyHelper::ShoulderRight], myskeleton.Joints[MyHelper::ShoulderCenter]);
    PoseAngles[MyHelper::ArmForearmRight].angle = MyHelper::VectorAngle(myskeleton.Joints[MyHelper::ElbowRight], myskeleton.Joints[MyHelper::ShoulderRight], myskeleton.Joints[MyHelper::ElbowRight], myskeleton.Joints[MyHelper::WristRight]);
    //Left Thing and Leg Angles
    tV.x = myskeleton.Joints[MyHelper::HipLeft].x;
    tV.y = myskeleton.Joints[MyHelper::KneeLeft].y;
    tV.z = myskeleton.Joints[MyHelper::HipLeft].z;
    PoseAngles[MyHelper::ThighRotationLeft].angle = MyHelper::VectorAngle(myskeleton.Joints[MyHelper::HipLeft], tV, myskeleton.Joints[MyHelper::HipLeft], myskeleton.Joints[MyHelper::KneeLeft]);
    PoseAngles[MyHelper::ThighLegLeft].angle = MyHelper::VectorAngle(myskeleton.Joints[MyHelper::KneeLeft], myskeleton.Joints[MyHelper::HipLeft], myskeleton.Joints[MyHelper::KneeLeft], myskeleton.Joints[MyHelper::AnkleLeft]);
    PoseAngles[MyHelper::ThingAbdomenLeft].angle = MyHelper::VectorAngle(myskeleton.Joints[MyHelper::HipLeft], myskeleton.Joints[MyHelper::HipCenter], myskeleton.Joints[MyHelper::HipLeft], myskeleton.Joints[MyHelper::KneeLeft]);
    PoseAngles[MyHelper::LegAbdomenLeft].angle = MyHelper::VectorAngle(myskeleton.Joints[MyHelper::KneeLeft], myskeleton.Joints[MyHelper::AnkleLeft], myskeleton.Joints[MyHelper::HipLeft], myskeleton.Joints[MyHelper::HipRight]);
    //Right Thing and Leg Angles
    tV.x = myskeleton.Joints[MyHelper::HipRight].x;
    tV.y = myskeleton.Joints[MyHelper::KneeRight].y;
    tV.z = myskeleton.Joints[MyHelper::HipRight].z;
    PoseAngles[MyHelper::ThighRotationRight].angle = MyHelper::VectorAngle(myskeleton.Joints[MyHelper::HipRight], tV, myskeleton.Joints[MyHelper::HipRight], myskeleton.Joints[MyHelper::KneeRight]);
    PoseAngles[MyHelper::ThighLegRight].angle = MyHelper::VectorAngle(myskeleton.Joints[MyHelper::KneeRight], myskeleton.Joints[MyHelper::HipRight], myskeleton.Joints[MyHelper::KneeRight], myskeleton.Joints[MyHelper::AnkleRight]);
    PoseAngles[MyHelper::ThingAbdomenRight].angle = MyHelper::VectorAngle(myskeleton.Joints[MyHelper::HipRight], myskeleton.Joints[MyHelper::HipCenter], myskeleton.Joints[MyHelper::HipRight], myskeleton.Joints[MyHelper::KneeRight]);
    PoseAngles[MyHelper::LegAbdomenRight].angle = MyHelper::VectorAngle(myskeleton.Joints[MyHelper::KneeRight], myskeleton.Joints[MyHelper::AnkleRight], myskeleton.Joints[MyHelper::HipRight], myskeleton.Joints[MyHelper::HipRight]);
    //General sides Angles
    tV.x = myskeleton.Joints[MyHelper::ShoulderRight].x;
    tV.y = myskeleton.Joints[MyHelper::Spine].y;
    tV.z = myskeleton.Joints[MyHelper::Spine].z;
    //Chest slope
    PoseAngles[MyHelper::ChestSideSlope].angle = MyHelper::VectorAngle(myskeleton.Joints[MyHelper::Spine], myskeleton.Joints[MyHelper::ShoulderCenter], myskeleton.Joints[MyHelper::Spine], tV);
    tV.x = myskeleton.Joints[MyHelper::ShoulderLeft].x;
    tV.y = myskeleton.Joints[MyHelper::ShoulderRight].y;
    tV.z = myskeleton.Joints[MyHelper::ShoulderRight].z;
    tV2.x = myskeleton.Joints[MyHelper::ShoulderLeft].x;
    tV2.y = myskeleton.Joints[MyHelper::ShoulderRight].y;
    tV2.z = myskeleton.Joints[MyHelper::ShoulderLeft].z;
    //Chest Rotation
    PoseAngles[MyHelper::ChestRotation].angle = MyHelper::VectorAngle(myskeleton.Joints[MyHelper::ShoulderRight], tV, myskeleton.Joints[MyHelper::ShoulderRight], tV2);
    tV.x = myskeleton.Joints[MyHelper::HipCenter].x;
    tV.y = myskeleton.Joints[MyHelper::ShoulderCenter].y;
    tV.z = myskeleton.Joints[MyHelper::HipCenter].z;
    tV2.x = myskeleton.Joints[MyHelper::HipCenter].x;
    tV2.y = myskeleton.Joints[MyHelper::ShoulderCenter].y;
    tV2.z = myskeleton.Joints[MyHelper::ShoulderCenter].z;
    //Chest slope front
    PoseAngles[MyHelper::ChestFrontSlope].angle = MyHelper::VectorAngle(myskeleton.Joints[MyHelper::HipCenter], tV, myskeleton.Joints[MyHelper::HipCenter], tV2);

    //Calulate Direction
    //Left Arm and Forearm Angles  
    PoseAngles[MyHelper::ArmChestLeft].direction = MyHelper::VectorsNormal(myskeleton.Joints[MyHelper::ShoulderLeft], myskeleton.Joints[MyHelper::ElbowLeft], myskeleton.Joints[MyHelper::ShoulderLeft], myskeleton.Joints[MyHelper::HipLeft]);
    PoseAngles[MyHelper::ForearmShouldersLeft].direction = MyHelper::VectorsNormal(myskeleton.Joints[MyHelper::ElbowLeft], myskeleton.Joints[MyHelper::WristLeft], myskeleton.Joints[MyHelper::ShoulderLeft], myskeleton.Joints[MyHelper::ShoulderRight]);
    PoseAngles[MyHelper::ArmShoulderLeft].direction = MyHelper::VectorsNormal(myskeleton.Joints[MyHelper::ShoulderLeft], myskeleton.Joints[MyHelper::ElbowLeft], myskeleton.Joints[MyHelper::ShoulderLeft], myskeleton.Joints[MyHelper::ShoulderCenter]);
    PoseAngles[MyHelper::ArmForearmLeft].direction = MyHelper::VectorsNormal(myskeleton.Joints[MyHelper::ElbowLeft], myskeleton.Joints[MyHelper::ShoulderLeft], myskeleton.Joints[MyHelper::ElbowLeft], myskeleton.Joints[MyHelper::WristLeft]);
    //Right Arm and Forearm Angles  
    PoseAngles[MyHelper::ArmChestRight].direction = MyHelper::VectorsNormal(myskeleton.Joints[MyHelper::ShoulderRight], myskeleton.Joints[MyHelper::ElbowRight], myskeleton.Joints[MyHelper::ShoulderRight], myskeleton.Joints[MyHelper::HipRight]);
    PoseAngles[MyHelper::ForearmShouldersRight].direction = MyHelper::VectorsNormal(myskeleton.Joints[MyHelper::ElbowRight], myskeleton.Joints[MyHelper::WristRight], myskeleton.Joints[MyHelper::ShoulderRight], myskeleton.Joints[MyHelper::ShoulderLeft]);
    PoseAngles[MyHelper::ArmShoulderRight].direction = MyHelper::VectorsNormal(myskeleton.Joints[MyHelper::ShoulderRight], myskeleton.Joints[MyHelper::ElbowRight], myskeleton.Joints[MyHelper::ShoulderRight], myskeleton.Joints[MyHelper::ShoulderCenter]);
    PoseAngles[MyHelper::ArmForearmRight].direction = MyHelper::VectorsNormal(myskeleton.Joints[MyHelper::ElbowRight], myskeleton.Joints[MyHelper::ShoulderRight], myskeleton.Joints[MyHelper::ElbowRight], myskeleton.Joints[MyHelper::WristRight]);
    //Left Thing and Leg Angles
    tV.x = myskeleton.Joints[MyHelper::HipLeft].x;
    tV.y = myskeleton.Joints[MyHelper::KneeLeft].y;
    tV.z = myskeleton.Joints[MyHelper::HipLeft].z;
    PoseAngles[MyHelper::ThighRotationLeft].direction = MyHelper::VectorsNormal(myskeleton.Joints[MyHelper::HipLeft], tV, myskeleton.Joints[MyHelper::HipLeft], myskeleton.Joints[MyHelper::KneeLeft]);
    PoseAngles[MyHelper::ThighLegLeft].direction = MyHelper::VectorsNormal(myskeleton.Joints[MyHelper::KneeLeft], myskeleton.Joints[MyHelper::HipLeft], myskeleton.Joints[MyHelper::KneeLeft], myskeleton.Joints[MyHelper::AnkleLeft]);
    PoseAngles[MyHelper::ThingAbdomenLeft].direction = MyHelper::VectorsNormal(myskeleton.Joints[MyHelper::HipLeft], myskeleton.Joints[MyHelper::HipCenter], myskeleton.Joints[MyHelper::HipLeft], myskeleton.Joints[MyHelper::KneeLeft]);
    PoseAngles[MyHelper::LegAbdomenLeft].direction = MyHelper::VectorsNormal(myskeleton.Joints[MyHelper::KneeLeft], myskeleton.Joints[MyHelper::AnkleLeft], myskeleton.Joints[MyHelper::HipLeft], myskeleton.Joints[MyHelper::HipRight]);
    //Right Thing and Leg Angles
    tV.x = myskeleton.Joints[MyHelper::HipRight].x;
    tV.y = myskeleton.Joints[MyHelper::KneeRight].y;
    tV.z = myskeleton.Joints[MyHelper::HipRight].z;
    PoseAngles[MyHelper::ThighRotationRight].direction = MyHelper::VectorsNormal(myskeleton.Joints[MyHelper::HipRight], tV, myskeleton.Joints[MyHelper::HipRight], myskeleton.Joints[MyHelper::KneeRight]);
    PoseAngles[MyHelper::ThighLegRight].direction = MyHelper::VectorsNormal(myskeleton.Joints[MyHelper::KneeRight], myskeleton.Joints[MyHelper::HipRight], myskeleton.Joints[MyHelper::KneeRight], myskeleton.Joints[MyHelper::AnkleRight]);
    PoseAngles[MyHelper::ThingAbdomenRight].direction = MyHelper::VectorsNormal(myskeleton.Joints[MyHelper::HipRight], myskeleton.Joints[MyHelper::HipCenter], myskeleton.Joints[MyHelper::HipRight], myskeleton.Joints[MyHelper::KneeRight]);
    PoseAngles[MyHelper::LegAbdomenRight].direction = MyHelper::VectorsNormal(myskeleton.Joints[MyHelper::KneeRight], myskeleton.Joints[MyHelper::AnkleRight], myskeleton.Joints[MyHelper::HipRight], myskeleton.Joints[MyHelper::HipRight]);
    //General sides Angles
    tV.x = myskeleton.Joints[MyHelper::ShoulderRight].x;
    tV.y = myskeleton.Joints[MyHelper::Spine].y;
    tV.z = myskeleton.Joints[MyHelper::Spine].z;
    //chest slope
    PoseAngles[MyHelper::ChestSideSlope].direction = MyHelper::VectorsNormal(myskeleton.Joints[MyHelper::Spine], myskeleton.Joints[MyHelper::ShoulderCenter], myskeleton.Joints[MyHelper::Spine], tV);
    tV.x = myskeleton.Joints[MyHelper::ShoulderLeft].x;
    tV.y = myskeleton.Joints[MyHelper::ShoulderRight].y;
    tV.z = myskeleton.Joints[MyHelper::ShoulderRight].z;
    tV2.x = myskeleton.Joints[MyHelper::ShoulderLeft].x;
    tV2.y = myskeleton.Joints[MyHelper::ShoulderRight].y;
    tV2.z = myskeleton.Joints[MyHelper::ShoulderLeft].z;
    //chest rotation
    PoseAngles[MyHelper::ChestRotation].direction = MyHelper::VectorsNormal(myskeleton.Joints[MyHelper::ShoulderRight], tV, myskeleton.Joints[MyHelper::ShoulderRight], tV2);
    tV.x = myskeleton.Joints[MyHelper::HipCenter].x;
    tV.y = myskeleton.Joints[MyHelper::ShoulderCenter].y;
    tV.z = myskeleton.Joints[MyHelper::HipCenter].z;
    tV2.x = myskeleton.Joints[MyHelper::HipCenter].x;
    tV2.y = myskeleton.Joints[MyHelper::ShoulderCenter].y;
    tV2.z = myskeleton.Joints[MyHelper::ShoulderCenter].z;
    //Chest slope front
    PoseAngles[MyHelper::ChestFrontSlope].direction = MyHelper::VectorsNormal(myskeleton.Joints[MyHelper::HipCenter], tV, myskeleton.Joints[MyHelper::HipCenter], tV2);
}

void Pose::LoadRelations(bool Relations[MyHelper::AnglesCount], double Accuracy[MyHelper::AnglesCount]){
    for (int i = MyHelper::ChestFrontSlope; i < MyHelper::AnglesCount; i++){
        PoseAngles[static_cast<MyHelper::AnglesID> (i)].accuracy = Accuracy[i];
        PoseAngles[static_cast<MyHelper::AnglesID> (i)].active = Relations[i]; 
    }
}
