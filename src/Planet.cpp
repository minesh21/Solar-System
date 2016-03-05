//
//  planet.cpp
//  Solar System Group
//
//  Created by Rajdeep Gill, Scott Smith, Mo M. , Minesh Varu
//

#include "Planet.hpp"

float planetSizeScale = 0.003f;
//float distanceScale = 0.0009f;


Planet::Planet() {
}

Planet::Planet(float orbitTime, float rotationTime, float radius, float incl, float distanceFromSun) {
    this->distanceFromSun = distanceFromSun;
    this->orbitTime = orbitTime;
    this->rotationTime = rotationTime;
    this->radius = radius;
    this-> incl = incl;
}

Planet::Planet(float orbitTime, float rotationTime, float radius, float incl, float distanceFromSun, Image* image) {
    this->distanceFromSun = distanceFromSun;
    this->orbitTime = orbitTime;
    this->rotationTime = rotationTime;
    this->radius = radius;
    this-> incl = incl;
    loadTexture(image);
}

void Planet::loadTexture(Image* image) {
    GLuint textureId;
    glGenTextures(1, &textureId); //Make room for our texture
    glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGB,                       //Format OpenGL uses for image
                 image->width, image->height,  //Width and height
                 0,                            //The border of the image
                 GL_RGB, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                 //as unsigned numbers
                 image->pixels);               //The actual pixel data
    texture = textureId;
    //    return textureId; //Returns the id of the texture
}

void Planet::addMoon(float orbitTime, float rotationTime, float radius, float incl, float distanceFromPlanet, Image *image) {
    moons.push_back(Moon(orbitTime, rotationTime, radius, incl, distanceFromPlanet, image));
}

void Planet::draw(bool m, bool o) {
    // flushing/swapping and  done by caller
    quad = gluNewQuadric();
    gluQuadricDrawStyle(quad, GL_POINT);
    gluQuadricNormals(quad, GLU_SMOOTH);
    gluQuadricOrientation(quad, GLU_OUTSIDE);
    glPushMatrix();
    
    if (moons.size() != 0) {
        for (int i = 0; i < moons.size(); i++) {
            moons[i].draw(position, radius, m, o);
        }
    }
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTranslatef(position[0] * distanceScale, position[1] * distanceScale,
                 position[2] * distanceScale);
    
    glRotatef(rotation, 0.0, 1.0, 0.0);
    gluQuadricTexture(quad, 1);
    gluSphere(quad, radius * planetSizeScale, slices, stacks);
    glPopMatrix();
    if (o){
        renderOrbit(true);
    }
}

void Planet::draw2D(bool m, bool o) {
    float delta_theta = 0.01;
    glColor3f(1.0,0.0,0.0);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
    
    glBegin( GL_POLYGON); // OR GL_LINE_LOOP
    
    for (float angle = 0; angle < 2 * 3.14159; angle += delta_theta)
        glVertex3f(radius * planetSizeScale * cos(angle)+ position[0]*distanceScale, radius * planetSizeScale * sin(angle) + position[1]*distanceScale, 0);
    
    glEnd();
    glFlush();
    glDisable(GL_TEXTURE_2D);
    if (o)
        renderOrbit(false);
}

void Planet::renderOrbit(bool rings3D) {
    // draw a line strip
    glBegin(GL_LINE_STRIP);
    glLineWidth(100);
    // loop round from 0 to 2*PI and draw around the radius of the orbit using trigonometry
    for (float angle = -1.0f; angle < 2*PI; angle += 0.001f) {
//        glVertex3f(cos(angle) * distanceFromSun * distanceScale, sin(incl) * distanceFromSun * distanceScale, 0.5 *sin(angle) * distanceFromSun * distanceScale);
        glVertex3f(0.5*sin(angle) * distanceFromSun * distanceScale, 0.0f, cos(angle) * distanceFromSun * distanceScale);
    }
    glEnd();

    
    glPushMatrix();
    // translate to the center of this planet to draw the moon orbit around it
    glTranslatef(position[0] * distanceScale, position[1] * distanceScale,
                 position[2] * distanceScale);

    // draw all moon orbits
    if (moons.size() != 0) {
        for (int i = 0; i < moons.size(); i++)
        {
            moons[i].renderOrbit(rings3D);
        }
    }
    
    glPopMatrix();
}

void Planet::calculatePosition(float time) {
    // find the angle of orientation of the orbit around the sun
    angle = time * 3.1419f / orbitTime;
    
    // use trig to find the position in space
    position[0] = 0.5 * sin(angle) * distanceFromSun;
    position[2] = cos(angle) * distanceFromSun;
//    position[1] = sin(incl) * distanceFromSun;
    position[1] = 0.0f;
    
    // find the rotation of the planet around its axis
    rotation = time * 360 / rotationTime;
    
    // calculate positions of moons
    if (moons.size() != 0) {
        for (int i = 0; i < moons.size(); i++)
        {
            moons[i].calculatePosition(time, position);
        }
    }
}

void Planet::printPosition(string name){
    cout << name << " position:" << endl;
    cout << "x: " << position[0]*distanceScale << endl;
    cout << "y: " << position[1]*distanceScale << endl;
    cout << "z: " << position[2]*distanceScale << endl;
    cout << endl;
}

float Planet::getX(){
    return position[0] * distanceScale;
    
}
float Planet::getY(){
    return position[1] * distanceScale;
}
float Planet::getZ(){
    return position[2] * distanceScale;
}
