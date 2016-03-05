//
//  Universe.cpp
//  Solar System Group
//
//  Created by Rajdeep Gill, Scott Smith, Mo M. , Minesh Varu
//

#include "Globals.h"
#include "Sun.hpp"
#include "Planet.hpp"
#include "Moon.hpp"
#include "camera.h"

//global variable

GLUquadricObj *quad;

// < --- BEGIN CAMERA GLOABLS - >
GLcamera camera;
bool orbitCamera;
float cameraAngle = 0;
// < --- END CAMERA GLOBALS --- >

// < --- BEGIN KEYBOARD GLOBALS - >
bool moonsOn = true;
bool orbitRingsOn = true;
bool draw3D = true;
// < --- END KEYBOARD GLOBALS --- >

Image *isun = loadBMP("Images/sun.bmp");
Image *imercury = loadBMP("Images/mercury.bmp");
Image *ivenus = loadBMP("Images/venus.bmp");
Image *iearth = loadBMP("Images/earth.bmp");
Image *imars = loadBMP("Images/mars.bmp");
Image *ijupiter = loadBMP("Images/jupiter.bmp");
Image *isaturn = loadBMP("Images/saturn.bmp");
Image *iuranus = loadBMP("Images/uranus.bmp");
Image *ineptune = loadBMP("Images/neptune.bmp");
Image *ipluto = loadBMP("Images/pluto.bmp");
Image *imoon = loadBMP("Images/earthMoon.bmp");
Image *iphobos = loadBMP("Images/phobos.bmp");
Image *ideimos = loadBMP("Images/deimos.bmp");
Image *iio = loadBMP("Images/io.bmp");
Image *ieuropa = loadBMP("Images/europa.bmp");
Image *iganymede = loadBMP("Images/ganymede.bmp");
Image *icallisto = loadBMP("Images/callisto.bmp");
Image *icharon = loadBMP("Images/charon.bmp");

//planets

Sun sun = Sun(sunOrbit, sunRotation, sunRadius, sunToSun);
//inner solar system
Planet mercury = Planet(mercuryOrbit, mercuryRotation, mercuryRadius, mercuryIncl, mercuryToSun);
Planet venus = Planet(venusOrbit, venusRotation, venusRadius, venusIncl, venusToSun);
Planet earth = Planet(earthOrbit, earthRotation, earthRadius, earthIncl, earthToSun);
Planet mars = Planet(marsOrbit, marsRotation, marsRadius, marsIncl, marsToSun);
//outer solar system
Planet jupiter = Planet(jupiterOrbit, jupiterRotation, jupiterRadius, jupiterIncl, jupiterToSun);
Planet saturn = Planet(saturnOrbit, saturnRotation, saturnRadius, saturnIncl, saturnToSun);
Planet uranus = Planet(uranusOrbit, uranusRotation, uranusRadius, uranusIncl, uranusToSun);
Planet neptune = Planet(neptuneOrbit, neptuneRotation, neptuneRadius, neptuneIncl, neptuneToSun);
Planet pluto = Planet(plutoOrbit, plutoRotation, plutoRadius, plutoIncl, plutoToSun);

GLfloat xeye = 3.0, yeye = 3.0, zeye = 7.0; //  Viewing-coordinate origin.
GLfloat xref = 0.0, yref = 0.0, zref = 0.0; //  Look-at point.
GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0; //  View up vector.

/*  Set positions for near and far clipping planes:  */
GLfloat vangle = 40.0, dnear = 4.0, dfar = 500000000.0;

float angle = 10.0;

GLint const HEIGHT = 800;   //need actual square values for 
GLint const WIDTH = 800;
GLfloat wWidth = WIDTH;
GLint wHeight = HEIGHT;

double times;
double timeSpeed;

void initRendering() {
	//Makes 3D drawing work when something is in front of something elsev
	glEnable(GL_DEPTH_TEST);
    
    
    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_TEXTURE_2D);
    
    // set up lighting
    glEnable(GL_LIGHTING);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    GLfloat matSpecular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat matAmbience[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat matShininess[] = { 20.0 };
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbience);
    
    GLfloat lightAmbient[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat lightDiffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat lightSpecular[] = { 1.0, 1.0, 1.0, 1.0 };
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //glDisable(GL_LIGHTING);
    
    
    
	sun.loadTexture(isun);
	mercury.loadTexture(imercury);
	venus.loadTexture(ivenus);
	earth.loadTexture(iearth);
	mars.loadTexture(imars);
	jupiter.loadTexture(ijupiter);
	saturn.loadTexture(isaturn);
	uranus.loadTexture(iuranus);
	neptune.loadTexture(ineptune);
	pluto.loadTexture(ipluto);
	earth.addMoon(moonOrbit, moonRotation, moonRadius, moonIncl, moonToEarth, imoon);
	mars.addMoon(phobosOrbit, phobosRotation, phobosRadius, phobosIncl, phobosToMars, iphobos);
	mars.addMoon(deimosOrbit, deimosRotation, deimosRadius, deimosIncl, deimosToMars, ideimos);
	jupiter.addMoon(ioOrbit, ioRotation, ioRadius, ioIncl, ioToJupiter, iio);
	jupiter.addMoon(europaOrbit, europaRotation, europaRadius, europaIncl, europaToJupiter, ieuropa);
	jupiter.addMoon(ganymedeOrbit, ganymedeRotation, ganymedeRadius, ganymedeIncl, ganymedeToJupiter, iganymede);
	jupiter.addMoon(callistoOrbit, callistoRotation, callistoRadius, callistoIncl, callistoToJupiter, icallisto);
	pluto.addMoon(charonOrbit, charonRotation, charonRadius, charonIncl, charonToPluto, icharon);
    
	times = 2.552f;
	timeSpeed = 0.0001f;
}
void update(int value) {
	angle += 1.0f;
	if (angle > 360) {
		angle -= 360;
	}
	glutPostRedisplay();
	//Tell GLUT to call update again in 25 milliseconds
	glutTimerFunc(25, update, 0);
}

void cameraOrbit(int val) {
    if (orbitCamera) {
        camera.moveTo(newGL3dVector(cos(cameraAngle * PIto180) * 10, 0, sin(cameraAngle * PIto180) * 10));
        cameraAngle =
        (cameraAngle < 360) ? cameraAngle + 90.0 : cameraAngle - 360;
    }
    glutTimerFunc(1000, cameraOrbit, 0);

}

//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void drawScene() {
	sun.calculatePosition(times);
	mercury.calculatePosition(times);
	venus.calculatePosition(times);
	earth.calculatePosition(times);
	mars.calculatePosition(times);
	jupiter.calculatePosition(times);
	saturn.calculatePosition(times);
	uranus.calculatePosition(times);
	neptune.calculatePosition(times);
	pluto.calculatePosition(times);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
    glLoadIdentity(); //Reset the drawing perspective
    
    GLfloat lightPosition[] = { 0.0, 0.0, 0.0, 10.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    
    camera.render();
    sun.calculatePosition(times);
    sun.draw();

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    
    mercury.draw(moonsOn, orbitRingsOn);
    venus.draw(moonsOn, orbitRingsOn);
    earth.draw(moonsOn, orbitRingsOn);
    mars.draw(moonsOn, orbitRingsOn);
    jupiter.draw(moonsOn, orbitRingsOn);
    saturn.draw(moonsOn, orbitRingsOn);
    uranus.draw(moonsOn, orbitRingsOn);
    neptune.draw(moonsOn, orbitRingsOn);
    pluto.draw(moonsOn, orbitRingsOn);
    
    //print new positions
//    mercury.printPosition("Mercury");
//    venus.printPosition("Venus");
//    earth.printPosition("Earth");
//    mars.printPosition("Mars");
//    jupiter.printPosition("Jupiter");
//    saturn.printPosition("Saturn");
//    uranus.printPosition("Uranus");
//    neptune.printPosition("Neptune");
//    pluto.printPosition("Pluto");
    

	if (draw3D) {
        glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
        glLoadIdentity(); //Reset the drawing perspective


	} else {
		glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
		glLoadIdentity();
        sun.calculatePosition(times);
        mercury.calculatePosition(times);
        venus.calculatePosition(times);
        earth.calculatePosition(times);
        mars.calculatePosition(times);
        jupiter.calculatePosition(times);
        saturn.calculatePosition(times);
        uranus.calculatePosition(times);
        neptune.calculatePosition(times);
        pluto.calculatePosition(times);
        
        pluto.draw2D(moonsOn, orbitRingsOn);
        neptune.draw2D(moonsOn, orbitRingsOn);
        uranus.draw2D(moonsOn, orbitRingsOn);
        saturn.draw2D(moonsOn, orbitRingsOn);
        jupiter.draw2D(moonsOn, orbitRingsOn);
        mars.draw2D(moonsOn, orbitRingsOn);
        earth.draw2D(moonsOn, orbitRingsOn);
        venus.draw2D(moonsOn, orbitRingsOn);
        mercury.draw2D(moonsOn, orbitRingsOn);
        sun.draw2D();
	}
    glDisable(GL_LIGHTING);

    glDisable(GL_DEPTH_TEST);

    
	times += timeSpeed;
    glFlush();

	glutSwapBuffers(); //Send the 3D scene to the screen

}

void handleResize(GLint w, GLint h) {
	wWidth = w;
	wHeight = h;
	//Tell OpenGL how to convert from coordinates to pixel values
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective
	//Set the camera perspective
	glLoadIdentity(); //Reset the camera
	if (draw3D) {
		gluPerspective(vangle, (double) w / (double) h, dnear, dfar);
	}
	else
	{
        
		gluOrtho2D(-4000, 4000, -4000, 4000);
	}
}

void myKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 32:
		orbitCamera = (orbitCamera ? false : true);
		break;
	case 27:		//ESC

#ifdef _WIN32
		PostQuitMessage(0);
#endif
            
        case 'm':
            if (moonsOn)
                moonsOn = false;
            else
                moonsOn = true;
            break;
        case 'o':
            if (orbitRingsOn)
                orbitRingsOn = false;
            else
                orbitRingsOn = true;
            break;
        case '@':
            if (draw3D){
                draw3D = false;
                initRendering();
            }
            handleResize(wWidth,wHeight);
            
            break;
        case '#':
            if (draw3D == false){
                draw3D = true;
                initRendering();
            }
            handleResize(wWidth,wHeight);
            break;
            
        case '/':
            camera.moveTo(newGL3dVector(0.0, 0.0, -12000.0));
            break;
            
        case 'a':
            camera.rotateY(5.0);
            break;
            
        case 'd':
            camera.rotateY(-5.0);
            break;
            
        case 'w':
            camera.moveForward(-0.01);
            break;
            
        case 's':
            camera.moveForward(0.01);
            break;
            
        case 'x':
            camera.rotateX(5.0);
            break;
            
        case 'y':
            camera.rotateX(-5.0);
            break;
            
        case 'c':
            camera.strafeRight(-1);
            break;
            
        case 'v':
            camera.strafeRight(1);
            break;
            
        case 'f':
            camera.moveUpward(-50.0);
            break;
            
        case 'r':
            camera.moveUpward(50.0);
            break;
            
        case 'j':
            camera.rotateZ(-5.0);
            break;
            
        case 'k':
            camera.rotateZ(5.0);
            break;
            
        case '+':
            timeSpeed*=1.1;
            break;
            
        case'-':
            timeSpeed*=0.9;
            break;
            
        case '[':
            planetSizeScale/=1.2; // make planet scale smaller
            break;
            
        case ']':
            planetSizeScale*=1.2; // make planet scale bigger
            break;
            
//        case '<':
//            distanceScale/=1.2; // make planet scale smaller
//            break;
//            
//        case '>':
//            distanceScale*=1.2; // make planet scale bigger
//            break;
          
        case '.':
            camera.moveTo(newGL3dVector(1.0, 1.0, 1.0));
            break;
            
        case '1':
            cout << "Moved to Mercury: x: " << mercury.getX() << " y: " <<mercury.getY() << " z: " << mercuryToSun*distanceScale<< endl <<endl;
            camera.moveTo(newGL3dVector(mercury.getX(), mercury.getY(),  mercury.getZ() + (mercuryRadius*3*planetSizeScale) ));
            break;
            
        case '2':
            cout << "Moved to Venus: x: " << venus.getX() << " y: " <<venus.getY() << " z: " << venus.getZ() + venusToSun*3*distanceScale<< endl <<endl;
            camera.moveTo(newGL3dVector(venus.getX(), venus.getY(), venus.getZ() + (venusRadius*3*planetSizeScale) ));
            break;
            
        case '3':
            cout << "Moved to Earth: x: " << earth.getX() << " y: " <<earth.getY() << " z: " << earth.getZ()<< endl <<endl;
            camera.moveTo(newGL3dVector(earth.getX(), earth.getY(), earth.getZ() + (earthRadius*3*planetSizeScale) ));
            break;
            
        case '4':
            
            cout << "Moved to Mars: x: " << mars.getX() << " y: " <<mars.getY() << " z: " << mars.getZ()<< endl <<endl;
            camera.moveTo(newGL3dVector(mars.getX(), mars.getY(), mars.getZ() + (marsRadius*3*planetSizeScale) ));
            break;
            
        case '5':
            
            cout << "Moved to Jupiter: x: " << jupiter.getX() << " y: " <<jupiter.getY() << " z: " << jupiter.getZ()<< endl <<endl;
            camera.moveTo(newGL3dVector(jupiter.getX(), jupiter.getY(), jupiter.getZ() + (jupiterRadius*3*planetSizeScale) ));
            break;
            
        case '6':
            cout << "Moved to Saturn: x: " << saturn.getX() << " y: " <<saturn.getY() << " z: " << saturn.getZ()<< endl <<endl;
            camera.moveTo(newGL3dVector(saturn.getX(), saturn.getY(), saturn.getZ() + (saturnRadius*3*planetSizeScale) ));
            break;
            
        case '7':
            cout << "Moved to Uranus: x: " << uranus.getX() << " y: " <<uranus.getY() << " z: " << uranus.getZ()<< endl <<endl;
            camera.moveTo(newGL3dVector(uranus.getX(), uranus.getY(), uranus.getZ() + (uranusRadius*3*planetSizeScale) ));
            break;

        case '8':
            cout << "Moved to Neptune: x: " << neptune.getX() << " y: " <<neptune.getY() << " z: " << neptune.getZ()<< endl <<endl;
            camera.moveTo(newGL3dVector(neptune.getX(), neptune.getY(), neptune.getZ() + (neptuneRadius*3*planetSizeScale) ));
            break;
            
        case '9':
            cout << "Moved to Puto: x: " << pluto.getX() << " y: " <<pluto.getY() << " z: " << pluto.getZ()<< endl <<endl;
            camera.moveTo(newGL3dVector(pluto.getX(), pluto.getY(), pluto.getZ() + (plutoRadius*3*planetSizeScale) ));
            break;

    }
}

void SpecialInput(int key, int x, int y) {
    switch (key) {
            
        case GLUT_KEY_UP:
            camera.moveForward(-10.0);
            break;
            
        case GLUT_KEY_DOWN:
            camera.moveForward(10.0);
            break;
            
        case GLUT_KEY_LEFT:
            camera.strafeRight(-10.0);
            break;
            
        case GLUT_KEY_RIGHT:
            camera.strafeRight(10.0);
            break;
    }
}


int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT); //Set the window size

	//Create the window
	glutCreateWindow(
			"CP411 Final: Solar System | Minesh Mohamed Rajdeep Scott");
	camera.moveTo(newGL3dVector(0.0, 0.0, 30000.0));
	initRendering(); //Initialize rendering
	//Set handler functions for drawing, keypresses, and window resizes
	glutDisplayFunc(drawScene);
	glutReshapeFunc(handleResize);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(SpecialInput);
	glutTimerFunc(25, update, 0); //Add a timer
	glutTimerFunc(1000, cameraOrbit, 0);
	glutMainLoop(); //Start the main loop.  glutMainLoop doesn't return.
	return 0; //This line is never reached
}
