//
// 3D Game Programming
// NYCU
// Instructor: Sai-Keung Wong
//
#include "TutorialApplication.h"
#include "BasicTools.h"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <math.h>

using namespace Ogre;

BasicTutorial_00::BasicTutorial_00(void)
{
    mPet = new Pet();
}

BasicTutorial_00::~BasicTutorial_00(void)
{
    delete mPet;
}

void BasicTutorial_00::chooseSceneManager(void)
{
    mSceneMgr = mRoot->createSceneManager(ST_EXTERIOR_CLOSE);
}

void BasicTutorial_00::createLights(void)
{
    mSceneMgr->setAmbientLight(ColourValue( 0.5, 0.5, 0.5 )); 
    mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE); 
}

void BasicTutorial_00::createObject(void)
{
    mPet->mEntity = mSceneMgr->createEntity("Pet1", READER_DATA::getMeshName_Pet());

    mPet->mSceneNode = mSceneMgr
        ->getRootSceneNode()
        ->createChildSceneNode();

    mPet->mSceneNode->attachObject(mPet->mEntity);
}

void BasicTutorial_00::createGroundMesh(void)
{
    Plane plane(Vector3::UNIT_Y, 0);

    MeshManager::getSingleton().createPlane(
        "ground",
        ResourceGroupManager
        ::DEFAULT_RESOURCE_GROUP_NAME,
        plane,
        1500, 1500, 	// width, height
        20, 20, 		// x- and y-segments
        true, 		// normal
        1, 		// num texture sets
        5, 5, 		// x- and y-tiles
        Vector3::UNIT_Z	// upward vector
    );
}

void BasicTutorial_00::createFloor(void)
{
    createGroundMesh();

    Entity* entity = mSceneMgr->createEntity("GroundEntity", "ground");
    entity->setMaterialName(READER_DATA::getMaterialName_Floor());
    entity->setCastShadows(false);

    mSceneMgr
        ->getRootSceneNode()
        ->createChildSceneNode()
        ->attachObject(entity);
}

void BasicTutorial_00::createScene(void)
{
    READER_DATA::readData();

    this->createLights();
    this->createFloor();
    this->createObject();
}

// void BaseApplication::createCamera(void)
// {
//     mCamera = mSceneMgr->createCamera("PlayerCam");

//     mCamera->setPosition(Vector3(0,80,1000));
//     mCamera->lookAt(Vector3(0,0,0));
//     mCamera->setNearClipDistance(5);

//     mCameraMan = new OgreBites::SdkCameraMan(mCamera);
// }

void BasicTutorial_00::createViewports(void)
{
    Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(ColourValue(0,0,1));

    mCamera->setAspectRatio(
        Real(vp->getActualWidth()) / Real(vp->getActualHeight()));
}

bool BasicTutorial_00::frameStarted(const FrameEvent& evt)
{
    bool flg_handled = false;
    mKeyboard->capture();
    mMouse->capture();

    if (!mKeyboard->isKeyDown(OIS::KC_M))
    {
        mPet->mActivate = true;
    }
    else if (mPet->mActivate)
    {
        mPet->translate(evt.timeSinceLastFrame);
        mPet->mActivate = false;
    }

    return true;
}

int main(int argc, char* argv[])
{
    (new BasicTutorial_00)->go();

    return 0;
}