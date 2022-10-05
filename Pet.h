#pragma once
#include "BaseApplication.h"
#include "reader_data.h"

using namespace Ogre;

#define PI 3.141592654

class Pet
{
public:
    Pet(void);
    ~Pet(void);
    void rotate(const Real&, Pet*);
public:
    SceneNode* mSceneNode;
    Entity* mEntity;
    Vector3 mVelocity;
    Real mRotationRadius;
    Real mAngle;
    Real mAngularSpeed;
    Real mAngularAcc;
    Real mMaxAngularSpeed;
    bool mActivated;
};