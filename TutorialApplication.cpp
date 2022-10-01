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
    mPet1 = new Pet();
    mPet2 = new Pet();
}

BasicTutorial_00::~BasicTutorial_00(void)
{
    delete mPet1;
    delete mPet2;
    delete[] mSceneMgrArray;
    delete[] mCameraArray;
    delete[] mViewportArray;
    delete[] mCameraManArray;
}

void BasicTutorial_00::chooseSceneManager(void)
{
    mSceneMgrArray[0] = mRoot->createSceneManager(ST_GENERIC, "primary");
    mSceneMgrArray[1] = mRoot->createSceneManager(ST_GENERIC, "secondary");
}

void BasicTutorial_00::createScene(void)
{
    READER_DATA::readData();

    this->createScene_00();
    this->createScene_01();
    mSceneMgr = mSceneMgrArray[0];
    mCamera = mCameraArray[0];
}

void BasicTutorial_00::createCamera(void)
{
    this->createCamera_00();
    this->createCamera_01();
    mCameraMan = mCameraManArray[0];
}

void BasicTutorial_00::createViewports(void)
{
    this->createViewport_00();
    this->createViewport_01();
}

bool BasicTutorial_00::frameStarted(const FrameEvent& evt)
{
    bool flg_handled = false;
    mKeyboard->capture();
    mMouse->capture();

    return true;
}

int main(int argc, char* argv[])
{
    (new BasicTutorial_00)->go();

    return 0;
}