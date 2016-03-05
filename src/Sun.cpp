//
//  Sun.cpp
//  Solar System Group
//
//  Created by Rajdeep Gill, Scott Smith, Mo M. , Minesh Varu
//

#include "Sun.hpp"

Sun::Sun() {
}

Sun::Sun(float orbitTime, float rotationTime, float radius,
		float distanceFromSun) {
	this->distanceFromSun = distanceFromSun;
	this->orbitTime = orbitTime;
	this->rotationTime = rotationTime;
	this->radius = radius;
	this->position[0] = 0;
	this->position[1] = 0;
	this->position[2] = 0;
}

void Sun::loadTexture(Image* image) {
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

void Sun::draw() {
	// flushing/swapping and  done by caller
	quad = gluNewQuadric();
	gluQuadricDrawStyle(quad, GL_POINT);
	gluQuadricNormals(quad, GLU_SMOOTH);
	gluQuadricOrientation(quad, GLU_OUTSIDE);

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTranslatef(position[0], position[1],
			position[2]);
	glRotatef(rotation, 0.0, 1.0, 0.0);
	gluQuadricTexture(quad, 1);
	gluSphere(quad, radius * planetSizeScale, slices, stacks);
	glPopMatrix();
}
void Sun::draw2D() {
	float delta_theta = 0.01;
	glColor3f(1.0,1.0,1.0);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

	glBegin( GL_POLYGON); // OR GL_LINE_LOOP

	for (float angle = 0; angle < 2 * 3.14159; angle += delta_theta)
		glVertex3f(radius * planetSizeScale * cos(angle) + position[0], radius * planetSizeScale * sin(angle) + position[2], 0);

	glEnd();
    glFlush();
    glDisable(GL_TEXTURE_2D);
}

void Sun::calculatePosition(float time) {
	// find the rotation of the planet around its axis
	rotation = time * 360 / rotationTime;
}
