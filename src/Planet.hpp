//
//  Planet.hpp
//  Solar System Group
//
//  Created by Rajdeep Gill, Scott Smith, Mo M. , Minesh Varu
//

#ifndef Planet_hpp
#define Planet_hpp

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifdef _WIN32
#include <windows.h>
#endif

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <vector>
#include "Moon.hpp"
#include "Globals.h"
#include "imageloader.h"


using namespace std;

class Planet{

private:
    // distance from the sun
    float distanceFromSun;
    // time it takes to complete 1 orbit
    float orbitTime;
    // time it takes to spin 360 degrees
    float rotationTime;
    // radius of the planet itself
    float radius;
    // the texture used for rendering
    GLuint texture;
    // its position in 3d space
    float position[3];
    // its rotation around its axis
    float rotation;
    // list of moons attached to this planet
    float incl;
    vector<Moon> moons;
    float angle;
    GLUquadricObj *quad;

    
public:
    Planet();
    // Distance is in units of km (kilometers) and time is in units of earth days (365.25 orbit time for earth)
    Planet(float orbitTime, float rotationTime, float radius, float incl, float distanceFromSun);
    Planet(float orbitTime, float rotationTime, float radius, float incl, float distanceFromSun, Image* image);
    void loadTexture(Image* image);
    // Get its position in 3d world space units (after scaling) and put it into the 3d vector
    // add a moon to this planet
    void addMoon(float orbitTime, float rotationTime, float radius, float incl, float distanceFromPlanet, Image *image);
    void renderOrbit(bool rings3D);
    void calculatePosition(float time);
    
    void printPosition(string name);
    float getX();
    float getY();
    float getZ();
    
    void draw(bool, bool);
    void draw2D(bool, bool);

};
#endif /* planet_hpp */
