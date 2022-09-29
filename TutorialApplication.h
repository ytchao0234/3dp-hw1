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

#define PI 3.141592654

class BasicTutorial_00 : public BaseApplication
{
public:
    BasicTutorial_00(void);
    ~BasicTutorial_00(void);
protected:
    virtual void chooseSceneManager(void);
    //
    virtual void createLights(void);
    virtual void createObject(void);
    virtual void createGroundMesh(void);
    virtual void createFloor(void);
    virtual void createScene(void);
    // virtual void createCamera(void);
    virtual void createViewports(void);
    //
    virtual bool frameStarted(const FrameEvent&);
protected:
    Pet* mPet;
};

#endif // #ifndef __BasicTutorial_00_h_