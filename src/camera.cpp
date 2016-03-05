//  Created by Rajdeep Gill, Scott Smith, Mo M. , Minesh Varu

#include "camera.h"
#include "math.h"
#include <iostream>
//#include "windows.h"

#define squared(x) (x*x)

#define NULL_VECTOR newGL3dVector(0.0f,0.0f,0.0f)

GL3dVector newGL3dVector ( GLfloat x, GLfloat y, GLfloat z )
{
	GL3dVector tmp;
	tmp.x = x;
	tmp.y = y;
	tmp.z = z;
	return tmp;
}

GLfloat getGL3dVectorLength( GL3dVector * v)
{
	return (GLfloat)(sqrt(squared(v->x)+squared(v->y)+squared(v->z)));
}

GL3dVector normalize3dVector( GL3dVector v)
{
	GL3dVector res;
	float l = getGL3dVectorLength(&v);
	if (l == 0.0f) return NULL_VECTOR;
	res.x = v.x / l;
	res.y = v.y / l;
	res.z = v.z / l;
	return res;
}

GL3dVector operator+ (GL3dVector v, GL3dVector u)
{
	GL3dVector res;
	res.x = v.x+u.x;
	res.y = v.y+u.y;
	res.z = v.z+u.z;
	return res;
}
GL3dVector operator- (GL3dVector v, GL3dVector u)
{
	GL3dVector res;
	res.x = v.x-u.x;
	res.y = v.y-u.y;
	res.z = v.z-u.z;
	return res;
}


GL3dVector operator* (GL3dVector v, float r)
{
	GL3dVector res;
	res.x = v.x*r;
	res.y = v.y*r;
	res.z = v.z*r;
	return res;
}

GL3dVector crossProduct (GL3dVector * u, GL3dVector * v)
{
	GL3dVector resVector;
	resVector.x = u->y*v->z - u->z*v->y;
	resVector.y = u->z*v->x - u->x*v->z;
	resVector.z = u->x*v->y - u->y*v->x;

	return resVector;
}
float operator* (GL3dVector v, GL3dVector u)	//dot product
{
	return v.x*u.x+v.y*u.y+v.z*u.z;
}




/***************************************************************************************/

GLcamera::GLcamera()
{
	position = newGL3dVector (0.0, 0.0,	0.0);
	viewDir = newGL3dVector( 0.0, 0.0, 0.0);
	rightVector = newGL3dVector (1.0, 0.0, 0.0);
	upVector = newGL3dVector (0.0, 1.0, 0.0);

	rotatedX = 0.0;
	rotatedY = 0.0;
	rotatedZ = 0.0;
}

void GLcamera::move (GL3dVector direction)
{
	position = position + direction;
}
void GLcamera::moveTo(GL3dVector pos){
	position.x = pos.x;
	position.y = pos.y;
	position.z = pos.z;
	viewDir.x = -pos.x;
	viewDir.y = -pos.y;
	viewDir.z = -pos.z;
	upVector.x = 0.0;
	upVector.y = 1.0;
	upVector.z = 0.0;
    rightVector.x = 1.0;
    rightVector.y = 0.0;
    rightVector.z = 0.0;
}

void GLcamera::rotateX (GLfloat angle)
{
	rotatedX += angle;
	
	//Rotate viewdir around the right vector:
	viewDir = normalize3dVector(viewDir*cos(angle*PIto180)
								+ upVector*sin(angle*PIto180));

	//now compute the new UpVector (by cross product)
	upVector = crossProduct(&viewDir, &rightVector)*-1;

	
}

void GLcamera::rotateY (GLfloat angle)
{
	rotatedY += angle;
	
	//Rotate viewdir around the up vector:
	viewDir = normalize3dVector(viewDir*cos(angle*PIto180)
								- rightVector*sin(angle*PIto180));

	//now compute the new RightVector (by cross product)
	rightVector = crossProduct(&viewDir, &upVector);
}

void GLcamera::rotateZ (GLfloat angle)
{
	rotatedZ += angle;
	
	//Rotate viewdir around the right vector:
	rightVector = normalize3dVector(rightVector*cos(angle*PIto180)
								+ upVector*sin(angle*PIto180));

	//now compute the new UpVector (by cross product)
	upVector = crossProduct(&viewDir, &rightVector)*-1;
}

void GLcamera::render( void )
{

	//The point at which the camera looks:
	GL3dVector viewPoint = getViewPoint();

	//as we know the up vector, we can easily use gluLookAt:
	gluLookAt(	position.x,position.y,position.z,
				viewPoint.x,viewPoint.y,viewPoint.z,
				upVector.x,upVector.y,upVector.z);
}

void GLcamera::moveForward( GLfloat distance )
{
	position = position + (viewDir*-distance);
}

void GLcamera::strafeRight ( GLfloat distance )
{
	position = position + (rightVector*distance);
}

void GLcamera::moveUpward( GLfloat Distance )
{
	position = position + (upVector*Distance);
}
GL3dVector GLcamera::getViewPoint()
{
	GL3dVector temp = position+viewDir;
	return temp;
}



