//
//  Sun.hpp
//  Solar System Group
//
//  Created by Rajdeep Gill, Scott Smith, Mo M. , Minesh Varu
//

#ifndef Sun_hpp
#define Sun_hpp

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

class Sun{
    
private:
    float distanceFromSun;
    float orbitTime;
    float rotationTime;
    float radius;
    GLuint texture;
    float position[3];
    float rotation;
    GLUquadricObj *quad;
    
public:
    Sun();
    Sun(float orbitTime, float rotationTime, float radius, float distanceFromSun);
    // Get its position in 3d world space units (after scaling) and put it into the 3d vector
    void loadTexture(Image* image);
    void calculatePosition(float time);
    void draw();
    void draw2D();
};

#endif /* Sun_hpp */
