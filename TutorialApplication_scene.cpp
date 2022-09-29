//
// 3D Game Programming
// 
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
//
//
// Purpose: Set the scenes. 
//
//
//
#include "TutorialApplication.h"
#include "BasicTools.h"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <math.h>

using namespace Ogre;

void BasicTutorial_00::createObjectGroup1_SphereGroup( void ) {
    mNumOfItems = 3;
    mItemGroupRadius = 150;

    for (int i = 0; i < mNumOfItems;++i) {
        double x, y, z;
        x = y = z = 0;
        double a = i/(double)mNumOfItems*PI*2;
        x = mItemGroupRadius*cos(a);
        z = mItemGroupRadius*sin(a);

        String ename;
        genNameUsingIndex("item", i, ename);
        Entity *ent = mSceneMgr->createEntity(
            ename, "sphere.mesh");
        ent->setMaterialName("Examples/SceneCubeMap1");
        //ent->setMaterialName("Examples/SceneCubeMap1");

        SceneNode *snode = mSceneMgr
            ->getRootSceneNode()
            ->createChildSceneNode();
        double scaleFactor = 0.2;
        snode->setScale(scaleFactor, scaleFactor, scaleFactor);
        snode->setPosition(x, y, z);
        snode->attachObject(ent);

        const AxisAlignedBox bb =  ent->getBoundingBox();
        Real itemSize = bb.getMaximum().x - bb.getMinimum().x;
        snode->translate(0, scaleFactor*itemSize/2.0, 0);
        mItemArr[i] = snode;
        mItemStatus[i] = ITEM_STATE_INACTIVE;
        //
        //
        //mVelocityArr[0] = Vector3( 1.0, 2.0, 1.0);
        mVelocityArr[i] = -mItemArr[i]->getPosition( );
        mVelocityArr[i].normalise( );
        mVelocityArr[i].y = 2.0;
        mVelocityArr[i].normalise( );
        mVelocityArr[i] = 170*mVelocityArr[i];
    }

}

void BasicTutorial_00::createObjectGroup2_WavyCircle( ) 
{
    int numCubes = 128;
    double L = 255;
    for (int i = 0; i < numCubes; ++i)
    {
        //
        //
        //
    }
}

void BasicTutorial_00::createObjectGroup3_Wave()
{
    int numCubes = 10;
    double L = 1000;

    for (int i = 0; i < numCubes; ++i)
    {
        String name;
        genNameUsingIndex("d", i, name);
        Entity* ent = mSceneMgr->createEntity(
            name, "cube.mesh");
        ent->setMaterialName("Examples/Chrome");
        const AxisAlignedBox bb = ent->getBoundingBox();
        Real cubeSize = bb.getMaximum().x - bb.getMinimum().x;
        double x = 0, y = 0, z = 125;
        SceneNode* snode = mSceneMgr
            ->getRootSceneNode()
            ->createChildSceneNode();
        snode->attachObject(ent);
        double fx;
        double h;

        fx = 2 * i / (double)(numCubes - 1);
        x = fx * L - L / 2.0;
        h = (1 + cos(fx * 3.1415 * 2.0)) * 20;
        Real unitF = 1.0 / cubeSize / numCubes * L * 0.8;
        snode->scale(unitF, h / cubeSize, unitF);
        snode->setPosition(x, 20, z);
    }

}

void BasicTutorial_00::createLights( ) 
{
    mSceneMgr->setAmbientLight( ColourValue( 0.5, 0.5, 0.5 ) ); 
    //mSceneMgr->setAmbientLight( ColourValue( 1, 1, 1 ) );  
    mSceneMgr->setShadowTechnique(
        SHADOWTYPE_STENCIL_ADDITIVE); 

    Light *light;
    light = mSceneMgr->createLight("Light1"); 
    light->setType(Light::LT_POINT); 
    light->setPosition(Vector3(150, 250, 100)); 
    light->setDiffuseColour(0.0, 1.0, 0.0);		
    light->setSpecularColour(0.0, 1.0, 0.0);	

    //
    //
    //
}

void BasicTutorial_00::createPets( )
{
    Entity *ent2 
        = mSceneMgr
        ->createEntity("Robot2", "sphere.mesh");
       // ->createEntity( "Robot2", READER_DATA::getMeshName_Pet( ) ); 

    SceneNode *node2 
        = mSceneMgr
        ->getRootSceneNode()
        ->createChildSceneNode( 
        "RobotNode2", Vector3( 150, 0, 0 ) ); 

    node2->yaw( 
        Degree( READER_DATA::getYawAngleDegreeOffset_Pet( ) ) 
        );


    node2->attachObject( ent2 );

    Entity *ent22 
        = mSceneMgr
        ->createEntity("Robot22", "ninja.mesh");
        //->createEntity( "Robot22", READER_DATA::getMeshName_Pet( ) ); 

    SceneNode *node22 
        = mSceneMgr
        ->getRootSceneNode()
        ->createChildSceneNode( 
        "RobotNode22", Vector3( 0, 0, 0 ) ); 

    node22->attachObject( ent22 );
    node22->scale(2, 3, 2);


    if (READER_DATA::getFlgAutoPlaceObj()) {
        Ogre::LogManager::getSingletonPtr()->logMessage("READER_DATA::getFlgAutoPlaceObj()***");

        AxisAlignedBox bb;
        Real obj_min_y;
        //
        bb = ent2->getBoundingBox();
        //
        //
        //
    }

    mMovableObj = node2;
    mTargetObj = node22;

}

// 
// Create a mesh and assign it a name. 
// After that, we use the mesh name to create entities.
//
void BasicTutorial_00::createPlaneObjectResource( )
{
    Plane plane(Vector3::UNIT_Y, 0); 
    MeshManager::getSingleton().createPlane(
        "plane_object_resource", 						
        ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
        plane, 
        1500,1500, 	// width, height
        20,20, 		// x- and y-segments
        true, 		// normal
        1, 			// num texture sets
        5,5, 		// x- and y-tiles
        Vector3::UNIT_Z	// upward vector
        ); 
}

void BasicTutorial_00::createFloor( )
{
    //
    //
    //
}

void BasicTutorial_00::createWall( )
{
    Entity *ent = mSceneMgr->createEntity(
        "Background", "plane_object_resource"); 
    //ent->setMaterialName("Examples/BeachStones");
    //ent->setMaterialName("Examples/Rockwall");
    ent->setMaterialName( READER_DATA::getMaterialName_Wall( ) );

    //Radian angle(3.141952654/2.0);
    Radian angle(3.141952654 / 4.0);

    Vector3 axis(1.0, 0.0, 0.0);
    mSceneMgr
        ->getRootSceneNode()
        ->createChildSceneNode(
        Vector3(0.0, 0.0, -750.0),
        Quaternion( angle, axis))
        ->attachObject(ent);
}

//
// Set mSceneMgr = mSceneMgrArr[0];
// Then we use mSceneMgr to create objects in the second scene.
// Because we use mSceneMgr, we keep our code consistent.
// But need to bear in mind that which scene manager that we are using.
// 
void BasicTutorial_00::createScene_00(void) 
{
    mSceneMgr = mSceneMgrArr[0];
    ////////////////////////////////////////////////////
    // Now we can use mSceneMgr to create objects as usual.
    ////////////////////////////////////////////////////

    ////////////////////////////////////////////////////
    // Enjoy modular programming experience
    ////////////////////////////////////////////////////
    createLights( );
    createPets( );
    UpdateMovableObjPosition();
    createPlaneObjectResource( );
    createFloor( );
    createWall( );
    //
    createObjectGroup1_SphereGroup();
    createObjectGroup2_WavyCircle();
    createObjectGroup3_Wave( );
}


//
// Set mSceneMgr = mSceneMgrArr[1];
// Then we use mSceneMgr to create objects in the second scene.
// Because we use mSceneMgr, we keep our code consistent.
// But need to bear in mind that which scene manager that we are using.
// 
void BasicTutorial_00::createScene_01(void)
{
    ////////////////////////////////////////////////////
    mSceneMgr = mSceneMgrArr[1];
    ////////////////////////////////////////////////////
    // Now we can use mSceneMgr to create objects as usual.
    ////////////////////////////////////////////////////

    //mSceneMgr->setAmbientLight( ColourValue( 1.0,1.0, 1.0 ) ); 
    mSceneMgr->setAmbientLight(ColourValue(0.0, 0.0, 0.0));
    //mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE); 
    //mSceneMgr->setShadowTechnique(SHADOWTYPE_TEXTURE_MODULATIVE);

    /*
    Light *light = mSceneMgr->createLight("Light1");
    light->setType(Light::LT_POINT);
    light->setPosition(Vector3(100, 150, 250));
    light->setDiffuseColour(0.0, 0.0, 1.0);
    light->setSpecularColour(0.0, 0.0, 1.0);
    */
    //ent3->setMaterialName("Examples/green");
    //
}