#pragma once
#include "Pet.h"

using namespace Ogre;

Pet::Pet(void):
    mSceneNode(nullptr),
    mEntity(nullptr),
    mVelocity(Vector3::ZERO),
    mActivate(false)
{

}

Pet::~Pet(void)
{

}

void Pet::translate(const Real& dt)
{
    if (!mSceneNode) return;

    Vector3 position = mSceneNode->getPosition();
    position += dt * mVelocity;
    mSceneNode->setPosition(position);
}