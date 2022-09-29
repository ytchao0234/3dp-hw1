//
// 3D Game Programming
// NYCU
// Instructor: Sai-Keung Wong
//
//
// Purpose: Update the game state, 
// including object states, game progress, physics simulation, 
// collision detection, collision response, and etc.
//
//
// The functions will be invoked at the runtime stage.
//
// Example: 
// Handle key events to control the camera.
// Handle key events to set viewports.
// Handle key events to obtain the camera information.
// Handle key events to activate the items, i.e., spheres.
// Update the spheres.
// Update the pets.
// And others
// 
// A key handler handles simple tasks, 
// such as setting the states of game objects. 
//
//

#include "TutorialApplication.h"
#include "BasicTools.h"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <math.h>

//
// using namespace Ogre;
// Enable to use the functions/structures defined in the namespace Ogre.
//
using namespace Ogre;

//
// Handle key events for controlling the active camera.
//
// Set the camera position and its lookat position.
//
bool BasicTutorial_00::handleKeyEvents_Camera( const OIS::KeyEvent &arg ) 
{
    bool flg_handled = false;
    if (arg.key == OIS::KC_1 ) {
        flg_handled = true;

        mCameraMan->getCamera()
            ->setPosition(Vector3(45.21,	10.27,	397.32));
        mCameraMan->getCamera()
            ->setDirection(Vector3(0.0,	-0.00,	-0.0));
    }


    if (arg.key == OIS::KC_2 ) {
        flg_handled = true;
        
        mCameraMan->getCamera()
            ->setPosition(Vector3(-51.32,	-159.52,	242.68));
        mCameraMan->getCamera()
            ->setDirection(Vector3(0.10,	0.18,	-0.98));
    }

    if (arg.key == OIS::KC_3 ) {
        flg_handled = true;
        //setPosition(Vector3(-1463.00,	606.45,	-513.24));
        //setDirection(Vector3(0.88,	-0.47,	0.10));
    }

    if (arg.key == OIS::KC_4 ) {
        flg_handled = true;

       //setPosition(Vector3(-1356.16,	634.32,	-964.51));
       //setDirection(Vector3(0.71,	-0.44,	0.55));
    }

    if (arg.key == OIS::KC_5 ) {
        flg_handled = true;

        //setPosition(Vector3(40.39,	155.23,	251.20));
        //setDirection(Vector3(-0.02,	-0.41,	-0.91));
    }

    if (arg.key == OIS::KC_6 ) {
        flg_handled = true;

       //setPosition(Vector3(19.94,	822.63,	30.79));
       //setDirection(Vector3(-0.01, - 1.00, - 0.05));
    }
    return flg_handled;
}

//
// Set the viewport attributes, 
// e.g., background colours, dimensions and locations.
//
bool BasicTutorial_00::handleKeyEvents_Viewport( const OIS::KeyEvent &arg ) 
{
    bool flg_handled = false;

    if (arg.key == OIS::KC_M ) {
        flg_handled = true;
        //
        //
        //
    }

    if (arg.key == OIS::KC_N ) {
        flg_handled = true;
        //
        //
        //
        
    }

    if ( arg.key == OIS::KC_B) {
        flg_handled = true;

        //
        //
        //
    }

    return flg_handled;
}

//
// Set the object states for animation or simulation.
// Try not to perform complex tasks in a key handler.
//
bool BasicTutorial_00::handleKeyEvents_Animation( const OIS::KeyEvent &arg ) 
{
    bool flg_handled = false;
    if ( arg.key == OIS::KC_P ) {
        flg_handled = true;
        //
        //
        //
    }

    if ( arg.key == OIS::KC_SPACE ) 
    {
        flg_handled = true;
        //
        //
        //
    }
    if ( arg.key == OIS::KC_K ) 
    {
        flg_handled = true;
        //
        //
        //
    }
    return flg_handled;
}

//
// Get the camera position and direction.
// Save them to the log file.
//
bool BasicTutorial_00::handleKeyEvents_GetCameraInformation( const OIS::KeyEvent &arg ) 
{
    bool flg_handled = false;

    stringstream ss;
    if (arg.key == OIS::KC_C ) {

        flg_handled = true;

        //How to clear ss?
        ss.str("");
        ss.clear();

        //stringstream ss; // Second way

        // Third way?
        //=============

        // How to get camera position?
        //-----------------------------
        // This is incorrect.
        // Vector3 pos = mCamera->getPosition();
        // The controller may have its own 
        // set of attributes to control the camera.
        //
        //We use the controller to get the camera information.
        //-----------------------------
        //
        //
        // The following is correct.
        //
        Vector3 pos = mCameraMan->getCamera()->getPosition(); 
        ss << std::fixed << std::setprecision(2) 
            << "CameraPosition:" 
            << pos.x << "\t" 
            << pos.y << "\t" 
            << pos.z << "\n";
        Ogre::LogManager::getSingletonPtr()
            ->logMessage( ss.str() );
        //
        ss.str("");
        ss.clear();
        Vector3 dir = mCameraMan->getCamera()->getDirection();

        ss << std::fixed << std::setprecision(2) 
            << "CameraDirection:" 
            << dir.x << "\t" 
            << dir.y << "\t" 
            << dir.z << "\n";

        Ogre::LogManager::getSingletonPtr()
            ->logMessage( ss.str() );
    }

    return flg_handled;
}


//
// return true if the key event has been handled
//
bool BasicTutorial_00::handleKeyEvents( const OIS::KeyEvent &arg )
{
    bool flg_handled = false;

    //
    // Use the OR operator to turn on the flag
    //
    // Make sure that the same key is not used in
    // two or more functions.
    //
    flg_handled |= handleKeyEvents_GetCameraInformation( arg );
    flg_handled |= handleKeyEvents_Camera( arg );
    flg_handled |= handleKeyEvents_Viewport( arg );
    flg_handled |= handleKeyEvents_Animation( arg );

    return flg_handled;
}

//
// Set the position, status, and velocity of each item.
// 
// 
void BasicTutorial_00::resetItems( ) {
    //
    //
    //
}

//
// Find one item and activate it.
// To activate an item, set its state properly.
//
// The item is pointed to by the small pet 
// rotating about the center pet.
//
// The center pet is at the original, 
// Thus use the position vector of the small pet and the position vector
// of the item (i.e., the sphere). 
// If the angle deviation between these two vectors is smaller than 
// a threshold, pick the item and activate it.
// So, use dot product? do we need to compute the actual angle? 
// use acos?
//
// We will update the item based on the state of the item 
// in the main update function.
//
void BasicTutorial_00::activateOneItem( ) {
    double angle_deviation = READER_DATA::getAimAtSphereAngleDeviation( );
    //
    //
    //
}

//
// Update the states of objects.
// The states of objects include positions, 
// velocities, colours, materials, etc.
//
void BasicTutorial_00::UpdateMovableObjPosition(bool flg_large)
{
    Vector3 pos = mMovableObj->getPosition();
    pos.x = mRadius*cos(mAngle);
    pos.z = mRadius*sin(mAngle);
    mMovableObj->setPosition(pos);

    Vector3 q = mTargetObj->getPosition();

    q.y = pos.y;
    mMovableObj->lookAt(q, Node::TransformSpace::TS_WORLD);
    //mMovableObj->yaw(Degree(180));

    mMovableObj->yaw(
        Degree( READER_DATA::getYawAngleDegreeOffset_Pet( ) )
        );
    //
    //
    //

}

//
// Update the states of the spheres.
// In our case, the states include positions and velocities.
// Furthermore, if a sphere position is lower than the floor, 
// set the status of the sphere as ITEM_STATE_DONE. 
//
void BasicTutorial_00::updateSpheres( double time_step )
{
    double mag = 100.0;
    Vector3 force_gravity = mag*Vector3( 0.0, -1.0, 0.0 );
    double dt = time_step;
    //
    //
    //
}

//
// Update the pets.
//
// Rotate the two pets and make them look at each other.
// Rotate the small pet in counter-clockwise direction 
// and then clockwise direction. Repeat the process.
//
// dt is the simulation time step size.
//
void BasicTutorial_00::updatePets( double dt )
{
    if (!mFlg_MoveObj) return;
    //
    //
    //
}

//
// Purpose: Update the game state based on the game logic.
//
// return true if everything is normal. 
// return false to quit the program.
// 
// dt is the simulation time step size
//
bool BasicTutorial_00::updateGameState(double dt)
{
    bool flg = true; 

    updatePets( dt );
    updateSpheres( dt );

    return flg;
}
