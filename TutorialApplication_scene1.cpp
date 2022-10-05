#pragma once
#include "TutorialApplication.h"
#include "BasicTools.h"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <math.h>

using namespace Ogre;

#define PENGUIN_DISTANCE 200

void BasicTutorial_00::createLights_00(void)
{
    Light *light1;
    light1 = mSceneMgrArray[0]->createLight("Light1");
    light1->setType(Light::LT_POINT);
    light1->setPosition(Vector3(150, 250, 100));
    light1->setDiffuseColour(0.0, 1.0, 0.0);
    light1->setSpecularColour(0.0, 1.0, 1.0);

    Light *light2;
    light2 = mSceneMgrArray[0]->createLight("Light2");
    light2->setType(Light::LT_POINT);
    light2->setPosition(Vector3(-150, 300, 250));
    light2->setDiffuseColour(1.0, 0.0, 0.0);
    light2->setSpecularColour(1.0, 1.0, 0.0);
}

void BasicTutorial_00::createObject_00(void)
{
    mPet1->mEntity = mSceneMgrArray[0]->createEntity("Pet1", READER_DATA::getMeshName_Pet());

    mPet1->mSceneNode = mSceneMgrArray[0]
        ->getRootSceneNode()
        ->createChildSceneNode();

    mPet1->mSceneNode->setScale(2, 3, 2);
    mPet1->mSceneNode->setPosition(0, 50, 0);
    mPet1->mSceneNode->setDirection(Vector3::UNIT_Z);
    mPet1->mSceneNode->yaw(
        Degree(READER_DATA::getYawAngleDegreeOffset_Pet())
    );
    mPet1->mSceneNode->attachObject(mPet1->mEntity);

// -------------------------------

    mPet2->mEntity = mSceneMgrArray[0]->createEntity("Pet2", READER_DATA::getMeshName_Pet());

    mPet2->mSceneNode = mSceneMgrArray[0]
        ->getRootSceneNode()
        ->createChildSceneNode();

    mPet2->mSceneNode->setPosition(PENGUIN_DISTANCE, 20, 0);
    mPet2->mRotationRadius = PENGUIN_DISTANCE;

    Vector3 q = mPet1->mSceneNode->getPosition();
    Vector3 p = mPet2->mSceneNode->getPosition();
    q.y = p.y;
    mPet2->mSceneNode->lookAt(q, Node::TransformSpace::TS_WORLD);

    mPet2->mSceneNode->yaw(
        Degree(READER_DATA::getYawAngleDegreeOffset_Pet())
    );

    mPet2->mSceneNode->attachObject(mPet2->mEntity);

}

void BasicTutorial_00::createObjectGroup1_WavingCircle_00(void)
{
    int numberOfItems = 120;
    int itemGroupRadius = 150;
    int L = 255;
    double x = 0, y = 50, z = 0, r = 0, h = 0, fx = 0;

    AxisAlignedBox bb;
    double cubeSize = 1.0, unitF = 1.0;

    for (int i = 0; i < numberOfItems; i += 1)
    {
        String entityName;
        genNameUsingIndex("WavingCircle", i, entityName);
        Entity *entity = mSceneMgrArray[0]->createEntity(
            entityName, "cube.mesh");
        entity->setMaterialName("Examples/SphereMappedRustySteel");

        bb =  entity->getBoundingBox();
        cubeSize = bb.getMaximum().x - bb.getMinimum().x;
        unitF = 1.0 / cubeSize / numberOfItems * L * 0.8;

        fx = i / (double)(numberOfItems - 1);
        r = itemGroupRadius + (1 + 2 * sin(fx * PI * 8)) * 10;
        x = r * cos(fx * PI * 2);
        z = r * sin(fx * PI * 2);
        h = (1 + sin(fx * PI * 8)) * 50 / cubeSize;

        SceneNode* sceneNode = mSceneMgrArray[0]
            ->getRootSceneNode()
            ->createChildSceneNode();

        sceneNode->setScale(unitF, h, unitF);
        sceneNode->setPosition(x, y, z);
        sceneNode->attachObject(entity);
    }
}

void BasicTutorial_00::createObjectGroup2_WavingRow_00(void)
{
    int numberOfItems = 120;
    int L = 255;
    double x = 0, y = 20, z = 200, r = 0, h = 0, fx = 0;

    AxisAlignedBox bb;
    double cubeSize = 1.0, unitF = 1.0;

    for (int i = 0; i < numberOfItems; i += 1)
    {
        String entityName;
        genNameUsingIndex("WavingRow", i, entityName);
        Entity *entity = mSceneMgrArray[0]->createEntity(
            entityName, "cube.mesh");
        entity->setMaterialName("Examples/Chrome");

        bb =  entity->getBoundingBox();
        cubeSize = bb.getMaximum().x - bb.getMinimum().x;
        unitF = 1.0 / cubeSize / numberOfItems * L * 0.8;

        fx = 2 * i / (double)(numberOfItems-1);
        x = fx * L - L / 2.0;
        h = (1 + cos(fx * PI * 2.0)) * 20 / cubeSize;

        SceneNode* sceneNode = mSceneMgrArray[0]
            ->getRootSceneNode()
            ->createChildSceneNode();

        sceneNode->setScale(unitF, h, unitF);
        sceneNode->setPosition(x, y, z);
        sceneNode->attachObject(entity);
    }
}

void BasicTutorial_00::createObjectGroup2_Balls_00(void)
{
    int numberOfItems = 8;
    int itemGroupRadius = 300;
    double x = 0, y = 20, z = 0, fx = 0;

    for (int i = 0; i < numberOfItems; i += 1)
    {
        mBalls[i] = new Ball();

        String entityName;
        genNameUsingIndex("Balls", i, entityName);
        mBalls[i]->mEntity = mSceneMgrArray[0]->createEntity(
            entityName, "sphere.mesh");
        mBalls[i]->mEntity->setMaterialName("Examples/SceneCubeMap1");

        fx = i / (double) numberOfItems;
        x = itemGroupRadius * cos(fx * PI * 2);
        z = itemGroupRadius * sin(fx * PI * 2);

        mBalls[i]->mSceneNode = mSceneMgrArray[0]
            ->getRootSceneNode()
            ->createChildSceneNode();

        mBalls[i]->mSceneNode->setScale(0.2, 0.2, 0.2);
        mBalls[i]->mSceneNode->setPosition(x, y, z);
        mBalls[i]->setVelocity(mPet1);
        mBalls[i]->mSceneNode->attachObject(mBalls[i]->mEntity);
    }
}

void BasicTutorial_00::createGroundMesh_00(void)
{
    Plane plane(Vector3::UNIT_Y, 0);

    MeshManager::getSingleton().createPlane(
        "ground0",
        ResourceGroupManager
        ::DEFAULT_RESOURCE_GROUP_NAME,
        plane,
        1500, 1500, 	// width, height
        20, 20, 		// x- and y-segments
        true, 		    // normal
        1, 		        // num texture sets
        5, 5, 		    // x- and y-tiles
        Vector3::UNIT_Z	// upward vector
    );
}

void BasicTutorial_00::createFloor_00(void)
{
    createGroundMesh_00();

    Entity* entity = mSceneMgrArray[0]->createEntity("GroundEntity0", "ground0");
    entity->setMaterialName(READER_DATA::getMaterialName_Floor());
    entity->setCastShadows(false);

    mSceneMgrArray[0]
        ->getRootSceneNode()
        ->createChildSceneNode()
        ->attachObject(entity);
}

void BasicTutorial_00::createScene_00(void)
{
    mSceneMgr = mSceneMgrArray[0];

    mSceneMgr->setAmbientLight(ColourValue( 0.5, 0.5, 0.5 ));
    mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);

    this->createLights_00();
    this->createFloor_00();
    this->createObject_00();
    this->createObjectGroup1_WavingCircle_00();
    this->createObjectGroup2_WavingRow_00();
    this->createObjectGroup2_Balls_00();
}

void BasicTutorial_00::createCamera_00(void)
{
    mSceneMgr = mSceneMgrArray[0];
    mCameraArray[0] = mSceneMgrArray[0]->createCamera("Camera0");

    mCameraArray[0]->setPosition(Vector3(120,300,600));
    mCameraArray[0]->lookAt(Vector3(120,0,0));
    mCameraArray[0]->setNearClipDistance(5);
    mCamera = mCameraArray[0];

    mCameraManArray[0] = new OgreBites::SdkCameraMan(mCameraArray[0]);
    mCameraMan = mCameraManArray[0];
}

void BasicTutorial_00::createViewport_00(void)
{
    mViewportArray[0] = mWindow->addViewport(mCameraArray[0]);
    mViewportArray[0]->setBackgroundColour(ColourValue(0,0,1));

    mCameraArray[0]->setAspectRatio(
        Real(mViewportArray[0]->getActualWidth()) /
        Real(mViewportArray[0]->getActualHeight())
    );

    mViewportArray[0]->setOverlaysEnabled(false);

    mCamera = mCameraArray[0];
}

bool BasicTutorial_00::handleKeyEvents_Camera_00(const OIS::KeyEvent& arg)
{
    bool flg_handled = false;

    if (arg.key == OIS::KC_1 ) {
        flg_handled = true;

        mCameraArray[0]
            ->setPosition(Vector3(0,300,500));
        mCameraArray[0]
            ->setDirection(Vector3(0,-300,-500));
        mCamera = mCameraArray[0];
    }

    if (arg.key == OIS::KC_2 ) {
        flg_handled = true;

        mCameraArray[0]
            ->setPosition(Vector3(500,300,0));
        mCameraArray[0]
            ->setDirection(Vector3(-500,-300,0));
        mCamera = mCameraArray[0];
    }

    if (arg.key == OIS::KC_3 ) {
        flg_handled = true;

        mCameraArray[0]
            ->setPosition(Vector3(0,300,-500));
        mCameraArray[0]
            ->setDirection(Vector3(0,-300,500));
        mCamera = mCameraArray[0];
    }

    if (arg.key == OIS::KC_4 ) {
        flg_handled = true;

        mCameraArray[0]
            ->setPosition(Vector3(-500,300,0));
        mCameraArray[0]
            ->setDirection(Vector3(500,-300,0));
        mCamera = mCameraArray[0];
    }

    if (arg.key == OIS::KC_5 ) {
        flg_handled = true;

        mCameraArray[0]
            ->setPosition(Vector3(50, 600, 50));
        mCameraArray[0]
            ->setDirection(Vector3(-50, -600, -50));
        mCamera = mCameraArray[0];
    }

    if (arg.key == OIS::KC_6 ) {
        flg_handled = true;

        mCameraArray[0]
            ->setPosition(Vector3(120,300,600));
        mCameraArray[0]
            ->setDirection(Vector3(-120,-300,-600));
        mCamera = mCameraArray[0];
    }

    return flg_handled;
}

void BasicTutorial_00::updatePets(const Real& dt)
{
    mPet1->rotate(dt, mPet2);
    mPet2->rotate(dt, mPet1);
}

void BasicTutorial_00::updateBalls(const Real& dt)
{
    for (int i = 0; i < 8; i += 1)
        mBalls[i]->projectile(dt);
}

void BasicTutorial_00::setTargetBallIndex(void)
{
    mTargetBallIndex = -1;
    Real limitDistance = 120.0;

    for (int i = 0; i < 8; i += 1)
    {
        Vector3 p0 = mPet2->mSceneNode->getPosition();
        Vector3 p1 = mBalls[i]->mSceneNode->getPosition();
        Real distance = p0.distance(p1);

        if (distance < limitDistance)
        {
            mTargetBallIndex = i;
            break;
        }
    }
}