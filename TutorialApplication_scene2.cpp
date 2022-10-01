#pragma once
#include "TutorialApplication.h"
#include "BasicTools.h"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <math.h>

using namespace Ogre;

void BasicTutorial_00::createLights_01(void)
{
    mSceneMgrArray[1]->setAmbientLight(ColourValue( 0.5, 0.5, 0.5 ));
    mSceneMgrArray[1]->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);

    Light *light3;
    light3 = mSceneMgrArray[1]->createLight("Light3");
    light3->setType(Light::LT_POINT);
    light3->setPosition(Vector3(-50, 250, 100));
    light3->setDiffuseColour(0.0, 0.0, 1.0);
    light3->setSpecularColour(0.0, 0.0, 1.0);
}

void BasicTutorial_00::createObject_01(void)
{
    Entity *entity = mSceneMgrArray[1]->createEntity(
        "Sphere0", "sphere.mesh");
    entity->setMaterialName("Template/Green");

    SceneNode* sceneNode = mSceneMgrArray[1]
        ->getRootSceneNode()
        ->createChildSceneNode();

    double scaleFactorX = 0.2, scaleFactorY = 0.5, scaleFactorZ = 0.8;

    sceneNode->setScale(scaleFactorX, scaleFactorY, scaleFactorZ);
    sceneNode->setPosition(50, 50, 0);
    sceneNode->attachObject(entity);
}

void BasicTutorial_00::createGroundMesh_01(void)
{
    Plane plane(Vector3::UNIT_Y, 0);

    MeshManager::getSingleton().createPlane(
        "ground1",
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

void BasicTutorial_00::createFloor_01(void)
{
    createGroundMesh_01();

    Entity* entity = mSceneMgrArray[0]->createEntity("GroundEntity1", "ground1");
    entity->setMaterialName(READER_DATA::getMaterialName_Floor());
    entity->setCastShadows(false);

    mSceneMgrArray[1]
        ->getRootSceneNode()
        ->createChildSceneNode()
        ->attachObject(entity);
}

void BasicTutorial_00::createScene_01(void)
{
    mSceneMgr = mSceneMgrArray[1];
    this->createObject_01();
    this->createLights_01();
    this->createFloor_01();
}

void BasicTutorial_00::createCamera_01(void)
{
    mSceneMgr = mSceneMgrArray[1];
    mCameraArray[1] = mSceneMgrArray[1]->createCamera("Camera1");

    mCameraArray[1]->setPosition(Vector3(0,350,0.001));
    mCameraArray[1]->lookAt(Vector3(0,0,0));
    mCameraArray[1]->setNearClipDistance(5);
    mCamera = mCameraArray[1];

    mCameraManArray[1] = new OgreBites::SdkCameraMan(mCameraArray[1]);
    mCameraMan = mCameraManArray[1];
}

void BasicTutorial_00::createViewport_01(void)
{
    mViewportArray[1] = mWindow->addViewport(
        mCameraArray[1], 1,
        0.0, 0.0, 0.25, 0.25);
    mViewportArray[1]->setBackgroundColour(ColourValue(0,0,1));

    mCameraArray[1]->setAspectRatio(
        Real(mViewportArray[1]->getActualWidth()) /
        Real(mViewportArray[1]->getActualHeight())
    );

    mViewportArray[1]->setOverlaysEnabled(false);

    mCamera = mCameraArray[1];
}