#pragma once
#include "Ball.h"

using namespace Ogre;

Ball::Ball(void):
    mSceneNode(nullptr),
    mEntity(nullptr),
    mVelocity(Vector3(0.0, 50.0, 0.0)),
    mAcceleration(Vector3(0.0, -10.0, 0.0)),
    mActivated(false),
    mTime(0.0),
    mTimeLimit(5.0)
{

}

Ball::~Ball(void)
{

}

void Ball::setVelocity(Pet* target)
{
    Vector3 p0 = target->mSceneNode->getPosition();
    Vector3 p1 = mSceneNode->getPosition();
    Real speed = 30.0;

    mVelocity = speed * (p0 - p1) / p0.distance(p1);
    mVelocity.y = 50.0;
}

void Ball::projectile(const Real& dt)
{
    if (!mSceneNode || !mActivated) return;

    if (mTime >= mTimeLimit)
        mActivated = false;
    else 
        mTime += dt;

    Real speed = 3.0;

    Vector3 p = mSceneNode->getPosition();
    mVelocity += speed * dt * mAcceleration;
    p += speed * dt * mVelocity;

    mSceneNode->setPosition(p);
}