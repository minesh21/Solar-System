//
//  Moon.hpp
//  Solar System Group
//
//  Created by Rajdeep Gill, Scott Smith, Mo M. , Minesh Varu
//

#ifndef Moon_hpp
#define Moon_hpp

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
#include "Globals.h"
#include "imageloader.h"

using namespace std;

class Moon{
    
private:
    float distanceFromPlanet;
    float orbitTime;
    float rotationTime;
    float radius;
    GLuint texture;
    float position[3];
    float rotation;
    float incl;
    GLUquadricObj *quad;
    Image* image;
    float angle;

public:
    Moon();
    Moon(float orbitTime, float rotationTime, float radius, float incl, float distanceFromPlanet, Image* image);
    void loadTexture();
    // Get its position in 3d world space units (after scaling) and put it into the 3d vector
    void renderOrbit(bool rings3D);
    void calculatePosition(float time, float planetPosition[]);
    void draw(float[], float radius);
    void draw(float[], float radius, bool mO, bool oO);
    void draw2D(float[], float radius, bool mO, bool oO);
};
#endif /* Moon_hpp */
