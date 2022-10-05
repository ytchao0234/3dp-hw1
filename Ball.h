#pragma once
#include "BaseApplication.h"
#include "reader_data.h"
#include "Pet.h"

using namespace Ogre;

class Ball
{
public:
    Ball(void);
    ~Ball(void);
    void setVelocity(Pet*);
    void projectile(const Real&);
public:
    SceneNode* mSceneNode;
    Entity* mEntity;
    Vector3 mVelocity;
    Vector3 mAcceleration;
    bool mActivated;
    Real mTime;
    Real mTimeLimit;
};