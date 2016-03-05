//
//  Moon.cpp
//  Solar System Group
//
//  Created by Rajdeep Gill, Scott Smith, Mo M. , Minesh Varu
//

#include "Moon.hpp"

Moon::Moon() {
}
Moon::Moon(float orbitTime, float rotationTime, float radius, float incl, float distanceFromPlanet, Image* image) {
	this->distanceFromPlanet = distanceFromPlanet;
	this->orbitTime = orbitTime;
	this->rotationTime = rotationTime;
	this->radius = radius;
    this-> incl = incl;
	this->image = image;
	loadTexture();
}

void Moon::loadTexture() {
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

void Moon::draw(GLfloat pos[], float planetRadius, bool mO, bool oO) {
	if (mO) {
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
//    glTranslatef(((position[0]*distanceScale) + pos[0]), ((position[1]*distanceScale) + pos[1]), ((position[2]*distanceScale) + pos[2]));
		glTranslatef(position[0] * distanceScale, position[1] * distanceScale, position[2] * distanceScale);
		glRotatef(rotation, 0.0, 1.0, 0.0);
		gluQuadricTexture(quad, 1);
		gluSphere(quad, radius * planetSizeScale, slices, stacks);
		glPopMatrix();
	}
	if (oO)
		renderOrbit(true);
//    cout << ", x: " << ((position[0]*distanceScale)) << ", y: " << ((position[1]*distanceScale)) << ", z: " << ((position[2]*distanceScale)) << endl;
}
void Moon::draw2D(GLfloat pos[], float planetRadius, bool mO, bool oO) {
	if (mO) {
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
//    glTranslatef(((position[0]*distanceScale) + pos[0]), ((position[1]*distanceScale) + pos[1]), ((position[2]*distanceScale) + pos[2]));
		glTranslatef(position[0] * distanceScale, position[1] * distanceScale,
				position[2] * distanceScale);
		glRotatef(rotation, 0.0, 1.0, 0.0);
		gluQuadricTexture(quad, 1);
		gluSphere(quad, radius * planetSizeScale, slices, stacks);
		glPopMatrix();
	}
	if (oO)
		renderOrbit(false);
//    cout << ", x: " << ((position[0]*distanceScale)) << ", y: " << ((position[1]*distanceScale)) << ", z: " << ((position[2]*distanceScale)) << endl;
}

void Moon::renderOrbit(bool rings3D) {
	// draw a line strip
	glBegin(GL_LINE_STRIP);
	// loop round from 0 to 2*PI and draw around the radius of the orbit using trigonometry
	for (float angle = -1.0f; angle < 2 * PI; angle += 0.001f) {
//        glVertex3f(cos(angle) * distanceFromPlanet * distanceScale, sin(incl) * distanceFromPlanet * distanceScale, sin(angle) * distanceFromPlanet * distanceScale);
        glVertex3f(sin(angle) * distanceFromPlanet * distanceScale, 0.0f, cos(angle) * distanceFromPlanet * distanceScale);
	}
	glEnd();
}

void Moon::calculatePosition(float time, float planetPosition[]) {
	// find the angle of orientation of the orbit around the sun
	angle = time * 3.1419f / orbitTime;

	// use trig to find the position in space
	position[0] = sin(angle) * (distanceFromPlanet + radius) + planetPosition[0];
	position[2] = cos(angle) * (distanceFromPlanet + radius) + planetPosition[2];
//    position[1] = sin(incl) * distanceFromPlanet + planetPosition[1];
    position[1] = 0.0f;

	// find the rotation of the planet around its axis
	rotation = time * 360 / rotationTime;

}
