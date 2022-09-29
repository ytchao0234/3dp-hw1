#pragma once
#include "BaseApplication.h"

using namespace Ogre;

class Pet
{
public:
    Pet(void);
    ~Pet(void);
    void translate(const Real&);
public:
    SceneNode* mSceneNode;
    Entity* mEntity;
    Vector3 mVelocity;
    bool mActivate;
};