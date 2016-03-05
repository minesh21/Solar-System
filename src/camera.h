//  Created by Rajdeep Gill, Scott Smith, Mo M. , Minesh Varu

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifdef _WIN32
#include <windows.h>
#endif
#include "Globals.h"
#define PI 3.1415926535897932384626433832795
#define PIto180 PI/180



/////////////////////////////////
//Note: All angles in degrees  //
/////////////////////////////////

struct GL3dVector  //Float 3d-vect, normally used
{
	GLfloat x,y,z;
};
GL3dVector newGL3dVector ( GLfloat x, GLfloat y, GLfloat z );

class GLcamera
{
//private:

public:
	
	GL3dVector viewDir;
	GL3dVector rightVector;
	GL3dVector upVector;
	GL3dVector position;

	GLfloat rotatedX, rotatedY, rotatedZ;
	

	GLcamera();				//inits the values (Position: (0|0|0) Target: (0|0|-1) )
	void render ( void );	//executes some glRotates and a glTranslate command
							//Note: You should call glLoadIdentity before using Render

	void move ( GL3dVector direction );
	void moveTo ( GL3dVector direction );
	void rotateX ( GLfloat angle );
	void rotateY ( GLfloat angle );
	void rotateZ ( GLfloat angle );

	void moveForward ( GLfloat distance );
	void moveUpward ( GLfloat distance );
	void strafeRight ( GLfloat distance );
	GL3dVector getViewPoint (void);
};
