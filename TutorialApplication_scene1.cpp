#pragma once
#include "TutorialApplication.h"
#include "BasicTools.h"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <math.h>

using namespace Ogre;

void BasicTutorial_00::createLights_00(void)
{
    mSceneMgrArray[0]->setAmbientLight(ColourValue( 0.5, 0.5, 0.5 ));
    mSceneMgrArray[0]->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);

    Light *light1;
    light1 = mSceneMgrArray[0]->createLight("Light1");
    light1->setType(Light::LT_POINT);
    light1->setPosition(Vector3(150, 250, 100));
    light1->setDiffuseColour(0.0, 1.0, 0.0);
    light1->setSpecularColour(0.0, 1.0, 0.0);

    Light *light2;
    light2 = mSceneMgrArray[0]->createLight("Light2");
    light2->setType(Light::LT_POINT);
    light2->setPosition(Vector3(-150, 250, 100));
    light2->setDiffuseColour(1.0, 0.0, 0.0);
    light2->setSpecularColour(1.0, 0.0, 0.0);
}

void BasicTutorial_00::createObject_00(void)
{
    mPet1->mEntity = mSceneMgrArray[0]->createEntity("Pet1", READER_DATA::getMeshName_Pet());

    mPet1->mSceneNode = mSceneMgrArray[0]
        ->getRootSceneNode()
        ->createChildSceneNode();

    double scaleFactor = READER_DATA::getMeshScale_Pet();
    mPet1->mSceneNode->setScale(scaleFactor, scaleFactor, scaleFactor);
    mPet1->mSceneNode->setPosition(Vector3::UNIT_Y * 100);
    mPet1->mSceneNode->attachObject(mPet1->mEntity);

// -------------------------------

    mPet2->mEntity = mSceneMgrArray[0]->createEntity("Pet2", READER_DATA::getMeshName_Pet());

    mPet2->mSceneNode = mSceneMgrArray[0]
        ->getRootSceneNode()
        ->createChildSceneNode();

    mPet2->mSceneNode->setPosition(300, 20, 0);
    mPet2->mSceneNode->setDirection(Vector3::UNIT_X);
    mPet2->mSceneNode->attachObject(mPet2->mEntity);
}

void BasicTutorial_00::createObjectGroup1_WavingCircle_00(void)
{
    int numberOfItems = 100;
    int itemGroupRadius = 250;
    double x = 0, y = 50, z = 0, a = 0;
    double scaleFactor = 2.0 / numberOfItems;

    for (int i = 0; i < numberOfItems; i += 1)
    {
        a = i / (double) numberOfItems * PI * 2;
        x = itemGroupRadius * cos(a);
        z = itemGroupRadius * sin(a);

        String entityName;
        genNameUsingIndex("WavingCircle", i, entityName);
        Entity *entity = mSceneMgrArray[0]->createEntity(
            entityName, "cube.mesh");

        SceneNode* sceneNode = mSceneMgrArray[0]
            ->getRootSceneNode()
            ->createChildSceneNode();

        sceneNode->setScale(scaleFactor, abs(sin(a * 2)), scaleFactor);
        sceneNode->setPosition(x, y, z);
        sceneNode->attachObject(entity);
    }
}

void BasicTutorial_00::createObjectGroup2_WavingRow_00(void)
{
    int numberOfItems = 100;
    double x = -200, y = 50, z = 500, a = 0;
    double scaleFactor = 2.0 / numberOfItems;
    double gap = 10.0;

    for (int i = 0; i < numberOfItems; i += 1)
    {
        a = i / (double) numberOfItems * PI * 2;
        x += gap;

        String entityName;
        genNameUsingIndex("WavingRow", i, entityName);
        Entity *entity = mSceneMgrArray[0]->createEntity(
            entityName, "cube.mesh");

        SceneNode* sceneNode = mSceneMgrArray[0]
            ->getRootSceneNode()
            ->createChildSceneNode();

        sceneNode->setScale(scaleFactor, abs(sin(a * 2)), scaleFactor);
        sceneNode->setPosition(x, y, z);
        sceneNode->attachObject(entity);
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
    this->createLights_00();
    this->createFloor_00();
    this->createObject_00();
    this->createObjectGroup1_WavingCircle_00();
    this->createObjectGroup2_WavingRow_00();
}

void BasicTutorial_00::createCamera_00(void)
{
    mSceneMgr = mSceneMgrArray[0];
    mCameraArray[0] = mSceneMgrArray[0]->createCamera("Camera0");

    mCameraArray[0]->setPosition(Vector3(0,500,1000));
    mCameraArray[0]->lookAt(Vector3(0,0,0));
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

    mCamera = mCameraArray[0];
}