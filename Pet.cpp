#pragma once
#include "Pet.h"

using namespace Ogre;

Pet::Pet(void):
    mSceneNode(nullptr),
    mEntity(nullptr),
    mVelocity(Vector3::ZERO),
    mRotationRadius(0.0),
    mTheta(0.0),
    mAngularSpeed(0.0),
    mAngularAcc(0.01),
    mActivated(true)
{

}

Pet::~Pet(void)
{

}

void Pet::rotate(const Real& dt, Pet*& target)
{
    if (!mSceneNode || !mActivated) return;

    mTheta += mAngularSpeed;

    if (mTheta < 0.0 && mAngularAcc < 0.0 ||
        mTheta > 2.0 * PI && mAngularAcc > 0.0)
    {  
        mAngularSpeed = 0;
        mAngularAcc = -mAngularAcc;
    }
    mAngularSpeed += mAngularAcc * dt;

    double x = mRotationRadius * cos(mTheta);
    double y = mSceneNode->getPosition().y;
    double z = mRotationRadius * sin(mTheta);

    mSceneNode->setPosition(Vector3(x, y, z));

    Vector3 q = target->mSceneNode->getPosition();
    Vector3 p = mSceneNode->getPosition();
    q.y = p.y;
    mSceneNode->lookAt(q, Node::TransformSpace::TS_WORLD);

    mSceneNode->yaw(
        Degree(READER_DATA::getYawAngleDegreeOffset_Pet())
    );
}