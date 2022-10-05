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

BasicTutorial_00::BasicTutorial_00(void):
mTopViewportDimIndex(0),
mViewportDimArraySize(4),
mKeyState_P(false),
mKeyState_SPACE(false)
{
    mPet1 = new Pet();
    mPet2 = new Pet();
    initViewportDimensions();
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

void BasicTutorial_00::initViewportDimensions()
{
    mViewportDimArray[0].left = 0.0;
    mViewportDimArray[0].top = 0.0;
    mViewportDimArray[0].width = 0.25;
    mViewportDimArray[0].height = 0.25;
    //
    mViewportDimArray[1].left = 0.75;
    mViewportDimArray[1].top = 0.0;
    mViewportDimArray[1].width = 0.25;
    mViewportDimArray[1].height = 0.25;
    //
    mViewportDimArray[2].left = 0.75;
    mViewportDimArray[2].top = 0.75;
    mViewportDimArray[2].width = 0.25;
    mViewportDimArray[2].height = 0.25;
    //
    mViewportDimArray[3].left = 0.0;
    mViewportDimArray[3].top = 0.75;
    mViewportDimArray[3].width = 0.25;
    mViewportDimArray[3].height = 0.25;
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

bool BasicTutorial_00::handleKeyEvents_Camera(const OIS::KeyEvent& arg)
{
    bool flg_handled = false;

    flg_handled |= handleKeyEvents_Camera_00(arg);

    return flg_handled;
}

bool BasicTutorial_00::handleKeyEvents_Viewport(const OIS::KeyEvent& arg)
{
    bool flg_handled = false;

    if (arg.key == OIS::KC_M ) {
        flg_handled = true;
        setViewport_M();
    }

    if (arg.key == OIS::KC_N ) {
        flg_handled = true;
        setViewport_N();
    }

    if (arg.key == OIS::KC_B ) {
        flg_handled = true;
        setViewport_B();
    }

    return flg_handled;
}

void BasicTutorial_00::setViewport_M()
{
    mWindow->removeViewport(mViewportArray[0]->getZOrder());
    mWindow->removeViewport(mViewportArray[1]->getZOrder());
    //
    mViewportArray[0] = mWindow->addViewport(mCameraArray[1]);
    mViewportArray[0]->setBackgroundColour(ColourValue(0,0,1));

    mCameraArray[1]->setAspectRatio(
        Real(mViewportArray[0]->getActualWidth()) /
        Real(mViewportArray[0]->getActualHeight())
    );

    mCamera = mCameraArray[1];
    //
    mViewportArray[1] = mWindow->addViewport(
        mCameraArray[0], 1,
        0.0, 0.0, 0.25, 0.25
    );
    mViewportArray[1]->setBackgroundColour(ColourValue(0,1,0));

    mCameraArray[0]->setAspectRatio(
        Real(mViewportArray[1]->getActualWidth()) /
        Real(mViewportArray[1]->getActualHeight())
    );

    mViewportArray[1]->setOverlaysEnabled(false);

    mCamera = mCameraArray[0];
}

void BasicTutorial_00::setViewport_N()
{
    mWindow->removeViewport(mViewportArray[0]->getZOrder());
    mWindow->removeViewport(mViewportArray[1]->getZOrder());
    //
    mViewportArray[0] = mWindow->addViewport(mCameraArray[0]);
    mViewportArray[0]->setBackgroundColour(ColourValue(0,1,0));

    mCameraArray[0]->setAspectRatio(
        Real(mViewportArray[0]->getActualWidth()) /
        Real(mViewportArray[0]->getActualHeight())
    );

    mCamera = mCameraArray[0];
    //
    mViewportArray[1] = mWindow->addViewport(
        mCameraArray[1], 1,
        0.0, 0.0, 0.25, 0.25
    );
    mViewportArray[1]->setBackgroundColour(ColourValue(0,0,1));

    mCameraArray[1]->setAspectRatio(
        Real(mViewportArray[1]->getActualWidth()) /
        Real(mViewportArray[1]->getActualHeight())
    );

    mViewportArray[1]->setOverlaysEnabled(false);

    mCamera = mCameraArray[1];
}

void BasicTutorial_00::setViewport_B()
{
    mTopViewportDimIndex = (mTopViewportDimIndex + 1) % mViewportDimArraySize;
    ViewportDim vd = mViewportDimArray[mTopViewportDimIndex];
    mViewportArray[1]->setDimensions(vd.left, vd.top, vd.width, vd.height);
}

bool BasicTutorial_00::handleKeyEvents(const OIS::KeyEvent& arg)
{
    bool flg_handled = false;

    flg_handled |= handleKeyEvents_Camera(arg);
    flg_handled |= handleKeyEvents_Viewport(arg);

    return flg_handled;
}

bool BasicTutorial_00::keyPressed(const OIS::KeyEvent& arg)
{
    bool flg = true;
    bool flg_handled = false;

    flg_handled = handleKeyEvents(arg);
    if (!flg_handled) BaseApplication::keyPressed(arg);

    return flg;
}

bool BasicTutorial_00::keyReleased(const OIS::KeyEvent& arg)
{
    bool flg = true;

    BaseApplication::keyReleased(arg);

    return flg;
}

bool BasicTutorial_00::frameStarted(const FrameEvent& evt)
{
    bool flg = FrameListener::frameStarted(evt);

    if (!flg) return flg;

    mKeyboard->capture();

    if (mKeyboard->isKeyDown(OIS::KC_P))
    {
        if (mKeyState_P)
        {
            mPet1->mActivated = !mPet1->mActivated;
            mPet2->mActivated = !mPet2->mActivated;
            mKeyState_P = false;
        }
    }
    else mKeyState_P = true;

    if (mKeyboard->isKeyDown(OIS::KC_SPACE))
    {
        if (mKeyState_SPACE)
        {
            setTargetBallIndex();

            if (mTargetBallIndex >= 0)
                mBalls[mTargetBallIndex]->mActivated = true;

            mKeyState_SPACE = false;
        }
    }
    else mKeyState_SPACE = true;

    updatePets(evt.timeSinceLastFrame);
    updateBalls(evt.timeSinceLastFrame);

    return flg;
}

int main(int argc, char* argv[])
{
    (new BasicTutorial_00)->go();

    return 0;
}