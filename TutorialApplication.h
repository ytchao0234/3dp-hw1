//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
//
/*!
\brief 3D Game Programming
\n
My Name: Yu-Ting Chao
\n
My ID: 311551031
\n
My Email: nd68319@gmail.com
\n Date: 2022/09/29

This is an assignment of 3D Game Programming

REMARK:
You are allowed to delete the functions
and data members that you do not want to use.
You can define your own data members and functions.
*/
#pragma once
#ifndef __BasicTutorial_00_h_
#define __BasicTutorial_00_h_

#include "BaseApplication.h"
#include "reader_data.h"
#include "SystemParameter.h"
#include "Pet.h"

using namespace Ogre;

#define PI 3.141592654

class BasicTutorial_00 : public BaseApplication
{
public:
    BasicTutorial_00(void);
    ~BasicTutorial_00(void);
protected:
    virtual void chooseSceneManager(void);
    virtual void createScene(void);
    virtual void createCamera(void);
    virtual void createViewports(void);
    //
    virtual bool frameStarted(const FrameEvent&);
    //
    void createObjectGroup1_WavingCircle_00(void);
    void createObjectGroup2_WavingRow_00(void);
    //
    void createLights_00(void);
    void createLights_01(void);
    void createObject_00(void);
    void createObject_01(void);
    void createGroundMesh_00(void);
    void createGroundMesh_01(void);
    void createFloor_00(void);
    void createFloor_01(void);
    void createCamera_00(void);
    void createCamera_01(void);
    void createViewport_00(void);
    void createViewport_01(void);
    void createScene_00(void);
    void createScene_01(void);
    //
    bool handleKeyEvents(const OIS::KeyEvent&);
    bool handleKeyEvents_Camera_00(const OIS::KeyEvent&);
    //
    bool keyPressed(const OIS::KeyEvent&);
    bool keyReleased(const OIS::KeyEvent&);
protected:
    SceneManager* mSceneMgrArray[2];
    Viewport* mViewportArray[2];
    Camera* mCameraArray[2];
    OgreBites::SdkCameraMan* mCameraManArray[2];

    Pet* mPet1;
    Pet* mPet2;
};

#endif // #ifndef __BasicTutorial_00_h_